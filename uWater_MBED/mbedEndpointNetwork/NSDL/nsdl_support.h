// Support functions for the NSDL library

#ifndef __NSDL_SUPPORT_H__
#define __NSDL_SUPPORT_H__

#include "mbed.h"
#include <stdint.h>

#include "sn_nsdl.h"
#include "sn_coap_header.h"
#include "sn_coap_protocol.h"
#include "sn_nsdl_lib.h"

#include "mbedConnectorInterface.h"

// ************************* MDS CONFIGURATION *********************************

extern uint8_t NSP_address_bytes[NSP_IP_ADDRESS_LENGTH];    // which MDS instance we want to bind to...
extern uint8_t endpoint_name[NODE_NAME_LENGTH];             // our NODE name
extern uint8_t domain_name[NSP_DOMAIN_LENGTH];              // our MDS domain name
extern int nsp_port;                                        // our MDS UDP port number
extern uint8_t ep_type[NSP_ENDPOINT_TYPE_LENGTH];           // our NODE type
extern uint8_t lifetime_ptr[NSP_LIFE_TIME_LENGTH];          // MDS lifetime

// ************************* MDS CONFIGURATION *********************************


#define MAIN_LOOP_SLEEP         2000

typedef uint8_t (*sn_grs_dyn_res_callback_t)(sn_coap_hdr_s *, sn_nsdl_addr_s *, sn_proto_info_s *);
typedef void (*sn_update_observation_t)(sn_coap_hdr_s *,sn_coap_hdr_s *);

// external methods
extern "C" void *nsdl_alloc(uint16_t size);
extern "C" void nsdl_free(void* ptr_to_free);
extern void nsdl_create_static_resource(sn_nsdl_resource_info_s *resource_structure, uint16_t pt_len, uint8_t *pt, uint16_t rpp_len, uint8_t *rpp_ptr, uint8_t *rsc, uint16_t rsc_len);
extern void nsdl_create_dynamic_resource(sn_nsdl_resource_info_s *resource_structure, uint16_t pt_len, uint8_t *pt, uint16_t rpp_len, uint8_t *rpp_ptr, uint8_t is_observable, sn_grs_dyn_res_callback_t callback_ptr, int access_right);
extern "C" sn_nsdl_ep_parameters_s* nsdl_init_register_endpoint(sn_nsdl_ep_parameters_s *endpoint_structure, uint8_t *domain, uint8_t* name, uint8_t* ypename_ptr, uint8_t *lifetime_ptr);
extern "C" void nsdl_clean_register_endpoint(sn_nsdl_ep_parameters_s **endpoint_structure);
extern "C" void nsdl_init();
extern "C" void nsdl_event_loop();
extern "C" void nsdl_reg_update();
extern "C" void configure_endpoint();
extern void NSP_registration();
extern "C" void register_endpoint(bool init);
extern void registration_update_thread(void const *args);
extern "C" void nsdl_set_nsp_address(void);
extern "C" bool nsdl_endpoint_is_registered(void);

#endif // __NSDL_SUPPORT_H__
