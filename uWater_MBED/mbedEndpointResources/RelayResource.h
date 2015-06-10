#ifndef __RELAY_RESOURCE_H__
#define __RELAY_RESOURCE_H__
#include <ctime>
// Base class
#include "DynamicResource.h"
#include "mbed.h"

//constants
#define DISCONNECTION_INTERVAL 600  //10mins disconnect if relay is on
#define CHECK_INTERVAL 300  //5 mins

//Analog in moisture sensor
DigitalOut relay_out(D4);

static uint8_t relay_state = 0;
static time_t lastQueried = 0;
static Ticker queryChecker;

/** Relay Resource **/
class RelayResource : public DynamicResource {
public:
    /**
    Default constructor
    @param logger input logger instance for this resource
    @param name input the resource name
    @param observable input the resource is Observable (default: FALSE)
    */
    RelayResource(const Logger *logger,const char *name,const bool observable = false) : DynamicResource(logger,name,"Relay", SN_GRS_GET_ALLOWED | SN_GRS_PUT_ALLOWED,observable) {
        queryChecker.attach(this, &RelayResource::checkQueried, CHECK_INTERVAL);
    }
    
    virtual string get() {
        char relay_stat[2] = {0, 0};
        relay_stat[0] = relay_state + '0';
        lastQueried = time(NULL);
        return string(relay_stat);
    }
    
    virtual void put(const string value) {
        int newVal;
        if (sscanf((char *)value.c_str(), "%d", &newVal) &&
            (newVal == 0 || newVal == 1)) {
            relay_out = relay_state = newVal;
        }
        lastQueried = time(NULL);
    }
    
    virtual void checkQueried() {
        if (lastQueried != 0 && relay_state == 1 &&
            difftime(time(NULL), lastQueried) > DISCONNECTION_INTERVAL) {
            relay_out = relay_state = 0;
        }
    }
};
#endif