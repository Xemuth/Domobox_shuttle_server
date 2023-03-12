#include "Definition.hpp"
#include "State.hpp"

namespace
{       
    struct ToggleData
    {
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
    struct State::StateImpl
    {
        StateImpl();
        ~StateImpl();

        gpio_config_t _io_conf;
        TaskHandle_t  _toggle_init = nullptr;
        ToggleData    _toggle_init_data{INIT_LED_PINK, 200 / portTICK_PERIOD_MS};
    };

    State::StateImpl::StateImpl()
    {
        _io_conf.intr_type = GPIO_INTR_DISABLE;
        _io_conf.mode = GPIO_MODE_OUTPUT;
        _io_conf.pin_bit_mask = (1 << INIT_LED_PINK) | (1 << WIFI_ACQ_BLUE) | (1 << WIFI_DONE_ROUTINE_UP) | (1 << ERROR_RED);
        gpio_config(&_io_conf);

        xTaskCreate(toggle_task, "blink_init", 1024, &_toggle_init_data , 1, &_toggle_init);
    }

    State::StateImpl::~StateImpl()
    {
        if(_toggle_init) vTaskDelete(_toggle_init);
    }

    namespace init
    {
        const char* name(State& state)
        {
            return "Initialisation";
        }

        State run(State& state)
        {
            for(;;)
            {
                // // First we init nvs flash partition
                // auto err = nvs_flash_init();
                // if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
                //     // NVS partition was truncated and needs to be erased
                //     // Retry nvs_flash_init
                //     ESP_ERROR_CHECK(nvs_flash_erase());
                //     err = nvs_flash_init();
                // }
                // ESP_ERROR_CHECK(err);


                // err = nvs_open("wifi_conf", NVS_READWRITE, &_context._nvs_handle);
                // if (err != ESP_OK) {
                //     printf("Error (%s) opening NVS handle!\n", esp_err_to_name(err));

                // } else {
                //     printf("Done\n");
                // }
                vTaskDelay(10000 / portTICK_PERIOD_MS);
                return make_error(DOMOBOX_ERROR_MESSAGE("Test error state", test > expected), 6000, 1000);
            }
        }
    }
        
    State make_init()
    {
        return State{
            .run = &init::run,
            .name = &init::name,
            .pimpl = std::make_shared<State::StateImpl>(),
        };
    }
}
