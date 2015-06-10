/**
 * @file    network_stubs.cpp
 * @brief   mbed Endpoint network stubs implementation (Ethernet)
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
 
#include "network_stubs.h"

extern "C" {
    
// plumb out the network
void net_stubs_pre_plumb_network(bool canActAsRouterNode) 
{
    // we have to defer all Ethernet until we are configured..
    ;
}

// called after the endpoint is configured...
void net_stubs_post_plumb_network(void) 
{
     // ethernet initialize
     ethernet.init();       // DHCP
     ethernet.connect();    // connect
     
     // our IP address
     DBG("net_stubs_post_plumb_network: Ethernet Address: %s\r\n",ethernet.getIPAddress());
}

// create a suitable main event loop for this specific network
void net_stubs_create_main_loop(void)
{
   // nothing to do for Ethernet endpoints - we are using the Threaded loop in nsdl_support.cpp
   ; 
}

// register the endpoint
void net_stubs_register_endpoint(void)
{
    // NSP registration
    DBG("net_stubs_register_endpoint: calling NSP registration...\r\n");
    register_endpoint(true);
    DBG("net_stubs_register_endpoint: NSP registration completed\r\n");
}

// begin the main loop for processing network events
void net_stubs_begin_main_loop(void) 
{
    // NDSL main loop
    nsdl_event_loop();
}

}
