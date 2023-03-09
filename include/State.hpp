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
    struct State
    {
        Error run();
        const char* name();

        struct StateImpl;
        std::shared_ptr<StateImpl> _pimpl;
    };

    

    std::shared_ptr<State::StateImpl> make_init();

}

#endif 