#include "Definition.hpp"
#include "State.hpp"

namespace 
{

}

namespace domobox
{
    struct State::StateImpl
    {
        StateImpl(std::string error_str, uint16_t time_before_reset, uint16_t blink_period);
        ~StateImpl();

        std::string   _error_str;
        uint16_t      _time_before_reset;
        uint16_t      _blink_period;
    };

    State::StateImpl::StateImpl(std::string error_str, uint16_t time_before_reset, uint16_t blink_period) 
        : _error_str(std::move(error_str))
        , _time_before_reset(time_before_reset)
        , _blink_period(blink_period)
    {
    }

    State::StateImpl::~StateImpl()
    {
    }

    namespace error 
    {
        State run(State& state)
        {
            DOMOBOX_VALUE_CHECK(state.pimpl->_time_before_reset > state.pimpl->_blink_period, "_blink_period must be lower than time before reset", state.pimpl->_blink_period = 0);
            bool toggle = false;
            uint32_t number_of_blink = state.pimpl->_time_before_reset / state.pimpl->_blink_period;
            if(state.pimpl->_blink_period == 0)   
                number_of_blink = state.pimpl->_time_before_reset;
            for(int e = 0; e < number_of_blink; e++)
            {
                toggle = !toggle;
                printf("%s", state.pimpl->_error_str.c_str());
                gpio_set_level(ERROR_RED, toggle);
                vTaskDelay(state.pimpl->_blink_period);
            }
            esp_restart();
            return State{nullptr, nullptr, nullptr};
        }
        
        const char* name(State& state)
        {
            return "Error";
        }
    }

    State make_error(std::string error_str, uint16_t time_before_reset, uint16_t blink_period)
    {
        return State{
            .run = &error::run,
            .name = &error::name,
            .pimpl = std::make_shared<State::StateImpl>(error_str, time_before_reset, blink_period),
        };
    }
}