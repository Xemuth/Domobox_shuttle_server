#include "Definition.hpp"
#include "State.hpp"

#include <esp_system.h>
#include <esp_err.h>
#include <esp_wifi.h>
#include <nvs_flash.h>
#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <EEPROM.h>

namespace
{       
    struct domobox::State::StateImpl;
    struct ToggleData
    {
        domobox::State::StateImpl& _impl;
        gpio_num_t _gpio_to_toggle;
        TickType_t _tick_to_wait;
    };
    
    void toggle_task(void* toggle_data)
    {
        bool state = false;
        for(;;)
        {
            auto& data = *reinterpret_cast<ToggleData*>(toggle_data);
            gpio_set_level(data._gpio_to_toggle, state);
            state = !state;
            vTaskDelay(data._tick_to_wait);
        }
    }
}

namespace domobox
{
    const auto INIT_LED_PINK = GPIO_NUM_17;
    const auto WIFI_ACQ_BLUE = GPIO_NUM_16;
    const auto WIFI_DONE_ROUTINE_UP = GPIO_NUM_18;

    struct State::StateImpl
    {
        StateImpl();
        ~StateImpl();

        gpio_config_t _io_conf;
        TaskHandle_t  _toggle_init = nullptr;
        ToggleData    _toggle_init_data{*this, INIT_LED_PINK, 200 / portTICK_PERIOD_MS};
        TaskHandle_t  _toggle_wifi_acq = nullptr;
        ToggleData    _toggle_wifi_acq_data{*this, WIFI_ACQ_BLUE, 400 / portTICK_PERIOD_MS};
        TaskHandle_t  _toggle_wifi_done = nullptr;
        ToggleData    _toggle_wifi_done_data{*this, WIFI_DONE_ROUTINE_UP, 600 / portTICK_PERIOD_MS};
    };

    State::StateImpl::StateImpl()
    {
        _io_conf.intr_type = GPIO_INTR_DISABLE;
        _io_conf.mode = GPIO_MODE_OUTPUT;
        _io_conf.pin_bit_mask = (1 << INIT_LED_PINK) | (1 << WIFI_ACQ_BLUE) | (1 << WIFI_DONE_ROUTINE_UP);
        gpio_config(&_io_conf);

        xTaskCreate(toggle_task, "blink_init", 1024, &_toggle_init_data , 1, &_toggle_init);
        xTaskCreate(toggle_task, "blink_wifi_acq", 1024, &_toggle_wifi_acq_data, 1, &_toggle_wifi_acq);
        xTaskCreate(toggle_task, "blink_wifi_done", 1024, &_toggle_wifi_done_data, 1, &_toggle_wifi_done);
    }

    State::StateImpl::~StateImpl()
    {
        if(_toggle_init) vTaskDelete(_toggle_init);
        if(_toggle_wifi_acq) vTaskDelete(_toggle_wifi_acq);
        if(_toggle_wifi_done) vTaskDelete(_toggle_wifi_done);
    }
    
    const char* State::name()
    {
        return "Initialisation";
    }

    Error State::run()
    {
        for(;;)
        {
            
        }
        return Error::no_error;
    }

    std::shared_ptr<State::StateImpl> make_init()
    {
        return std::make_shared<State::StateImpl>();
    }
}
