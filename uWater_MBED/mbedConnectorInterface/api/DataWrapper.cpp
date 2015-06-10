/**
 * @file    DynamicResource.h
 * @brief   mbed CoAP Endpoint Dynamic Resource class (header)
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
 
 #include "DataWrapper.h"
 
 // constructor
 DataWrapper::DataWrapper(uint8_t *data,int data_length) {
     this->m_data = data;
     this->m_data_length = 0;
     this->m_data_length_max = data_length;
     this->m_alloced = false;
     this->reset();
 }
 
 // constructor (alloc)
 DataWrapper::DataWrapper(int data_length) {
     this->m_data = (uint8_t *)malloc(data_length+1);
     memset(this->m_data,0,data_length+1);
     this->m_data_length = 0;
     this->m_data_length_max = data_length;
     this->m_alloced = true;
 }
 
 // copy constructor
 DataWrapper::DataWrapper(const DataWrapper &data) {
     this->m_data = data.m_data;
     this->m_data_length = data.m_data_length;
     this->m_data_length_max = data.m_data_length_max;
     this->m_alloced = data.m_alloced;
 }
 
 // destructor
 DataWrapper::~DataWrapper() {
     if (this->m_alloced && this->m_data != NULL) free(this->m_data);
 }
 
 // wrap
 void DataWrapper::wrap(uint8_t *data,int data_length) {
     this->reset();
     if (data != NULL && data_length > 0) {
        int length = data_length;
        if (length > this->m_data_length_max) length = this->m_data_length_max;
        memcpy(this->m_data,data,length);
        this->m_data_length = length;
     }
 }
 
 // unwrap       
 void DataWrapper::unwrap(uint8_t *data,int data_length) {
     this->reset();
     if (data != NULL && data_length > 0) {
        int length = data_length;
        if (length > this->m_data_length_max) length = this->m_data_length_max;
        memcpy(this->m_data,data,length);
        this->m_data_length = length;
     }
 }

 // reset 
 void DataWrapper::reset() {
     if (this->m_data != NULL && this->m_data_length_max > 0)
        memset(this->m_data,0,this->m_data_length_max);
     this->m_data_length = 0;
 }
 
 // set the app key
 void DataWrapper::setAppKey(uint8_t *appkey,int appkey_length) {
     // do nothing in the base class
     ;
 }

