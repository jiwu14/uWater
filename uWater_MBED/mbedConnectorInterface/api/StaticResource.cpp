/**
 * @file    StaticResource.h
 * @brief   mbed CoAP Endpoint Static Resource class
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

#include "StaticResource.h"

// NSDL libraries
#include "nsdl_support.h"

// Constructor
StaticResource::StaticResource(const Logger *logger,const char *name, const char *value) : Resource<string>(logger,string(name),string(value)), m_data_wrapper()
{
}

// Constructor
StaticResource::StaticResource(const Logger *logger,const char *name,const string value) : Resource<string>(logger,string(name),string(value))
{
    this->m_data_wrapper = NULL;
}

// Constructor with buffer lengths
StaticResource::StaticResource(const Logger *logger,const string name,const string value) : Resource<string>(logger,string(name),string(value))
{
    this->m_data_wrapper = NULL;
}

// Copy constructor
StaticResource::StaticResource(const StaticResource &resource) : Resource<string>((const Resource<string> &)resource)
{
    this->m_data_wrapper = resource.m_data_wrapper;
}

// Destructor
StaticResource::~StaticResource()
{
}

// Bind resource to Endpoint
void StaticResource::bind(void *p)
{
    if (p != NULL) {
        sn_nsdl_resource_info_s *resource_ptr = (sn_nsdl_resource_info_s *)p;
        const uint8_t *name = (const uint8_t *)(this->getName().c_str());
        int name_length = this->getName().size();
        
        // do we wrap the data?
        if (this->getDataWrapper() != NULL) {
            // wrap the data...
            this->getDataWrapper()->wrap((uint8_t *)this->getValue().c_str(),(int)this->getValue().size());
            nsdl_create_static_resource(resource_ptr,name_length,(uint8_t *)name,0,0,this->getDataWrapper()->get(),this->getDataWrapper()->length());
            this->logger()->log("StaticResource: [%s] value: [%s] bound",name,this->getDataWrapper()->get());
        }
        else {
            // do not wrap the data...
            int value_length = this->getValue().size();
            const uint8_t *value = (const uint8_t *)(this->getValue().c_str());
            nsdl_create_static_resource(resource_ptr,name_length,(uint8_t *)name,0,0,(uint8_t *)value,value_length);
            this->logger()->log("StaticResource: [%s] value: [%s] bound",name,value);
        }
    } else {
        this->logger()->log("StaticResource: NULL parameter in bind()");
    }
}
