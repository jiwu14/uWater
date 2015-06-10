/**
 * @file    ResourceObserver.cpp
 * @brief   mbed CoAP DynamicResource observer (implementation)
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
 
 #include "ResourceObserver.h"
 
 // constructor
 ResourceObserver::ResourceObserver(DynamicResource *resource,int sleep_time) : m_is_observing(false), m_sleep_time(sleep_time) {
     this->m_resource = resource;
     if (resource != NULL) resource->setObserver(this);
 }
 
 // copy constructor
 ResourceObserver::ResourceObserver(const ResourceObserver &observer) {
     this->m_resource = observer.m_resource;
 }
 
 // destructor
 ResourceObserver::~ResourceObserver() {
 }
 
 // get our resource
 DynamicResource *ResourceObserver::getResource() {
     return this->m_resource;
 }
 
 // we are observing?
 bool ResourceObserver::isObserving() {
     return this->m_is_observing;
 }
 
 // set our observation state
 void ResourceObserver::setObserving(bool observing) {
     this->m_is_observing = observing;
 }
 
 // get our sleep time
 int ResourceObserver::getSleepTime() {
     return this->m_sleep_time;
 }