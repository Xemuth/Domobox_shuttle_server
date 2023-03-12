/*******************************************************
* Defintition -- provide few features and macro for    *
* error handling. Configuration management. Etc...     *
*                                                      *
* Author:  Clément Hamon                               *
********************************************************/
#ifndef DEFINITION_HEADER
#define DEFINITION_HEADER
#include <esp_err.h>
#include <esp_system.h>
#include <esp_err.h>
#include <esp_wifi.h>
#include <nvs_flash.h>
#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <string>

#define DOMOBOX_ESP_ERROR_MESSAGE(function_name, error) domobox_esp_message_preparation(__err_rc, __FILE__, __LINE__, __PRETTY_FUNCTION__, #function_name)
#define DOMOBOX_ERROR_MESSAGE(message_assert, expression) domobox_message_preparation(message_assert, __FILE__, __LINE__, __PRETTY_FUNCTION__, #expression)
#define DOMOBOX_VALUE_CHECK(expression_to_check, str_error, action_to_do)             \
{                                                                                     \
    if(!(expression_to_check))                                                        \
    {                                                                                 \
        printf("%s", DOMOBOX_ERROR_MESSAGE(str_error, expression_to_check).c_str());  \
        action_to_do;                                                                 \
    }                                                                                 \
}                                                                                     \

namespace domobox
{
    const auto INIT_LED_PINK        = GPIO_NUM_17;
    const auto WIFI_ACQ_BLUE        = GPIO_NUM_16;
    const auto WIFI_DONE_ROUTINE_UP = GPIO_NUM_18;
    const auto ERROR_RED            = GPIO_NUM_15;

    std::string domobox_esp_message_preparation(esp_err_t rc, const char *file, int line, const char *function, const char *expression);
    std::string domobox_message_preparation(const char* message_assert, const char *file, int line, const char *function, const char *expression);

    enum class Error: uint8_t 
    {
        no_error   = 0x00,
        fake_error = 0x01,
    };
}

#endif

