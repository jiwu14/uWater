/**
 * @file    DataWrapper.h
 * @brief   mbed CoAP Endpoint Data Wrapper class (header)
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

#ifndef __DATA_WRAPPER_H__
#define __DATA_WRAPPER_H__

// mbed support
#include "mbed.h"

class DataWrapper {
    public:
        /**
        Default constructor
        @param data input the buffer to use for operations
        @param data_length input the data length
        */
        DataWrapper(uint8_t *data,int data_length);
        
        /**
        Default constructor (alloc)
        @param data_length input the data length (alloc)
        */
        DataWrapper(int data_length);
        
        /**
        Default copy constructor
        @param data input the DataWrapper to copy
        */
        DataWrapper(const DataWrapper &data);
        
        /**
        Destructor
        */
        virtual ~DataWrapper();
        
        /**
        Wrap the data (trivial in base class)
        @param data input the data to wrap
        @param data_length input the length of the data to wrap
        */
        virtual void wrap(uint8_t *data,int data_length);
        
        /**
        Unwrap the data (trivial in base class)
        @param data input the data to unwrap
        @param data_length input the length of the data to unwrap
        */
        virtual void unwrap(uint8_t *data,int data_length);
        
        /**
        Get the wrap/unwrap result
        @return pointer to the data buffer of DataWrapper containing the wrap/unwrap result
        */
        uint8_t *get() { return this->m_data; }
        
        /**
        Get the wrap/unwrap result length
        @return length of the wrap/unwrap data result
        */
        int length() { return this->m_data_length; }
        
        /**
        Reset the wrapper
        */
        void reset();
        
        /**
        Set the new application key
        @param appkey input the new appkey (encrypted) to set
        @param appkey_length input the new appkey (encrypted) length
        */
        virtual void setAppKey(uint8_t *appkey,int appkey_length);
        
    protected:
        uint8_t *m_data;
        
    private:
        bool     m_alloced;
        int      m_data_length;
        int      m_data_length_max;
};

#endif // __DATA_WRAPPER_H__