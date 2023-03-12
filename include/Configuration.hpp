/*******************************************************
* State -- Configuration for domobox server            *
*                                                      *
* Author:  Clément Hamon                               *
********************************************************/
#ifndef CONFIGURATION_HEADER
#define CONFIGURATION_HEADER

#include "Definition.hpp"
#include "State.hpp"

namespace domobox
{
        // Configuration carry configuration. It is mostly initialised during init phase.
        //
        // |_wifi_pass|: wifi password stored inside nvs storage.
        //
        // |_wifi_ssid|: wifi ssid stored inside nvs storage.
        //
        // |_nvs_handle|: non volatle storage handle provided by esp api.
        //
        // |_timeout_reset_ms|: Time in ms before reseting the esp when going to error state.
        //
        struct Configuration
        {
            char       _wifi_pass[64];
            char       _wifi_ssid[32];
            nvs_handle _nvs_handle;        // non volatile storage lib
            uint16_t   _timeout_reset_ms; 
        };    
}

#endif