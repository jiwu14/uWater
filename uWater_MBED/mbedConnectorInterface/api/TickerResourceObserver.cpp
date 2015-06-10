/**
 * @file    TickerResourceObserver.cpp
 * @brief   mbed CoAP DynamicResource Ticker-based observer (implementation)
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
 
 #include "TickerResourceObserver.h"
 
 // DEBUG
 //DigitalOut __ticker_led(LED2);
 
 // determines whether the mDS endpoint has been registered or not...
 extern "C" bool nsdl_endpoint_is_registered(void);
 
 // constructor
 TickerResourceObserver::TickerResourceObserver(DynamicResource *resource,int sleep_time) : 
                                    ResourceObserver(resource,(int)(sleep_time/1000)) {
     this->setObserving(false);
     // DEBUG
     std::printf("TickerResourceObserver being used for %s (sleep_time=%d)\r\n",resource->getName().c_str(),sleep_time);
 }
  
 // destructor
 TickerResourceObserver::~TickerResourceObserver() {
     this->stopObservation();
 }

 // notifier
 void TickerResourceObserver::observationNotifier() {
     if (this->isObserving() == true && this->getResource() != NULL && nsdl_endpoint_is_registered() == true) {
         this->getResource()->observe();
         //__ticker_led = !__ticker_led;
     }
 }
 
 // begin observing...
 void TickerResourceObserver::beginObservation() {
     if (this->isObserving() == false) {
        this->m_ticker.attach(this,&TickerResourceObserver::observationNotifier,(float)this->getSleepTime());
        this->setObserving(true);
     }
 }
 
 // begin observing...
 void TickerResourceObserver::stopObservation() {
     this->setObserving(false);
 }