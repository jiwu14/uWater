/**
 * @file    main.cpp
 * @brief   mbed Connected Home Endpoint main entry point
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

// mbed Connector Interface (configuration)
#include "mbedConnectorInterface.h"

// Ethernet Interface
#include "EthernetInterface.h"
EthernetInterface ethernet;

// mbed Connector Endpoint includes
#include "ConnectorEndpoint.h"
#include "OptionsBuilder.h"

// USB Serial port access for debugging/logging
RawSerial pc(USBTX,USBRX);

// Logging facility
Logger logger(&pc);

// Static Resources
#include "StaticResource.h"
StaticResource mfg(&logger,"3/0/0","Freescale");
StaticResource model(&logger,"3/0/1","K64F mbed WateringBoard");

//
// Dynamic Resource Note:
//
//  mbedConnectorInterface supports up to IPT_MAX_ENTRIES 
//  (currently 5) independent dynamic resources.
//
//  You can increase this (at the cost of memory) 
//  in mbedConnectorinterface.h
//

// Light Resource
//#include "LightResource.h"
//LightResource light(&logger,"3311/0/5706");

// LED Resource
#include "OnBoardLED.h"
LEDResource led(&logger,"3311/1/5706");

// SLide control Resource
//#include "SliderResource.h"
//SliderResource slider(&logger,"3202/0/5600", true); /* true if observable */

// Moisture Resource
#include "MoistureResource.h"
MoistureResource moisture(&logger, "3304/0/5700", true); /* true for observable */

// Relay Resource
#include "RelayResource.h"
RelayResource relay(&logger, "3201/0/5550", true); /* true for observable */

// Set our own unique endpoint name
#define MY_ENDPOINT_NAME                       "WateringBoard"

// My NSP Domain
#define MY_NSP_DOMAIN                          "water"                               

// Customization Example: My custom NSP IPv4 or IPv6 address and NSP CoAP port 
//uint8_t my_nsp_address[NSP_IP_ADDRESS_LENGTH] = {192,168,1,199}; /* local */
uint8_t my_nsp_address[NSP_IP_ADDRESS_LENGTH] = {54,191,98,247}; /* smartobjectservice.com */
int my_nsp_coap_port                          = 5683;

// called from the Endpoint::start() below to create resources and the endpoint internals...
Connector::Options *configure_endpoint(Connector::OptionsBuilder &config)
{
    // Build the endpoint configuration parameters
    logger.log("configure_endpoint: building endpoint configuration...");
    //slider.setMaxAge(0); /* MaxAge = 0 to disable caching of the slide value in the Device Server */
    moisture.setMaxAge(0);
    relay.setMaxAge(0);
    return config.setEndpointNodename(MY_ENDPOINT_NAME)                   // custom endpoint name
                 .setNSPAddress(my_nsp_address)                           // custom NSP address
                 .setDomain(MY_NSP_DOMAIN)                                // custom NSP domain
                 .setNSPPortNumber(my_nsp_coap_port)                      // custom NSP CoAP port
                 
                 // add the static resource representing this endpoint
                 .addResource(&mfg)
                 .addResource(&model)
                                    
                 // Add my specific physical dynamic resources...
                 //.addResource(&light)
                 //.addResource(&slider, 10000)
                 .addResource(&led)
                 .addResource(&moisture, 10000)
                 .addResource(&relay)
                   
                 // finalize the configuration...
                 .build();
}

// main entry point...
int main()
{
    // Announce
    logger.log("\r\n\r\nmbed mDS Sample Endpoint v1.0 (Ethernet)");

    // we have to plumb our network first
    Connector::Endpoint::plumbNetwork();
     
    // starts the endpoint by finalizing its configuration (configure_endpoint() above called),creating a Thread and reading NSP events...
    logger.log("Start the endpoint to finish setup and enter the main loop...");
    Connector::Endpoint::start();
}
