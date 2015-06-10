/**
 * @file    DynamicResource.cpp
 * @brief   mbed CoAP Endpoint Dynamic Resource class
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

#include "DynamicResource.h"

// InstancePointerTable Helper
#include "InstancePointerTableHelper.h"

// ResourceObserver help
#include "ResourceObserver.h"

// Options enablement
#include "Options.h"

// GET option that can be used to Start/Stop Observations...
#define START_OBS 0
#define STOP_OBS  1

// MaxAge support for each DynamicResource
#define DEFAULT_MAXAGE 60

// ContentFormat defaults for each DynamicResource
#define DEFAULT_CONTENT_FORMAT 0

// default constructor
DynamicResource::DynamicResource(const Logger *logger,const char *name,const char *res_type,uint8_t res_mask,const bool observable) : Resource<string>(logger,string(name),string(""))
{
    this->m_res_type = string(res_type);
    this->m_observable = observable;
    this->m_res_mask = res_mask;
    this->m_obs_number = 0;
    this->m_obs_token_ptr = NULL;
    this->m_obs_token_len = 0;
    this->m_data_wrapper = NULL;
    this->m_observer = NULL;
    this->m_maxage = DEFAULT_MAXAGE;
    this->m_content_format = DEFAULT_CONTENT_FORMAT;
}

// constructor (input initial value)
DynamicResource::DynamicResource(const Logger *logger,const char *name,const char *res_type,const string value,uint8_t res_mask,const bool observable) : Resource<string>(logger,string(name),value)
{
    this->m_res_type = string(res_type);
    this->m_observable = observable;
    this->m_res_mask = res_mask;
    this->m_obs_number = 0;
    this->m_obs_token_ptr = NULL;
    this->m_obs_token_len = 0;
    this->m_data_wrapper = NULL;
    this->m_observer = NULL;
    this->m_maxage = DEFAULT_MAXAGE;
    this->m_content_format = DEFAULT_CONTENT_FORMAT;
}

// constructor (strings)
DynamicResource::DynamicResource(const Logger *logger,const string name,const string res_type,const string value,uint8_t res_mask,const bool observable) : Resource<string>(logger,name,value)
{
    this->m_res_type = res_type;
    this->m_observable = observable;
    this->m_res_mask = res_mask;
    this->m_obs_number = 0;
    this->m_obs_token_ptr = NULL;
    this->m_obs_token_len = 0;
    this->m_data_wrapper = NULL;
    this->m_observer = NULL;
    this->m_maxage = DEFAULT_MAXAGE;
    this->m_content_format = DEFAULT_CONTENT_FORMAT;
}

// copy constructor
DynamicResource::DynamicResource(const DynamicResource &resource) : Resource<string>((const Resource<string> &)resource)
{
    this->m_res_type = resource.m_res_type;
    this->m_observable = resource.m_observable;
    this->m_res_mask = resource.m_res_mask;
    this->m_obs_number = resource.m_obs_number;
    this->m_obs_token_ptr = resource.m_obs_token_ptr;
    this->m_obs_token_len = resource.m_obs_token_len;
    this->m_data_wrapper = resource.m_data_wrapper;
    this->m_observer = resource.m_observer;
    this->m_maxage = resource.m_maxage;
    this->m_content_format = resource.m_content_format;
}

// destructor
DynamicResource::~DynamicResource()
{
    if(this->m_obs_token_ptr) free(this->m_obs_token_ptr);
}

// bind resource to NSDL
void DynamicResource::bind(void *p)
{
    if (p != NULL) {
        sn_nsdl_resource_info_s *resource_ptr = (sn_nsdl_resource_info_s *)p;
        const uint8_t *name = (const uint8_t *)(this->getName().c_str());
        const uint8_t *res_type = (const uint8_t *)this->m_res_type.c_str();
        int name_length = this->getName().size();
        int res_type_length = this->m_res_type.size();
        int is_observable = 0;
        if (this->m_observable == true) is_observable = 1;
        const string *key = new string(this->getName());
        ipt_helper_add_instance_pointer(key,this);
        nsdl_create_dynamic_resource(resource_ptr,name_length,(uint8_t *)name,res_type_length,(uint8_t *)res_type,is_observable,&ipt_helper_nsdl_callback_stub,this->m_res_mask);
        this->logger()->log("DynamicResource: [%s] type: [%s] bound (observable: %d)",name,res_type,is_observable);
    } else {
        this->logger()->log("DynamicResource: NULL parameter in bind()");
    }
}

// process NSDL message
uint8_t DynamicResource::process(sn_coap_hdr_s *received_coap_ptr, sn_nsdl_addr_s *address, sn_proto_info_s *proto)
{
    sn_coap_hdr_s *coap_res_ptr = 0;
    
    // create our key for debugging output...
    DataWrapper *hold = this->getDataWrapper();
    this->setDataWrapper(NULL);
    string key = this->coapDataToString(received_coap_ptr->uri_path_ptr,received_coap_ptr->uri_path_len);
    this->setDataWrapper(hold);

    if(received_coap_ptr->msg_code == COAP_MSG_CODE_REQUEST_GET) {
        coap_res_ptr = sn_coap_build_response(received_coap_ptr, COAP_MSG_CODE_RESPONSE_CONTENT);

        // process the GET if we have registered a callback for it...
        if ((this->m_res_mask&SN_GRS_GET_ALLOWED) != 0) {
            // call the resource get() to get the resource value
            this->logger()->log("Calling resource(GET) for [%s]...",key.c_str());
            string value = this->get();

            // convert the string from the GET to something suitable for CoAP payloads          
            if (this->getDataWrapper() != NULL) {
                // wrap the data...
                this->getDataWrapper()->wrap((uint8_t *)value.c_str(),(int)value.size());
                
                // announce (after wrap)
                this->logger()->log("Building payload for [%s]=[%s]...",key.c_str(),this->getDataWrapper()->get());
                
                // fill in the CoAP response payload
                coap_res_ptr->payload_len = this->getDataWrapper()->length();
                coap_res_ptr->payload_ptr = this->getDataWrapper()->get();
            }
            else {
                // announce (no wrap)
                this->logger()->log("Building payload for [%s]=[%s]...",key.c_str(),value.c_str());
                
                // do not wrap the data...
                coap_res_ptr->payload_len = value.size();
                coap_res_ptr->payload_ptr = (uint8_t *)value.c_str();
            }
            
            // CoAP Content-Format
            coap_res_ptr->content_type_ptr = &this->m_content_format;                       
            coap_res_ptr->content_type_len = sizeof(this->m_content_format);
            
            // max-age cache control
            coap_res_ptr->options_list_ptr = (sn_coap_options_list_s*)nsdl_alloc(sizeof(sn_coap_options_list_s));
            if(!coap_res_ptr->options_list_ptr){
                this->logger()->log("Cant alloc options list");
                coap_res_ptr->options_list_ptr = NULL;
            }
            else{
                memset(coap_res_ptr->options_list_ptr, 0, sizeof(sn_coap_options_list_s));
                coap_res_ptr->options_list_ptr->max_age_ptr = &this->m_maxage;              
                coap_res_ptr->options_list_ptr->max_age_len = sizeof(this->m_maxage);
            }
            
            // Observation handling... 
            if(received_coap_ptr->token_ptr) {
                if(this->m_obs_token_ptr) {
                    free(this->m_obs_token_ptr);
                    this->m_obs_token_ptr = NULL;
                    this->m_obs_token_len = 0;
                }
                
                this->m_obs_token_ptr = (uint8_t*)malloc(received_coap_ptr->token_len);
                if(this->m_obs_token_ptr) {
                    memcpy(this->m_obs_token_ptr, received_coap_ptr->token_ptr,received_coap_ptr->token_len);
                    this->m_obs_token_len = received_coap_ptr->token_len;
                }
            }
            
            // Observation handling...
            if(received_coap_ptr->options_list_ptr && received_coap_ptr->options_list_ptr->observe) {                
                // create the options list pointer
                coap_res_ptr->options_list_ptr = (sn_coap_options_list_s*)malloc(sizeof(sn_coap_options_list_s));
                memset(coap_res_ptr->options_list_ptr, 0, sizeof(sn_coap_options_list_s));

                // if GET controlled observation is enabled, perform it here...
                if (((Connector::Options *)this->getOptions())->enableGETObservationControl()) {  
                    // ResourceObserver
                    ResourceObserver *observer = (ResourceObserver *)this->m_observer;
                    
                    // I think we have to check for a NULl reference first... then process possibly..
                    if (received_coap_ptr->options_list_ptr->observe_ptr != NULL) {
                        // get observe start/stop value from received options list pointer
                        uint8_t OBS_command = *received_coap_ptr->options_list_ptr->observe_ptr;
                        if (OBS_command == START_OBS) {
                            coap_res_ptr->options_list_ptr->observe_ptr = &this->m_obs_number;      // see nullify note below...
                            coap_res_ptr->options_list_ptr->observe_len = 1;
                            this->m_obs_number++;
                            if (observer != NULL) observer->beginObservation();
                        }
                        if (OBS_command == STOP_OBS) {
                            if (observer != NULL) observer->stopObservation();
                        }
                    }
                    else {
                        // non-GET controlled observationing: simply fill in the observation requirements...
                        coap_res_ptr->options_list_ptr->observe_ptr = &this->m_obs_number;          // see nullify note below...
                        coap_res_ptr->options_list_ptr->observe_len = 1;
                        this->m_obs_number++;
                    }
                }
                else {
                    // non-GET controlled observationing: simply fill in the observation requirements...
                    coap_res_ptr->options_list_ptr->observe_ptr = &this->m_obs_number;          // see nullify note below...
                    coap_res_ptr->options_list_ptr->observe_len = 1;
                    this->m_obs_number++;
                }
            }

            // build out the response and send...
            sn_nsdl_send_coap_message(address,coap_res_ptr);
            
            // freeing up the options_list_ptr and clearing the content_type pointer
            nsdl_free(coap_res_ptr->options_list_ptr);
            coap_res_ptr->options_list_ptr = NULL;
            coap_res_ptr->content_type_ptr = NULL;
            
            //
            // nullify note: 
            //
            // because our obs_number (assigned to observe_ptr) is part of this object instance, we dont 
            // want to have the underlying free() try to free it... to just nullify here
            //
            if (coap_res_ptr->options_list_ptr) coap_res_ptr->options_list_ptr->observe_ptr = 0;        
        } 
        else {
            this->logger()->log("ERROR: resource(GET) mask is munged (mask: 0x%x)",this->m_res_mask);
        }
    } else if(received_coap_ptr->msg_code == COAP_MSG_CODE_REQUEST_PUT) {
        if(received_coap_ptr->payload_len > 0) {
            // process the PUT if we have registered a callback for it...
            if ((this->m_res_mask&SN_GRS_PUT_ALLOWED) != 0) {
                // put() delivers values as std::string
                string value = this->coapDataToString(received_coap_ptr->payload_ptr,received_coap_ptr->payload_len);

                // call the resource put() to set the resource value
                this->logger()->log("Calling resource(PUT) with [%s]=[%s]...",key.c_str(),value.c_str());
                this->put(value);

                // build out the response and send...
                this->logger()->log("resource(PUT) completed for [%s]...",key.c_str());
                coap_res_ptr = sn_coap_build_response(received_coap_ptr,COAP_MSG_CODE_RESPONSE_CHANGED);
                sn_nsdl_send_coap_message(address,coap_res_ptr);
            } else {
                this->logger()->log("ERROR: resource(PUT) mask is munged (mask: 0x%x)",this->m_res_mask);
            }
        } else {
            this->logger()->log("ERROR: Binder(PUT) payload is NULL...");
        }
    } else if(received_coap_ptr->msg_code == COAP_MSG_CODE_REQUEST_POST) {
        if(received_coap_ptr->payload_len > 0) {
            // process the POST if we have registered a callback for it...
            if ((this->m_res_mask&SN_GRS_POST_ALLOWED) != 0) {
                // post() delivers values as std::string
                string value = this->coapDataToString(received_coap_ptr->payload_ptr,received_coap_ptr->payload_len);

                // call the resource post() to set the resource value
                this->logger()->log("Calling resource(POST) with [%s]=[%s]...",key.c_str(),value.c_str());
                this->post(value);

                // build out the response and send...
                this->logger()->log("resource(POST) completed for [%s]...",key.c_str());
                coap_res_ptr = sn_coap_build_response(received_coap_ptr,COAP_MSG_CODE_RESPONSE_CHANGED);
                sn_nsdl_send_coap_message(address,coap_res_ptr);
            } else {
                this->logger()->log("ERROR: resource(POST) mask is munged (mask: 0x%x)",this->m_res_mask);
            }
        } else {
            this->logger()->log("ERROR: Binder(POST) payload is NULL...");
        }
    } else if(received_coap_ptr->msg_code == COAP_MSG_CODE_REQUEST_DELETE) {
        if(received_coap_ptr->payload_len > 0) {
            // process the DELETE if we have registered a callback for it...
            if ((this->m_res_mask&SN_GRS_DELETE_ALLOWED) != 0) {
                // del() delivers values as std::string
                string value = this->coapDataToString(received_coap_ptr->payload_ptr,received_coap_ptr->payload_len);

                // call the resource del() to set the resource value
                this->logger()->log("Calling resource(DELETE) with [%s]=[%s]...",key.c_str(),value.c_str());
                this->del(value);

                // build out the response and send...
                this->logger()->log("resource(DELETE) completed for [%s]...",key.c_str());
                coap_res_ptr = sn_coap_build_response(received_coap_ptr,COAP_MSG_CODE_RESPONSE_CHANGED);
                sn_nsdl_send_coap_message(address,coap_res_ptr);
            } else {
                this->logger()->log("ERROR: resource(DELETE) mask is munged (mask: 0x%x)",this->m_res_mask);
            }
        } else {
            this->logger()->log("ERROR: Binder(DELETE) payload is NULL...");
        }
    }

    sn_coap_parser_release_allocated_coap_msg_mem(coap_res_ptr);
    
    return 0;
}

// send the notification
int DynamicResource::notify(const string data) {
    return this->notify((uint8_t *)data.c_str(),(int)data.length());
}

// send the notification
int DynamicResource::notify(uint8_t *data,int data_length) {
    uint8_t *notify_data = NULL;
    int notify_data_length = 0;
    
    // convert the string from the GET to something suitable for CoAP payloads          
    if (this->getDataWrapper() != NULL) {
        // wrap the data...
        this->getDataWrapper()->wrap((uint8_t *)data,data_length);
        
        // announce (after wrap)
        //this->logger()->log("Notify payload [%s]...",this->getDataWrapper()->get());
        
        // fill notify 
        notify_data_length = this->getDataWrapper()->length();
        notify_data = this->getDataWrapper()->get();
    }
    else {
        // announce (no wrap)
        //this->logger()->log("Notify payload [%s]...",data);
        
        // do not wrap the data...
        notify_data_length = data_length;
        notify_data = data;
    }
    
    // send the observation...
    int status = sn_nsdl_send_observation_notification(this->m_obs_token_ptr,this->m_obs_token_len,notify_data,notify_data_length,&this->m_obs_number,1,COAP_MSG_TYPE_NON_CONFIRMABLE,0);
    if (status == 0) {
        this->logger()->log("ERROR: resource(NOTIFY) send failed...");
    }
    else {
        ++(this->m_obs_number);
    }
    
    // return our status
    return status;
}

// default PUT (does nothing)
void DynamicResource::put(const string value)
{
    // not used by default
    ;
}

// default POST (does nothing)
void DynamicResource::post(const string value)
{
    // not used by default
    ;
}

// default DELETE (does nothing)
void DynamicResource::del(const string value)
{
    // not used by default
    ;
}

// default observe behavior
void DynamicResource::observe() {
    if (this->m_observable == true) {
        this->notify(this->get());
    }
}

// set the observer pointer
void DynamicResource::setObserver(void *observer) {
    this->m_observer = observer;
}

// set the content-format in responses
void DynamicResource::setContentFormat(uint8_t content_format) {
    this->m_content_format = content_format;
}

// set the max-age of responses
void DynamicResource::setMaxAge(uint8_t maxage) {
    this->m_maxage = maxage;
}

// convenience method to get the URI from its buffer field...
string DynamicResource::coapDataToString(uint8_t *coap_data_ptr,int coap_data_ptr_length)
{
    if (coap_data_ptr != NULL && coap_data_ptr_length > 0) {
        if (this->getDataWrapper() != NULL) {
            // unwrap the data...
            this->getDataWrapper()->unwrap(coap_data_ptr,coap_data_ptr_length);
            char *buf = (char *)this->getDataWrapper()->get();                  // assumes data is null terminated in DataWrapper...
            return string(buf);
        }
        else {
            // no unwrap of the data...
            char buf[MAX_VALUE_BUFFER_LENGTH+1];
            memset(buf,0,MAX_VALUE_BUFFER_LENGTH+1);
            memcpy(buf,(char *)coap_data_ptr,coap_data_ptr_length);
            return string(buf);
        }
    }
    return string("");
}
