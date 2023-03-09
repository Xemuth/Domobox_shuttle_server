/*******************************************************
* Main -- Entry point of dombox shuttle server project *
*                                                      *
* Author:  Clément Hamon                               *
********************************************************/

#include "State.hpp"
#include "Definition.hpp"

extern "C" {
    void app_main(void);
}

void app_main() 
{
    domobox::State state;
    state._pimpl = domobox::make_init();
    state.run();
}
