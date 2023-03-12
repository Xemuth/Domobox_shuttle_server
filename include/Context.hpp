/*******************************************************
* State -- Opaque ptr to current state                 *
*                                                      *
* Author:  Clément Hamon                               *
********************************************************/
#ifndef CONTEXT_HEADER
#define CONTEXT_HEADER

#include "Definition.hpp"
#include "State.hpp"
#include "Configuration.hpp"

namespace domobox
{
    // Context carry all date over all state of domobox server.
    //
    // |_state|: opaque ptr to implementation of each state of domobox server.
    //
    // |_config|: global configuration of domobox server.
    //
    struct Context
    {
        State         _state;
        Configuration _config;
    };
}

#endif