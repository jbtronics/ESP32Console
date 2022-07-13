/**
 * This example demonstrates the usage of the internal GPIO functions and the env variables interpolation
 */

#include <Arduino.h>
#include "ESP32Console.h"

#include "ESP32Console/Helpers/PWDHelpers.h"

using namespace ESP32Console;

Console console;

void setup()
{    

    console.begin(115200);
    console.registerSystemCommands();
    
    /**
     * Set environment variables, so users can access pin numbers easily in console.
     * Users can do commands like `digitalWrite $LED HIGH` which will then be expanded to `digitalWrite 10 HIGH`.
     * Users can change these env variables or create new ones dynamically in the console by `declare LED 10`.
     */
    setenv("LED", "10", 1);
    setenv("BUTTON", "4", 1);

    /**
     * Users can list all defined env variables and their values by `env` command
     */

    //Register GPIO commands
    console.registerGPIOCommands();
}

void loop()
{
    
}