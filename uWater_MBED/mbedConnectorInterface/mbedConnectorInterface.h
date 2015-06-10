/**
 * @file    mbedConnectorInterface.h
 * @brief   mbed Connector Inteface configuration header file
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

#ifndef __MBED_CONNECTOR_INTERFACE_H__
#define __MBED_CONNECTOR_INTERFACE_H__

// Include specific NSP configuration details
#include "nsp_configuration.h"

/************** DEFAULT CONFIGURATION PARAMETERS  ************************/

// NSP Configuration
#define NSP_COAP_UDP_PORT        5683                                        // Default CoAP UDP port
#define NSP_LIFE_TIME_LENGTH     24                                          // length of the lifetime buffer string
#define NSP_LIFE_TIME            "120"                                       // liftime buffer (representing seconds)
#define NSP_RD_UPDATE_PERIOD     30000                                       // (in ms) - 30 seconds (1/4 of NSP_LIFE_TIME seconds)
#define NSP_TICKERUPDATE_PERIOD  30.0                                        // (float secs) - 30 seconds (used for Ticker-based re-registration periods)
#define NSP_DEFAULT_OBS_PERIOD   10000                                       // (in ms) - 10 seconds between observations..

// 6LowPAN Configuration
#define NODE_MAC_ADDRESS_LENGTH  8
#define NODE_MAC_ADDRESS         {0x00,0x00,0x06,0x02,0x00,0x00,0x36,0x18}
#define NODE_CHANNEL_LIST        0x07FFF800                                  // All channels

// DynamicResource Configuration
#define MAX_VALUE_BUFFER_LENGTH  128                                         // largest "value" a dynamic resource may assume as a string

// Instance Pointer Table Configuration
#define IPT_MAX_ENTRIES          5                                           // maximum number of unique pointers managed by the IPT (i.e. number of independent dynamic resources)

// Logger buffer size
#define LOGGER_BUFFER_LENGTH     300                                         // largest single print of a given debug line

// 802.15.4 Network ID and RF channel defaults
#define MESH_NETWORK_ID_LENGTH   32
#define MESH_DEF_NETWORK_ID      "Network000000000"
#define MESH_DEF_RF_CHANNEL      11


// WiFi Configuration
#define WIFI_SSID_LENGTH         128
#define WIFI_DEFAULT_SSID        "changeme"
#define WIFI_AUTH_KEY_LENGTH     128
#define WIFI_DEFAULT_AUTH_KEY    "changeme"

/************** DEFAULT CONFIGURATION PARAMETERS  ************************/

#endif // __MBED_CONNECTOR_INTERFACE___