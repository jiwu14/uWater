/**
 * @file    OptionsBuilder.h
 * @brief   mbed CoAP OptionsBuilder class header
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

#ifndef __OPTIONS_BUILDER_H__
#define __OPTIONS_BUILDER_H__

// base class support
#include "Options.h"

// Connector namespace
namespace Connector {

/** OptionsBuilder class
 */
class OptionsBuilder : Options
{
public:
    /**
    Default Constructor
    */
    OptionsBuilder();

    /**
    Copy Constructor
    @param ob input options builder instance to deep copy
    */
    OptionsBuilder(const OptionsBuilder &ob);

    /**
    Destructor
    */
    virtual ~OptionsBuilder();

    /**
    Set the NSDL Endpoint Lifetime
    @param lifetime input the NSDL endpoint lifetime (seconds)
    @return instance to ourself
    */
    OptionsBuilder &setLifetime(const char *lifetime);

    /**
    Set the NSDL Domain
    @param domain input the NSDL domain to set
    @return instance to ourself
    */
    OptionsBuilder &setDomain(const char *domain);

    /**
    Set the Endpoint Node Name
    @param node_name input the node endpoint name
    @return instance to ourself
    */
    OptionsBuilder &setEndpointNodename(const char *node_name);

    /**
    Set the NSDL Endpoint Type
    @param endpoint_type input the NSDL endpoint type
    @return instance to ourself
    */
    OptionsBuilder &setEndpointType(const char *endpoint_type);

    /**
    Set the NSDL Port Number
    @param port_num input the NSDL port number
    @return instance to ourself
    */
    OptionsBuilder &setNSPPortNumber(const int port_num);

    /**
    Set the underlying radio stack channel list
    @param channel_list input the radio channel list
    @return instance to ourself
    */
    OptionsBuilder &setRadioChannelList(const uint32_t channel_list);

    /**
    Set the NSDL Read Update Period
    @param rd_update_period_ms input the NSDL read update period (in ms)
    @return instance to ourself
    */
    OptionsBuilder &setReadUpdatePeriod(const int rd_update_period_ms);

    /**
    Set the NSP IPv6 Address
    @param nsp_address input the NSP IPv6 address
    @param nsp_address_length input the length of the NSP IPv6 address buffer
    @return instance to ourself
    */
    OptionsBuilder &setNSPAddress(const uint8_t *nsp_address,const int nsp_address_length = NSP_IP_ADDRESS_LENGTH);

    /**
    Set the MAC address
    @param mac_address input the MAC address buffer
    @param mac_address_length input the MAC address buffer length
    @return instance to ourself
    */
    OptionsBuilder &setMACAddress(const uint8_t *mac_address,const int mac_address_length = NODE_MAC_ADDRESS_LENGTH);

    /**
    Add a NSDL endpoint resource (static)
    @param static_resource input the NSDL static resource
    @return instance to ourself
    */
    OptionsBuilder &addResource(const StaticResource *static_resource);
    
    /**
    Add a NSDL endpoint resource (dynamic)
    @param dynamic_resource input the NSDL dynamic resource
    */
    OptionsBuilder &addResource(const DynamicResource *dynamic_resource);
    
    /**
    Add a NSDL endpoint resource (dynamic)
    @param dynamic_resource input the NSDL dynamic resource
    @param use_observer input if true, use an appropriate ResourceObserver to observer. if false, the underlying resource will handle it 
    @return instance to ourself
    */
    OptionsBuilder &addResource(const DynamicResource *dynamic_resource,const bool use_observer);

    /**
    Add a NSDL endpoint resource (dynamic)
    @param dynamic_resource input the NSDL dynamic resource
    @param sleep_time input the observation sleep time in milliseconds (for observable resource only)
    @return instance to ourself
    */
    OptionsBuilder &addResource(const DynamicResource *dynamic_resource,const int sleep_time);
    
    /**
    Add a NSDL endpoint resource (dynamic)
    @param dynamic_resource input the NSDL dynamic resource
    @param sleep_time input the observation sleep time in milliseconds (for observable resource only)
    @param use_observer input if true, use an appropriate ResourceObserver to observer. if false, the underlying resource will handle it 
    @return instance to ourself
    */
    OptionsBuilder &addResource(const DynamicResource *dynamic_resource,const int sleep_time,const bool use_observer);

    /**
    Set the WiFi SSID
    @param ssid input the WiFi SSID
    */
    OptionsBuilder &setWiFiSSID(char *ssid);
    
    /**
    Set the WiFi AuthType
    @param auth_type input the WiFi AuthType
    */
    OptionsBuilder &setWiFiAuthType(WiFiAuthTypes auth_type);
    
    /**
    Set the WiFi AuthKey
    @param auth_key input the WiFi AuthKey
    */
    OptionsBuilder &setWiFiAuthKey(char *auth_key);
    
    /**
    Set the 802.15.4 Network ID
    @param network_id input the 802.15.4 mesh Network ID
    */
    OptionsBuilder &setNetworkID(char *network_id);
    
    /**
    Set the 802.15.4 Radio Channel
    @param channel input the 802.15.4 radio channel
    */
    OptionsBuilder &setRadioChannel(int channel);
    
    /** 
    Enable/Disable immediate observationing
    @param enable input enable immediate observationing without GET 
    */
    OptionsBuilder &setImmedateObservationEnabled(bool enable);
    
    /** 
    Enable/Disable GET-based control of observations
    @param enable input enable GET-based observation enable/disable control
    */
    OptionsBuilder &setEnableGETObservationControl(bool enable);
    
    /**
    Build our our immutable self
    */
    Options *build();

};

} // namespace Connector

#endif // __OPTIONS_BUILDER_H__
