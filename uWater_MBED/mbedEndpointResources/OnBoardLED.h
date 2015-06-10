/**
 * @file    LightResource.h
 * @brief   mbed CoAP Endpoint Light resource supporting CoAP GET and PUT
 * @author  Doug Anson, Michael Koster
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

#ifndef __LED_RESOURCE_H__
#define __LED_RESOURCE_H__


// Base class
#include "DynamicResource.h"

// our Light
DigitalOut LED_red(LED1);
DigitalOut LED_green(LED2);
DigitalOut LED_blue(LED3);

static char * LED_color_value = {"0000000"}; //RRGGBBII

void LED_set_color(char * color_string)
{
    static uint8_t red, green, blue, index;
    int color_int;

    sscanf(color_string, "%X", &color_int);
    
    index = color_int & 255;
    blue = color_int >> 8 & 255;
    green = color_int >> 16 & 255;
    red = color_int >> 24 & 255;
        
    if(index == 0) {
        LED_red = !(red & 1);
        LED_green = !(green & 1);
        LED_blue = !(blue & 1);
    }
}

/** LightResource class
 */
class LEDResource : public DynamicResource
{

public:
    /**
    Default constructor
    @param logger input logger instance for this resource
    @param name input the Light resource name
    @param observable input the resource is Observable (default: FALSE)
    */
    LEDResource(const Logger *logger,const char *name,const bool observable = false) : DynamicResource(logger,name,"OnBoardLED",SN_GRS_GET_ALLOWED|SN_GRS_PUT_ALLOWED,observable) {
    LED_set_color("00000000");
    wait(0.5);
    LED_set_color("FF000000");
    wait(0.5);
    LED_set_color("00FF0000");
    wait(0.5);
    LED_set_color("0000FF00");
    wait(0.5);
    LED_set_color(LED_color_value);
    }

    /**
    Get the value of the LED
    @returns string containing the last setting
    */
    virtual string get() {
        return(LED_color_value);
    }

    /**
    Set the value of the LED
    @param string input the string containing the desired setting
    */
    virtual void put(const string value) {
        if( sizeof(value) == sizeof(LED_color_value) ){
            LED_color_value = (char *)value.c_str();
            LED_set_color(LED_color_value);
        }
    }
};

#endif // __LED_RESOURCE_H__
