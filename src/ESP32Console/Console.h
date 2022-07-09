#pragma once

#if !defined(ESP32)
#error This library depends on ESP-IDF and only works on ESP32!
#endif

#include "esp_console.h"
#include "Arduino.h"
#include "./ConsoleCommandBase.h"

namespace ESP32Console
{
    class Console
    {
    private:
        esp_console_repl_config_t repl_config_;
        esp_console_repl_t *repl_ = nullptr;

    public:
        /**
         * @brief Create a new ESP32Console with the default parameters
         */
        Console()
        {   
            repl_config_ = ESP_CONSOLE_REPL_CONFIG_DEFAULT();
            repl_config_.prompt = "ESP32>";
        }

        /**
         * @brief Create a new ESP32Console with the given configuration. Useful for advanced configurations
         *
         * @param config
         */
        Console(esp_console_repl_config_t config)
        {
            repl_config_ = config;
        };

        ~Console()
        {
            end();
        }

        /**
         * @brief Register the given command, using the raw ESP-IDF structure.
         * 
         * @param cmd The command that should be registered
         * @return Return true, if the registration was successfull, false if not.
         */
        bool registerCommand(const esp_console_cmd_t *cmd)
        {
            log_v("Registering new command %s", cmd->command);

            auto code = esp_console_cmd_register(cmd);
            if(code != ESP_OK) {
                log_e("Error registering command (Reason %s)", esp_err_to_name(code));
                return false;
            }

            return true;
        }

        /**
         * @brief Register the given command
         * 
         * @param cmd The command that should be registered
         * @return true If the command was registered successful.
         * @return false If the command was not registered because of an error.
         */
        bool registerCommand(const ConsoleCommandBase &cmd)
        {   
            auto c = cmd.toCommandStruct(); 
            return registerCommand(&c);
        }

        /**
         * @brief Registers the given command
         * 
         * @param command The name under which the command can be called (e.g. "ls"). Must not contain spaces.
         * @param func A pointer to the function which should be run, when this command is called
         * @param help A text shown in output of "help" command describing this command. When empty it is not shown in help.
         * @param hint A text describing the usage of the command in help output
         * @return true If the command was registered successful.
         * @return false If the command was not registered because of an error.
         */
        bool registerCommand(const char *command, esp_console_cmd_func_t func, const char* help, const char* hint = "")
        {
            const esp_console_cmd_t cmd = {
                .command = command,
                .help = help,
                .hint = hint,
                .func = func,
            };

            return registerCommand(&cmd);
        };

        void registerCoreCommands();

        void registerSystemCommands();

        void registerNetworkCommands();

        /**
         * @brief Set the command prompt. Default is "ESP32>". Must be called before begin() to work!
         *
         * @param prompt
         */
        void setPrompt(const char *prompt) { repl_config_.prompt = prompt; };

        /**
         * @brief Enable saving of command history, which makes history persistent over resets. SPIFF need to be enabled, or you need to pass the filename to use. Must be called before begin() to work!
         *
         * @param history_save_path The file which will be used to save command history
         */
        void enablePersistentHistory(const char *history_save_path = "/data/.history.txt") { repl_config_.history_save_path = history_save_path; };

        void begin(int baud, int rxPin = -1, int txPin = -1, uint8_t channel = 0);

        void end();
    };
};