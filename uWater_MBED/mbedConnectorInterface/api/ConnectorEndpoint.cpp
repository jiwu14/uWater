/**
 * @file    ConnectorEndpoint.cpp
 * @brief   mbed CoAP Endpoint base class
 * @author  Doug Anson/Chris Paola
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

#include "ConnectorEndpoint.h"

// lower level network stubs integration
#include "mbedEndpointNetworkStubs.h"

// Connector namespace
namespace Connector {

// STATIC: Plumb the network
void Endpoint::plumbNetwork(bool canActAsRouterNode) {
    // call into our network stubs to (pre-configure) plumb the network... 
    DBG("plumbNetwork: pre-configure plumb of network...\r\n");
    net_stubs_pre_plumb_network(canActAsRouterNode);
    
    // configure the endpoint now...
    DBG("plumbNetwork: configuring endpoint...\r\n");
    utils_configure_endpoint();   
    
    // call into our network stubs to (pre-configure) plumb the network... 
    DBG("plumbNetwork: post-configure plumb of network...\r\n");
    net_stubs_post_plumb_network(); 
}

// STATIC: Finalize the endpoint's configuration and begin the endpoint's main even loop (static, not tied into Logger)
void Endpoint::start()
{   
   // initialize our endpoint and register it
   DBG("Endpoint::start(): creating endpoint instance and registering with mDS...\r\n");
   utils_init_and_register_endpoint();
   
   // create the main loop plumbing for our lower network stack
   DBG("Endpoint::start(): creating main loop plumbing...\r\n");
   net_stubs_create_main_loop();
   
   // call into the lower network stubs to start event processing
   DBG("Endpoint::start(): beginning main event loop...\r\n");
   net_stubs_begin_main_loop();
}

// Constructor
Endpoint::Endpoint(const Logger *logger, const Options *options)
{
    this->m_logger = (Logger *)logger;
    this->m_options = (Options *)options;
}

// Copy Constructor
Endpoint::Endpoint(const Endpoint &ep)
{
    this->m_logger = ep.m_logger;
    this->m_options = ep.m_options;
}

// Destructor
Endpoint::~Endpoint()
{
}

// register the endpoint
void Endpoint::register_endpoint()
{    
    // Create the NSDL Resource Pointer...
    this->logger()->log("Endpoint::initialize(): initializing NSP resource pointer...");
    sn_nsdl_resource_info_s *resource_ptr = (sn_nsdl_resource_info_s*)nsdl_alloc(sizeof(sn_nsdl_resource_info_s));
    if(!resource_ptr) return;
    memset(resource_ptr, 0, sizeof(sn_nsdl_resource_info_s));

    resource_ptr->resource_parameters_ptr = (sn_nsdl_resource_parameters_s*)nsdl_alloc(sizeof(sn_nsdl_resource_parameters_s));
    if(!resource_ptr->resource_parameters_ptr) {
        nsdl_free(resource_ptr);
        return;
    }
    memset(resource_ptr->resource_parameters_ptr, 0, sizeof(sn_nsdl_resource_parameters_s));

    // Loop through Static Resources and bind each of them...
    this->logger()->log("Endpoint::initialize(): adding static resources...");
    const StaticResourcesList *static_resources = this->m_options->getStaticResourceList();
    for(int i=0; i<static_resources->size(); ++i) {
        this->logger()->log("Endpoint::initialize(): binding static resource: [%s]...",static_resources->at(i)->getName().c_str());
        static_resources->at(i)->bind(resource_ptr);
    }

    // Loop through Dynamic Resources and bind each of them...
    this->logger()->log("Endpoint::initialize(): adding dynamic resources...");
    const DynamicResourcesList *dynamic_resources = this->m_options->getDynamicResourceList();
    for(int i=0; i<dynamic_resources->size(); ++i) {
        this->logger()->log("Endpoint::initialize(): binding dynamic resource: [%s]...",dynamic_resources->at(i)->getName().c_str());
        dynamic_resources->at(i)->bind(resource_ptr);
    }

    // register the endpoint
    net_stubs_register_endpoint();

    // clean up
    nsdl_free(resource_ptr->resource_parameters_ptr);
    nsdl_free(resource_ptr);
}

// our logger
Logger *Endpoint::logger()
{
    return this->m_logger;
}

} // namespace Connector
