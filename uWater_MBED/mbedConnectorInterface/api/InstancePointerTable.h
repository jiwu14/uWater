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

#ifndef __INSTANCE_POINTER_TABLE_H__
#define __INSTANCE_POINTER_TABLE_H__

// Logger support
#include "Logger.h"

// string support
#include <string>

// Configuration
#include "mbedConnectorInterface.h"

// our table row structure
typedef struct {
    string  key;
    void   *instance;
} InstancePointerTableRow;

/** InstancePointerTable class
 */
class InstancePointerTable
{
public:
    /**
    Default constructor
    @param logger input the logger instance
    */
    InstancePointerTable(const Logger *logger = NULL);

    /**
    Destructor
    */
    virtual ~InstancePointerTable();

    /**
    Add pointer to the instance table
    @param key input the key for the new pointer
    @param instance input the instance pointer to save
    */
    void add(string key,void *instance);

    /**
    Get a instance pointer index by the name of the key
    @param key input the key to use for the lookup
    @returns the instance pointer if found or NULL if not found
    */
    void *get(string key);

    /**
    Set the Logger instance
    @param logger input the logger instance
    */
    void setLogger(const Logger *logger);

private:
    Logger                 *m_logger;
    InstancePointerTableRow m_instance_pointer_table[IPT_MAX_ENTRIES];

    // initialize our table
    void init();

    // get the next empty slot
    int nextEmptySlot();

    // index from key
    int indexFromKey(string key);

    // get our logger
    Logger *logger();
};

#endif // __INSTANCE_POINTER_TABLE_H__
