/**
 * @file    ThreadedResourceObserver.cpp
 * @brief   mbed CoAP DynamicResource Thread-based observer (implementation)
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
 
 #include "ThreadedResourceObserver.h"
 
 #ifdef CONNECTOR_USING_THREADS
 // DEBUG
 //DigitalOut __threaded_led(LED2);
 #endif
 
 // constructor
 ThreadedResourceObserver::ThreadedResourceObserver(DynamicResource *resource,int sleep_time) : 
                                                            ResourceObserver(resource,sleep_time) 
 #ifdef CONNECTOR_USING_THREADS
                                                            ,m_observation_thread(&ThreadedResourceObserver::_observation_notifier,this) 
 #endif 
                                                            {
        this->setObserving(false);
        // DEBUG
        std::printf("ThreadedResourceObserver being used for %s (sleep_time=%d)\r\n",resource->getName().c_str(),sleep_time);
 }
 
 // destructor
 ThreadedResourceObserver::~ThreadedResourceObserver() {
     this->stopObservation();
 #ifdef CONNECTOR_USING_THREADS
     this->m_observation_thread.terminate();
 #endif
 }
 
 // notifier
 void ThreadedResourceObserver::_observation_notifier(void const *instance) {
 #ifdef CONNECTOR_USING_THREADS
     ThreadedResourceObserver *me = (ThreadedResourceObserver *)instance;
     while(true) {
         Thread::wait(me->getSleepTime());
         if (me->isObserving() == true && me->getResource() != NULL && nsdl_endpoint_is_registered() == true) {
             me->getResource()->observe();
             //__threaded_led = !__threaded_led;
         }
     }
 #endif
 }

 // begin observing...
 void ThreadedResourceObserver::beginObservation() {
     this->setObserving(true);
 }
 
 // stop observing...
 void ThreadedResourceObserver::stopObservation() {
     this->setObserving(false);
 }