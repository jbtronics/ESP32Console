# ESP32Console

Arduino library to add a serial console to your ESP32 console. It includes some useful commands and allows to easily add your own custom commands.

This easily allows you to control and configure your control via serial console in a comfortable and easy way.

This library encapsulates the Console component included in the ESP-IDF and allows to use it in an easy "Arduino-way".

![Screenshot of console output](screenshot.png)

## Features
* Simple to use
* Navigatable history, autocompletion with tab for commands (when using an ANSI terminal)
* Persistent history if wished (history gets saved across reboots)
* Many useful commands included like showing infos about system, memory, network and more (see [commands.md](commands.md) for more info)
* Easy to implement own commands
* Customizable prompt
* Console works in its own asynchronous task, so you can use your arduino loop() function as you like

## Usage

### Included commands
ESP32Console includes many useful commands, which can be registered using their respective `registerXXX()` functions. See [commands.md](commands.md) for a detailed list of the commands.

### Examples
A simple usage can be seen here (see `examples/simple.ino`):
More advanced usages can be found in `examples/` folder.

```
#include <Arduino.h>

#include "ESP32Console.h"

using namespace ESP32Console;

Console console;

constexpr int LED = 2;

int led(int argc, char **argv)
{
    //Ensure that we have an argument to parse
    if (argc != 2)
    {
        printf("You have to give 'on' or 'off' as a argument (e.g. 'led on')\n");
        
        //Return EXIT_FAILURE if something did not worked.
        return EXIT_FAILURE;
    }
    
    //Take the first argument...
    auto arg = String(argv[1]);

    //and use it to decide what to do with the LED
    if (arg == "on") {
        digitalWrite(LED, HIGH);
        printf("LED is now on\n");
    } else if(arg == "off") {
        digitalWrite(LED, LOW);
        printf("LED is now off\n");
    } else {
        printf("Unknown argument!\n");
        return EXIT_FAILURE;
    }
    
    //Return EXIT_SUCCESS if everything worked as intended.
    return EXIT_SUCCESS;
}

void setup()
{
    pinMode(LED, OUTPUT);

    //You can change the console prompt before calling begin(). By default it is "ESP32>"
    console.setPrompt("MyConsole>");

    console.begin(115200);

    //Register builtin commands like 'reboot', 'sysinfo', or 'meminfo'
    console.registerSystemCommands();

    //Register our own command
    //First argument is the name with which the command can be executed, second argument is the function to execute and third one is the description shown in help command.
    console.registerCommand(ConsoleCommand("led", &led, "Turn the LED on or off"));

    //When console is in use, we can not use Serial.print but you can use printf to output text
    printf("\n\nWelcome to ESP32Console example. Try out typing 'led off' and 'led on' (without quotes) or see 'help' for all commands.");
}

void loop()
{
    //Console works async in its own task, so you can do whatever you want in your loop() function.
}
```

## Credits
This library utilizes the console component of ESP-IDF written by Espressif at core. Argument parsing is done by [cxxopts](https://github.com/jarro2783/cxxopts).

## LICENSE
ESP32Console is licensed under MIT LICENSE. See [LICENSE file](LICENSE) for more info.
