/**
 * @file    Logger.cpp
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

#include "Logger.h"

// Constructor
Logger::Logger(const RawSerial *pc)
{
    this->m_pc = (RawSerial *)pc;
}

// Copy Constructor
Logger::Logger(const Logger &logger)
{
    this->m_pc = logger.m_pc;
}

// Destructor
Logger::~Logger()
{
}

// Log the ouput to the attached serial console
void Logger::logIt(const char *format,...)
{   
    // build the variable args into a string
    va_list args;
    char buffer[LOGGER_BUFFER_LENGTH+1];
    memset(buffer,0,LOGGER_BUFFER_LENGTH+1);
    va_start(args, format);
    vsnprintf(buffer,LOGGER_BUFFER_LENGTH,format,args);
    
    // clean up...
    va_end(args);
    
    // print it...
    if (this->m_pc != NULL)
        this->m_pc->printf("%s",buffer);
    else
        std::printf("%s",buffer);
}
