/**
 * This example demonstrates the usage of ESP32Console on a seperate UART channel, using its own Pins, which allows you to use
 * the console besides normal Serial.* commands
 */

#include <Arduino.h>
#include "ESP32Console.h"

using namespace ESP32Console;

Console console;

void setup()
{   
    //Initialize Serial port on UART0 (the onboard USB Serial Converter)
    Serial.begin(115200);
    
    //Enable ESP32Console on Pin 12 & 14 on UART1
    console.begin(115200, 12, 14, 1);


    console.registerSystemCommands();
    console.registerNetworkCommands();
}

void loop()
{
    //We can use Serial on UART0 as usual, while ESP32Console is available on the Pins above.
    Serial.println("Test");
    delay(1000);
}