#include "./Console.h"
#include "soc/soc_caps.h"
#include "esp_err.h"
#include "ESP32Console/Commands/CoreCommands.h"
#include "ESP32Console/Commands/SystemCommands.h"
#include "ESP32Console/Commands/NetworkCommands.h"

static const char *TAG = "ESP32Console";



using namespace ESP32Console::Commands;

namespace ESP32Console
{
    void Console::registerCoreCommands()
    {
        registerCommand(getClearCommand());
        registerCommand(getEchoCommand());
        registerCommand(getSetMultilineCommand());
    }

    void Console::registerSystemCommands()
    {
        registerCommand(getSysInfoCommand());
        registerCommand(getRestartCommand());
        registerCommand(getMemInfoCommand());
    }

    void ESP32Console::Console::registerNetworkCommands() {
        registerCommand(getPingCommand());
    }

    void Console::begin(int baud, int rxPin, int txPin, uint8_t channel)
    {
        log_d("Initialize console");

        if (channel >= SOC_UART_NUM)
        {
            log_e("Serial number is invalid, please use numers from 0 to %u", SOC_UART_NUM - 1);
            return;
        }

        // Register help command
        esp_console_register_help_command();

        // Configure the UART
        esp_console_dev_uart_config_t hw_config = {
            .channel = channel,
            .baud_rate = baud,
            .tx_gpio_num = txPin,
            .rx_gpio_num = rxPin};

        auto code = esp_console_new_repl_uart(&hw_config, &repl_config_, &repl_);
        if (code != ESP_OK)
        {
            log_e("Could not initialize UART. Check if you are still have an active Serial component! (Reason %s)", esp_err_to_name(code));
            return;
        }

        code = esp_console_start_repl(repl_);
        if (code != ESP_OK)
        {
            log_e("Could not start REPL! (Reason %s)", esp_err_to_name(code));
            return;
        }

        // Register core commands like echo
        registerCoreCommands();
    }

    void Console::end()
    {
        if (repl_)
        {
            // Stop REPL
            repl_->del(repl_);
            esp_console_deinit();
        }
    }
};