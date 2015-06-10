// NSDL library support functions

#include "mbed.h"
#include "nsdl_support.h"

#include "mbedConnectorInterface.h"

// we have to redefine DBG as its used differently here...
#ifdef DBG
    #undef DBG
#endif
#define DBG  std::printf

#include "EthernetInterface.h"
#include "UDPSocket.h"
#include "Endpoint.h"

Endpoint nsp;
UDPSocket server;

char null_endpoint_name[] = "";
char null_domain[] = "";
uint8_t null_ep_type[] = "";
uint8_t null_lifetime_ptr[] = "";
bool endpoint_registered = false;

void *nsdl_alloc(uint16_t size) {
    void *chunk = NULL;
    if (size > 0) chunk = malloc(size);
    if (chunk != NULL && size > 0) memset(chunk,0,size);
    return chunk;
}

void nsdl_free(void* ptr_to_free) {
    if (ptr_to_free != NULL) free(ptr_to_free);
}

/*
 * Create a static resoure
 * Only get is allowed
 */
void nsdl_create_static_resource(sn_nsdl_resource_info_s *resource_structure, uint16_t pt_len, uint8_t *pt, uint16_t rpp_len, uint8_t *rpp_ptr, uint8_t *rsc, uint16_t rsc_len)
{
    resource_structure->access = SN_GRS_GET_ALLOWED;
    resource_structure->mode = SN_GRS_STATIC;
    resource_structure->pathlen = pt_len;
    resource_structure->path = pt;
    resource_structure->resource_parameters_ptr->resource_type_len = rpp_len;
    resource_structure->resource_parameters_ptr->resource_type_ptr = rpp_ptr;
    resource_structure->resource = rsc;
    resource_structure->resourcelen = rsc_len;
    sn_nsdl_create_resource(resource_structure);
}

void nsdl_create_dynamic_resource(sn_nsdl_resource_info_s *resource_structure, uint16_t pt_len, uint8_t *pt, uint16_t rpp_len, uint8_t *rpp_ptr, uint8_t is_observable, sn_grs_dyn_res_callback_t callback_ptr, int access_right)
{
    resource_structure->access = (sn_grs_resource_acl_e)access_right;
    resource_structure->resource = 0;
    resource_structure->resourcelen = 0;
    resource_structure->sn_grs_dyn_res_callback = callback_ptr;
    resource_structure->mode = SN_GRS_DYNAMIC;
    resource_structure->pathlen = pt_len;
    resource_structure->path = pt;
    resource_structure->resource_parameters_ptr->resource_type_len = rpp_len;
    resource_structure->resource_parameters_ptr->resource_type_ptr = rpp_ptr;
    resource_structure->resource_parameters_ptr->observable = is_observable;
    sn_nsdl_create_resource(resource_structure);
}

sn_nsdl_ep_parameters_s* nsdl_init_register_endpoint(sn_nsdl_ep_parameters_s *endpoint_structure, uint8_t *domain, uint8_t* name, uint8_t* typename_ptr, uint8_t *lifetime_ptr) {
    if (endpoint_structure == NULL) {   
        endpoint_structure = (sn_nsdl_ep_parameters_s*)nsdl_alloc(sizeof(sn_nsdl_ep_parameters_s));
    }
    
    if (endpoint_structure != NULL) {
        memset(endpoint_structure, 0, sizeof(sn_nsdl_ep_parameters_s));
        endpoint_structure->endpoint_name_ptr = name;
        endpoint_structure->endpoint_name_len = strlen((char*)name);
        endpoint_structure->domain_name_ptr = domain;
        endpoint_structure->domain_name_len = strlen((char *)domain);
        endpoint_structure->type_ptr = typename_ptr;
        endpoint_structure->type_len =  strlen((char*)typename_ptr);
        endpoint_structure->lifetime_ptr = lifetime_ptr;
        endpoint_structure->lifetime_len =  strlen((char*)lifetime_ptr);
    }
    
    return endpoint_structure;
}

void nsdl_clean_register_endpoint(sn_nsdl_ep_parameters_s **endpoint_structure) {
    if (endpoint_structure != NULL) {
        if (*endpoint_structure != NULL) {
            nsdl_free(*endpoint_structure);
            *endpoint_structure = NULL;
        }
    }
}

