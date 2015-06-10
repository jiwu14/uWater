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

#ifndef __STATIC_RESOURCE_H__
#define __STATIC_RESOURCE_H__

// Base Class
#include "Resource.h"

// String class support
#include <string>

// DataWrapper support
#include "DataWrapper.h"

/** StaticResource is a static (GET only) resource with a value type pinned as a string type
 */
class StaticResource : public Resource<string>
{
public:
    /**
    Default constructor
    @param logger input logger instance for this resource
    @param name input the Resource URI/Name
    @param value input the Resource value (a string)
    */
    StaticResource(const Logger *logger,const char *name,const char *value);

    /**
    string value constructor
    @param logger input logger instance for this resource
    @param name input the Resource URI/Name
    @param value input the Resource value (a string)
    */
    StaticResource(const Logger *logger,const char *name,const string value);

    /**
    constructor with buffer lengths
    @param logger input logger instance for this resource
    @param name input the Resource URI/Name
    #param name_length input the length of the Resource URI/Name
    @param value input the Resource value (or NULL)
    */
    StaticResource(const Logger *logger,const string name,const string value);

    /**
    Copy constructor
    @param resource input the StaticResource that is to be deep copied
    */
    StaticResource(const StaticResource &resource);

    /**
    Destructor
    */
    virtual ~StaticResource();

    /**
    Bind resource to endpoint
    @param p input pointer to the endpoint resources necessary for binding
    */
    virtual void bind(void *p);
    
    /**
    Set the data wrapper
    @param data_wrapper input the data wrapper instance
    */
    void setDataWrapper(DataWrapper *data_wrapper) { this->m_data_wrapper = data_wrapper; }

protected:
    DataWrapper *getDataWrapper() { return this->m_data_wrapper; }

private:
    DataWrapper *m_data_wrapper;
};

#endif // __STATIC_RESOURCE_H__
