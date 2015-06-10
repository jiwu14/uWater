/**
 * @file    ThreadedResourceObserver.h
 * @brief   mbed CoAP DynamicResource Thread-based observer (header)
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

#ifndef __THREADED_RESOURCE_OBSERVER_H__
#define __THREADED_RESOURCE_OBSERVER_H__

// mbed support
#include "mbed.h"

// switch for proper resource observer selection (from mbedEndpointNetwork)
#include "configuration.h"

// mbedConnectorInterface configuration
#include "mbedConnectorInterface.h"

// Thread support
#ifdef CONNECTOR_USING_THREADS
    #include "rtos.h"
#endif

// Base class support
#include "ResourceObserver.h"

class ThreadedResourceObserver : public ResourceObserver {
    public:
        /**
        Default Constructor
        @param resource input the resource to observe
        @param sleep_time input the time for the observation thread to sleep (in ms)
        */
        ThreadedResourceObserver(DynamicResource *resource,int sleep_time = NSP_DEFAULT_OBS_PERIOD);
                
        /**
        Destructor
        */
        virtual ~ThreadedResourceObserver();
        
        /**
        begin the observation
        */
        virtual void beginObservation();
        
        /**
        stop the observation
        */
        virtual void stopObservation();
        
        /**
        thread invoke function (static)
        */
        static void _observation_notifier(void const *instance);
        
    private:
#ifdef CONNECTOR_USING_THREADS 
        Thread  m_observation_thread;
#endif
};

#endif // __THREADED_RESOURCE_OBSERVER_H__