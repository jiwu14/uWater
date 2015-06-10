/**
 * @file    InstancePointerTable.h
 * @brief   instance pointer table header
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

#include "InstancePointerTable.h"

// constructor
InstancePointerTable::InstancePointerTable(const Logger *logger)
{
    this->m_logger = (Logger *)logger;
}

// destructor
InstancePointerTable::~InstancePointerTable()
{
}

// add to the table
void InstancePointerTable::add(string key,void *instance)
{
    // get our index
    int index = this->indexFromKey(key);
    if (index >= 0) {
        // overwrite the existing reference we have...
        this->m_instance_pointer_table[index].instance = instance;
    } else {
        // get the next empty slot
        index = this->nextEmptySlot();
        if (index >= 0) {
            // set the table entry
            this->m_instance_pointer_table[index].key = key;
            this->m_instance_pointer_table[index].instance = instance;
        } else {
            // table is FULL!  Error...
            this->logger()->log("ERROR: InstancePointerTable is FULL... please expand table");
        }
    }
}

// get from the table
void *InstancePointerTable::get(string key)
{
    // get our index
    int index = this->indexFromKey(key);
    if (index >= 0) {
        return this->m_instance_pointer_table[index].instance;
    }
    return NULL;
}

// find next empty slot
int InstancePointerTable::nextEmptySlot()
{
    return this->indexFromKey("");
}

// lookup into the table
int InstancePointerTable::indexFromKey(string key)
{
    int index = -1;
    bool found = false;

    for(int i=0; i<IPT_MAX_ENTRIES && !found; ++i) {
        if (this->m_instance_pointer_table[i].key.compare(key) == 0) {
            found = true;
            index = i;
        }
    }

    return index;
}

// initialize
void InstancePointerTable::init()
{
    for(int i=0; i<IPT_MAX_ENTRIES; ++i) {
        this->m_instance_pointer_table[i].key = "";
        this->m_instance_pointer_table[i].instance = NULL;
    }
}

// set our logger
void InstancePointerTable::setLogger(const Logger *logger)
{
    this->m_logger = (Logger *)logger;
}

// get our logger
Logger *InstancePointerTable::logger()
{
    return this->m_logger;
}
