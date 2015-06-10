/**
 * @file    ResourceObserver.h
 * @brief   mbed CoAP DynamicResource observer (header)
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

#ifndef __RESOURCE_OBSERVER_H__
#define __RESOURCE_OBSERVER_H__

// DynamicResource
#include "DynamicResource.h"

class ResourceObserver {
    public:
        /**
        Default Constructor
        @param resource input the resource to observe
        @param sleep_time input the amount of time to sleep between observations
        */
        ResourceObserver(DynamicResource *resource,int sleep_time);
        
        /**
        Copy Constructor
        */
        ResourceObserver(const ResourceObserver &observer);
        
        /**
        Destructor
        */
        virtual ~ResourceObserver();
        
        /**
        begin the observation (ABSTRACT)
        */
        virtual void beginObservation() = 0;
        
        /**
        stop the observation (ABSTRACT)
        */
        virtual void stopObservation() = 0;
    
        /** 
        we are observing?
        */
        bool isObserving();
        
        /**
        get our sleep time
        */
        int getSleepTime();
        
    protected:
        DynamicResource *getResource();
        void             setObserving(bool observing);
        
    private:
        DynamicResource *m_resource;
        bool             m_is_observing;
        int              m_sleep_time;
};

#endif // __RESOURCE_OBSERVER_H__