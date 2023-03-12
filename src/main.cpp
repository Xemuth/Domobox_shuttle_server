/*******************************************************
* Main -- Entry point of dombox shuttle server project *
*                                                      *
* Author:  Clément Hamon                               *
********************************************************/

#include "Context.hpp"
#include "State.hpp"
#include "Definition.hpp"

extern "C" {
    void app_main(void);
}

void app_main() 
{
    domobox::Context context;
    context._state = domobox::make_init();
    for(;;)
    {
        context._state = context._state.run(context._state);
    }
}
