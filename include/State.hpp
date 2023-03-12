/*******************************************************
* State -- Opaque ptr to current state                 *
*                                                      *
* Author:  Clément Hamon                               *
********************************************************/
#ifndef STATE_HEADER
#define STATE_HEADER
#include "Definition.hpp"
#include <memory>

namespace domobox
{  
    
    struct State;
    using RunCallback = State (*)(State& state);
    using NameCallback = const char* (*)(State& state);

    struct State
    {
            RunCallback run;
            NameCallback name;

            struct StateImpl;
            std::shared_ptr<StateImpl> pimpl;
    };

    State make_init();
    State make_error(std::string error_str, uint16_t time_before_reset, uint16_t blink_period);
}

#endif 