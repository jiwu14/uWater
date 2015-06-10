/**
 * @file    Endpoint.h
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

#ifndef __CONNECTOR_ENDPOINT_H__
#define __CONNECTOR_ENDPOINT_H__

// Support for Logging/Debug output
#include "Logger.h"

// Options support
#include "Options.h"

// Connector namespace
namespace Connector {

/** Endpoint class
 */
class Endpoint
{

public:
    /**
    Default Constructor
    */
    Endpoint(const Logger *logger,const Options *ob);

    /**
    Copy Constructor
    @param ob input endpoint instance to deep copy
    */
    Endpoint(const Endpoint &ep);

    /**
    Destructor
    */
    virtual ~Endpoint();

    /**
    Register the endpoint with mbed Device Server
    */
    void register_endpoint();

    /**
    Plumb the lower RF network stack
    @param canActAsRouterNode input boolean indicating whether this node can act as a router node or not.
    */
    static void plumbNetwork(bool canActAsRouterNode = false);
    
    /**
    Initialize the endpoint's configuration and begin the endpoint's main even loop
    */
    static void start();

private:
    Logger         *m_logger;
    Options        *m_options;
    
    // access the logger
    Logger *logger();
};

} // namespace Connector

#endif // __CONNECTOR_ENDPOINT_H__
