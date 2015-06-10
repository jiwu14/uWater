#ifndef __MOISTURE_RESOURCE_H__
#define __MOISTURE_RESOURCE_H__
// Base class
#include "DynamicResource.h"

//Analog in moisture sensor
AnalogIn moisture_in(A0);

/** Moisture Resource **/
class MoistureResource : public DynamicResource {
public:
    /**
    Default constructor
    @param logger input logger instance for this resource
    @param name input the resource name
    @param observable input the resource is Observable (default: FALSE)
    */
    MoistureResource(const Logger *logger,const char *name,const bool observable = false) : DynamicResource(logger,name,"Moisture", SN_GRS_GET_ALLOWED,observable) {
    }
    
    virtual string get() {
        char moisture_lvl[7];
        memset(moisture_lvl,0,7);
        sprintf(moisture_lvl,"%3.2f", moisture_in.read());
        return string(moisture_lvl);
    }
};
#endif