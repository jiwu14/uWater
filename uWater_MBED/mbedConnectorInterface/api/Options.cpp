/**
 * @file    Options.cpp
 * @brief   mbed CoAP Options (immutable OptionsBuilder instance) class implementation
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

#include "Options.h"

namespace Connector {

// default constructor
Options::Options()
{
}

// copy constructor
Options::Options(const Options &opt)
{
}

// destructors
Options::~Options()
{
}

// lifetime pointer
char *Options::getLifetime()
{
    return this->m_lifetime;
}

// NSP domain
string Options::getDomain()
{
    return this->m_domain;
}

// Endpoint name
string Options::getEndpointNodename()
{
    return this->m_node_name;
}

// Endpoint Type
string Options::getEndpointType()
{
    return this->m_endpoint_type;
}

// NSP Port number
int Options::getNSPPortNumber()
{
    return this->m_nsp_port;
}

// NODE Radio Channel List
uint32_t Options::getRadioChannelList()
{
    return this->m_channel_list;
}

// NSP Read update period
int Options::getReadUpdatePeriod()
{
    return this->m_rd_update_period;
}

// NSP Address
uint8_t *Options::getNSPAddress()
{
    return this->m_nsp_address;
}

// NODE MAC Address
uint8_t *Options::getMACAddress()
{
    return this->m_mac_address;
}

// Static Resources
StaticResourcesList *Options::getStaticResourceList()
{
    return &this->m_static_resources;
}

// Dynamic Resources
DynamicResourcesList *Options::getDynamicResourceList()
{
    return &this->m_dynamic_resources;
}

// WiFi SSID
string Options::getWiFiSSID() {
    return this->m_wifi_ssid;
}

// WiFi AuthType
WiFiAuthTypes Options::getWiFiAuthType() {
    return this->m_wifi_auth_type;
}

// WiFi AuthKey
string Options::getWiFiAuthKey() {
    return this->m_wifi_auth_key;
}

// 802.15.4 Network ID
string Options::getNetworkID() {
    return this->m_network_id;
}

// 802.15.4 Network ID
uint8_t Options::getRadioChannel() {
    return this->m_channel;
}

// Immediate Observationing Enabled
bool Options::immedateObservationEnabled() {
    return this->m_enable_immediate_observation;
}
    
// Enable/Disable Observation control via GET
bool Options::enableGETObservationControl() {
    return this->m_enable_get_obs_control;
}

} // namespace Connector
