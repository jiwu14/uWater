/**
 * @file    Utils.cpp
 * @brief   mbed CoAP Endpoint misc utils collection
 * @author  Doug Anson
 * @version 1.0
 * @see
 *
 * Copyright (c) 2014
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// mbed Endpoint includes
#include "ConnectorEndpoint.h"
#include "OptionsBuilder.h"

// External references (defined in main.cpp)
Connector::Options *configure_endpoint(Connector::OptionsBuilder &builder);
extern Logger logger;

// Our Endpoint
Connector::Endpoint *endpoint = NULL;

// Our Endpoint configured Options
Connector::OptionsBuilder config;
Connector::Options *options = NULL;

// ************************* NSDL Linkage - MDS CONFIGURATION (defaulted) *********************************

uint8_t NSP_address_bytes[NSP_IP_ADDRESS_LENGTH] = NSP_IP_ADDRESS;     // which MDS instance we want to bind to...
uint8_t endpoint_name[NODE_NAME_LENGTH] = NODE_NAME;                   // our NODE name
uint8_t domain_name[NSP_DOMAIN_LENGTH] = NSP_DOMAIN;                   // our MDS domain name
int nsp_port = NSP_COAP_UDP_PORT;                                      // our MDS UDP port
uint8_t ep_type[NSP_ENDPOINT_TYPE_LENGTH] = NSP_ENDPOINT_TYPE;         // our NODE type
uint8_t lifetime_ptr[NSP_LIFE_TIME_LENGTH] = { NSP_LIFE_TIME };        // NSDL lifetime
uint8_t app_MAC_address[NODE_MAC_ADDRESS_LENGTH] = NODE_MAC_ADDRESS;   // Node MAC address
uint32_t channel_list = NODE_CHANNEL_LIST;                             // Node RF Channel list

uint8_t wifi_ssid[WIFI_SSID_LENGTH];                                   // WiFi SSID
WiFiAuthTypes wifi_auth_type;                                          // WiFi Auth Type
uint8_t wifi_auth_key[WIFI_AUTH_KEY_LENGTH];                           // WiFi Auth Key

uint8_t mesh_network_id[MESH_NETWORK_ID_LENGTH] = MESH_DEF_NETWORK_ID; // 802.15.4 Network ID (6LowPAN)
uint8_t rf_channel = MESH_DEF_RF_CHANNEL;                              // 802.15.4 RF Channel (6LowPAN)

// ************************* NSDL Linkage - MDS CONFIGURATION (defaulted)  *********************************


// further simplifies the endpoint main() configuration by removing the final initialization details of the endpoint...
void utils_configure_endpoint()
{    
    // NSP/NSDL default configuration - see mbedConnectorInterface.h for definitions...
    logger.log("utils_configure_endpoint: setting defaults...");
    config.setNSPAddress(NSP_address_bytes);
    config.setNSPPortNumber(NSP_COAP_UDP_PORT);
    config.setDomain(NSP_DOMAIN);
    config.setEndpointNodename(NODE_NAME);
    config.setEndpointType(NSP_ENDPOINT_TYPE);
    config.setLifetime(NSP_LIFE_TIME);
    
    // Node default configuration - see mbedConnectorInterface.h for definitions...
    config.setRadioChannelList(NODE_CHANNEL_LIST);
    config.setReadUpdatePeriod(NSP_RD_UPDATE_PERIOD);
    config.setEndpointNodename(NODE_NAME); 
    config.setMACAddress(app_MAC_address);   // TODO: arm_ns_tasklet_create() should call Endpoint::plumbNetwork()... currently its called before this MAC address can be (re)set
    
    // WiFi defaults
    config.setWiFiSSID(WIFI_DEFAULT_SSID);          // default: changeme
    config.setWiFiAuthType(WIFI_WPA_PERSONAL);      // default: WPA Personal
    config.setWiFiAuthKey(WIFI_DEFAULT_AUTH_KEY);   // default: changeme
    
    // 802.15.4 defaults (6LowPAN)
    config.setNetworkID((char *)mesh_network_id);
    config.setRadioChannel((int)mesh_network_id);
    
    // Establish default CoAP observation behavior
    config.setImmedateObservationEnabled(false);    // default: false (per CoAP spec)
    
    // Establish default CoAP GET-based observation control behavior
    config.setEnableGETObservationControl(true);    // default: true (CoAP spec)
    
    // main.cpp can override or change any of the above defaults...
    logger.log("utils_configure_endpoint: gathering configuration overrides...");
    options = configure_endpoint(config);
        
    // with options, lets set the underlying NSDL globals...
    logger.log("utils_configure_endpoint: finalizing configuration...");
    memcpy(NSP_address_bytes,options->getNSPAddress(),NSP_IP_ADDRESS_LENGTH);
    memset(endpoint_name,0,NODE_NAME_LENGTH);
    memcpy(endpoint_name,options->getEndpointNodename().c_str(),options->getEndpointNodename().size());
    memset(domain_name,0,NSP_DOMAIN_LENGTH);
    memcpy(domain_name,options->getDomain().c_str(),options->getDomain().size());
    nsp_port = options->getNSPPortNumber();
    memset(ep_type,0,NSP_ENDPOINT_TYPE_LENGTH);
    memcpy(ep_type,options->getEndpointType().c_str(),options->getEndpointType().size());
    memcpy(lifetime_ptr,options->getLifetime(),NSP_LIFE_TIME_LENGTH);
    memcpy(app_MAC_address,options->getMACAddress(),NODE_MAC_ADDRESS_LENGTH); // TODO: arm_ns_tasklet_create() should call Endpoint::plumbNetwork()... currently its called before this MAC address can be (re)set
    channel_list = options->getRadioChannelList();
    
    // WiFi Configration
    memcpy(wifi_ssid,options->getWiFiSSID().c_str(),options->getWiFiSSID().size());
    wifi_auth_type = options->getWiFiAuthType();
    memcpy(wifi_auth_key,options->getWiFiAuthKey().c_str(),options->getWiFiAuthKey().size());
    
    // 802.15.4 Configuration
    memcpy(mesh_network_id,options->getNetworkID().c_str(),options->getNetworkID().size());
    rf_channel = options->getRadioChannel();

    // DONE
    logger.log("utils_configure_endpoint: endpoint configuration completed.");
}

// initialize and register the endpoint and its resources
void utils_init_and_register_endpoint(void) 
{
    // initialize NSDL
    logger.log("net_stubs_post_plumb_network: initializing NSP..\r\n.");
    nsdl_init();
    nsdl_set_nsp_address();

    // alloc Endpoint
    logger.log("utils_init_and_register_endpoint: allocating endpoint instance...");
    if (endpoint == NULL) endpoint = new Connector::Endpoint(&logger,options);

    // initialize Endpoint resources
    logger.log("utils_init_and_register_endpoint: registering endpoint and its resources...");
    endpoint->register_endpoint();
}
