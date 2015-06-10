/**
 * @file    TickerResourceObserver.h
 * @brief   mbed CoAP DynamicResource Ticker-based observer (header)
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

#ifndef __TICKER_RESOURCE_OBSERVER_H__
#define __TICKER_RESOURCE_OBSERVER_H__

// mbed support
#include "mbed.h"

// switch for proper resource observer selection (from mbedEndpointNetwork)
#include "configuration.h"

// mbedConnectorInterface configuration
#include "mbedConnectorInterface.h"

// Base class support
#include "ResourceObserver.h"

class TickerResourceObserver : public ResourceObserver {
    public:
        /**
        Default Constructor
        @param resource input the resource to observe
        @param timer_id input the id for our timer (can be index value of each resource that is observed...)
        @param sleep_time input the time for the observation tasklet to sleep (in whole seconds...)
        */
        TickerResourceObserver(DynamicResource *resource,int sleep_time = NSP_DEFAULT_OBS_PERIOD);
        
        /**
        Copy Constructor
        */
        TickerResourceObserver(const TickerResourceObserver &observer);
        
        /**
        Destructor
        */
        virtual ~TickerResourceObserver();
        
        /**
        begin the observation
        */
        virtual void beginObservation();
        
        /**
        stop the observation
        */
        virtual void stopObservation();
                     
        /**
        tasklet invoke function (static)
        */
        void observationNotifier(void);
    
    private:
        Ticker m_ticker;
};

#endif // __TICKER_RESOURCE_OBSERVER_H__