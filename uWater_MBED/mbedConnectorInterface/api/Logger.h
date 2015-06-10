/**
 * @file    Logger.h
 * @brief   mbed CoAP Endpoint logging class
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

#ifndef __LOGGER_H__
#define __LOGGER_H__

// mbed API
#include "mbed.h"

// Support for std args
#include <stdarg.h>

// Configuration
#include "mbedConnectorInterface.h"

// logging macro
#define log(x, ...)  logIt(x"\r\n",##__VA_ARGS__)

/** Logger class
 */
class Logger
{
public:
    /**
    Default constructor
    @param pc input BufferedSerial instance for debugging (if NULL, no debugging output will occur in the library)
    */
    Logger(const RawSerial *pc);

    /**
    Copy constructor
    @param logger input Logger instance to deep copy
    */
    Logger(const Logger &logger);

    /**
    Destructor
    */
    virtual ~Logger();

    /**
    Log output to the given serial console
    @param format input format for the logging
    @param ... input (variable arguments to display)
    */
    void logIt(const char *format, ...);
protected:

private:
    RawSerial  *m_pc;
};

#endif // __LOGGER_H__
