/**
 * @file    nsp_configuration.h
 * @brief   mbed Connector Interface NSP configuration header
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
 
 #ifndef __NSP_CONFIGURATION_H__
 #define __NSP_CONFIGURATION_H__
 
 // NSP node name
 #define NODE_NAME_LENGTH         24
 #define NODE_NAME                "mbed-eth-endpoint"
 
 // NSP Address (4 bytes for IPV4, 16 bytes for IPV6)
 #define NSP_IP_ADDRESS_LENGTH    4
 #define NSP_IP_ADDRESS           {192,168,1,199}
 
 // NSP Endpoint Type specification
 #define NSP_ENDPOINT_TYPE_LENGTH 24
 #define NSP_ENDPOINT_TYPE        "mbed-eth-device"
 
 // NSP Domain used
 #define NSP_DOMAIN_LENGTH        24
 #define NSP_DOMAIN               "domain"

 #endif // __NSP_CONFIGURATION_H__