static uint8_t tx_cb(sn_nsdl_capab_e protocol, uint8_t *data_ptr, uint16_t data_len, sn_nsdl_addr_s *address_ptr) {
    //DBG("NSP: sending %d bytes...\r\n",data_len);
    int sent = server.sendTo(nsp, (char*)data_ptr, data_len);
    return 1;
}

static uint8_t rx_cb(sn_coap_hdr_s *coap_packet_ptr, sn_nsdl_addr_s *address_ptr) {
    // Rx callback process it...
    //DBG("NSP: received data. processing...\r\n");
    return 0;
}

void register_endpoint(bool init) {
    sn_nsdl_ep_parameters_s *endpoint_ptr = NULL;
    if (init) {
        endpoint_ptr = nsdl_init_register_endpoint(endpoint_ptr, (uint8_t *)domain_name, (uint8_t*)endpoint_name, ep_type, lifetime_ptr);
        if(sn_nsdl_register_endpoint(endpoint_ptr) != 0) {
            DBG("NSP initial registration failed\r\n");
            endpoint_registered = false;
        }
        else {
            //DBG("NSP initial registration OK\r\n");
            endpoint_registered = true;
        }
    }
    else {
        endpoint_ptr = nsdl_init_register_endpoint(endpoint_ptr, (uint8_t *)null_domain, (uint8_t*)null_endpoint_name, null_ep_type, null_lifetime_ptr);
        if(sn_nsdl_update_registration(endpoint_ptr) != 0) {
            DBG("NSP re-registration failed\r\n");
            endpoint_registered = false;
        }
        else {
            //DBG("NSP re-registration OK\r\n");
            endpoint_registered = true;
        }
    }
    nsdl_clean_register_endpoint(&endpoint_ptr);
}

bool nsdl_endpoint_is_registered(void) {
    return endpoint_registered;
}

void registration_update_thread(void const *args) {    
    while(true) {
        Thread::wait(NSP_RD_UPDATE_PERIOD);
        register_endpoint(false);
    }
}

void nsdl_init() {    
    sn_nsdl_mem_s memory_cbs;
    
    // initilize the UDP channel
    server.init();
    server.bind(nsp_port);
    
    /* Initialize libNsdl */
    memset(&memory_cbs,0,sizeof(memory_cbs));
    memory_cbs.sn_nsdl_alloc = &nsdl_alloc;
    memory_cbs.sn_nsdl_free = &nsdl_free;
    if(sn_nsdl_init(&tx_cb, &rx_cb, &memory_cbs) == -1) {
        DBG("NSP: libNsdl init failed.\r\n");
    }
    else {
        DBG("NSP: libNsdl init successful.\r\n");
    }
}

void nsdl_set_nsp_address(void) {
    char NSP_address_str[16];
    
    /* Set nsp address for library */
    sprintf(NSP_address_str,"%d.%d.%d.%d",NSP_address_bytes[0],NSP_address_bytes[1],NSP_address_bytes[2],NSP_address_bytes[3]);
    DBG("NSP: libNsdl NSP_ADDRESS: %s port: %d\r\n",NSP_address_str,nsp_port);
    set_NSP_address(NSP_address_bytes, nsp_port, SN_NSDL_ADDRESS_TYPE_IPV4);
    nsp.set_address(NSP_address_str,nsp_port);
}

// NSP event loop - spawn a re-registration thread AFTER we have initially registered and begun event processing...     
void nsdl_event_loop() {    
    sn_nsdl_addr_s received_packet_address; 
    Endpoint from;
    uint8_t nsp_received_address[4];
    char nsp_buffer[1024];

    memset(&received_packet_address, 0, sizeof(sn_nsdl_addr_s));
    memset(nsp_received_address, 0, sizeof(nsp_received_address));
    received_packet_address.addr_ptr = nsp_received_address;    
            
    // start the registration update thread.. it will wait a bit while the endpoint gins up...
    Thread registration_thread(registration_update_thread);
    
    // FOREVER: main loop for event processing  
    while(true) {        
        //DBG("NSP: waiting for data...\r\n");
        int n = server.receiveFrom(from,nsp_buffer,sizeof(nsp_buffer));

        //DBG("NSP: received %d bytes... processing..\r\n.",n);
        if (n >= 0) sn_nsdl_process_coap((uint8_t*)nsp_buffer,n,&received_packet_address);        
     }
}