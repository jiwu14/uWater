/**
 * @file    InstancePointerTableHelper.h
 * @brief   instance pointer table helper functions for DynamicResource
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

#ifndef __INSTANCE_POINTER_TABLE_HELPER_H__
#define __INSTANCE_POINTER_TABLE_HELPER_H__

// InstancePointerTable
#include "InstancePointerTable.h"
extern Logger logger;
InstancePointerTable              __nsdl_lookup_table(&logger);         // Instance Pointer Table


// lookup a DynamicResource instance indexed by our resource URI as the key
extern "C" DynamicResource *__lookup_instance_pointer(const char *uri,const int uri_length)
{
    if (uri != NULL && uri_length > 0) {
        string key(uri,uri_length);
        return (DynamicResource *)__nsdl_lookup_table.get(key);
    }
    return NULL;
}

// callback function for NSDL library to call into... ASSUMPTION: 1 and only 1 DynamicResource<> instance per Resource URI...
extern "C" uint8_t ipt_helper_nsdl_callback_stub(sn_coap_hdr_s *received_coap_ptr, sn_nsdl_addr_s *address, sn_proto_info_s * proto)
{
    uint8_t status = 1;
    if (received_coap_ptr != NULL) {
        // retrieve our resource instance via lookup/index by our resource URI
        DynamicResource *instance = __lookup_instance_pointer((const char *)received_coap_ptr->uri_path_ptr,received_coap_ptr->uri_path_len);
        if (instance != NULL) {
            std::printf("Instance retrieved.. processing callback...\r\n");
            status = instance->process(received_coap_ptr,address,proto);
        } else {
            std::printf("Unable to process callback: unable to lookup DynamicResource<> instance pointer... ignorning...\r\n");
        }
    } else {
        std::printf("Unable to process callback: received coap pointer is NULL... ignoring...\r\n");
    }
    return status;
}

// add a instance pointer to our lookup table keyed by the key
extern "C" void ipt_helper_add_instance_pointer(const string *key,DynamicResource *instance)
{
    __nsdl_lookup_table.add(*key,instance);
    if (key != NULL) delete key;
}

#endif // __INSTANCE_POINTER_TABLE_HELPER_H__
