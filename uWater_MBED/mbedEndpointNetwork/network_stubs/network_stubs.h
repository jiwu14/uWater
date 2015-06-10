/**
 * @file    network_stubs.h
 * @brief   mbed Endpoint Network Stubs header (Ethernet)
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
#ifndef __ETHERNET_STUBS_H__
#define __ETHERNET_STUBS_H__

// mbed support
#include "mbed.h"

// NSP support
#include "nsdl_support.h"

// Ethernet Interface
#include "EthernetInterface.h"
extern EthernetInterface ethernet;

// configure the endpoint
extern void configure_endpoint();

// we have to redefine DBG as its used differently here...
#ifdef DBG
    #undef DBG
#endif
#define DBG  printf

#endif // __ETHERNET_STUBS_H__