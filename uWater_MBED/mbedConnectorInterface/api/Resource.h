/**
 * @file    Resource.h
 * @brief   mbed CoAP Endpoint Resource base class template
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

#ifndef __RESOURCE_H__
#define __RESOURCE_H__

// logging facility
#include "Logger.h"

// string support
#include <string>

/** Resource class
 */
template <typename InnerType> class Resource
{
public:
    /**
    Default constructor
    @param logger input the Logger instance this Resource is a part of
    @param name input the Resource URI/Name
    @param value input the Resource value
    */
    Resource(const Logger *logger,const string name,InnerType value)  {
        this->init(logger);
        this->m_name = name;
        this->m_value = value;
        this->m_implements_observation = false;
    }

    /**
    Copy constructor
    @param resource input the Resource that is to be deep copied
    */
    Resource(const Resource<InnerType> &resource) {
        this->init(resource.m_logger);
        this->m_endpoint = resource.m_endpoint;
        this->m_name = resource.m_name;
        this->m_value = resource.m_value;
        this->m_implements_observation = resource.m_implements_observation;
    }

    /**
    Destructor
    */
    virtual ~Resource() {
    }

    /**
    Get the resource name
    @return the name of the resource
    */
    string getName() {
        return this->m_name;
    }

    /**
    Get the resource value
    @return the value of the resource
    */
    InnerType getValue() {
        return this->m_value;
    }

    /**
    Set the resource name
    @param name input the resource name
    */
    void setName(const string name) {
        this->m_name = name;
    }

    /**
    Set the resource value
    @param value input the resource value
    */
    void setValue(const InnerType value) {
        this->m_value = value;
    }

    /**
    Bind resource to endpoint
    */
    virtual void bind(void *p) = 0;

    // access the logger()
    Logger *logger() {
        return this->m_logger;
    }
    
    /**
    set the options 
    */
    void setOptions(const void *options) { 
        this->m_options = (void *)options; 
    }
    
    // this resource implements its own observation handler
    bool implementsObservation() { return this->m_implements_observation; }

protected:
    // initialize internals to Resource
    void init(const Logger *logger) {
        this->m_logger = (Logger *)logger;
        this->m_endpoint = NULL;
        this->m_name = "";
        this->m_value = "";
    }
    
    // get our options
    void *getOptions() { 
        return this->m_options; 
    }
    
    Logger      *m_logger;
    void        *m_endpoint;
    string       m_name;
    InnerType    m_value;
    bool         m_implements_observation;
    void        *m_options;
};

#endif // __RESOURCE_H__
