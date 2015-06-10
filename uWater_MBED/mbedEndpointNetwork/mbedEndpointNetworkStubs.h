 /**
 * @file    mbedEndpointNetworkStubs.h
 * @brief   mbed Endpoint Network Stubs header - these must be implemented in any lower network layer interfacing with mbedConnectorInterface
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
 
 #ifndef __MBED_ENDPOINT_NETWORK_STUBS_H__
 #define __MBED_ENDPOINT_NETWORK_STUBS_H__
 
 #include "configuration.h"
 #include "nsdl_support.h"
 
 // we have to redefine DBG as its used differently here...
 #ifdef DBG
    #undef DBG
 #endif
 #define DBG  printf
 
 // Linkage to the lower network APIs and interfaces
 extern "C" void net_stubs_pre_plumb_network(bool canActAsRouterNode);      // before endpoint is configured...
 extern "C" void net_stubs_post_plumb_network(void);                        // after endpoint is configured...
 extern "C" void net_stubs_create_main_loop(void);
 extern "C" void net_stubs_register_endpoint();
 extern "C" void net_stubs_begin_main_loop(void);
 
 // Utils.cpp functions...
 extern void utils_configure_endpoint(void);
 extern void utils_init_and_register_endpoint(void);
 
 #endif // __MBED_ENDPOINT_NETWORK_STUBS_H__