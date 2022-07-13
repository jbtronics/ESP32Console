/**
 * This example demonstrates the usage of the builtin network functions
 */

#include <Arduino.h>
#include "ESP32Console.h"
#include <WiFi.h>

#include "ESP32Console/Helpers/PWDHelpers.h"

using namespace ESP32Console;

Console console;

const char *ssid = "yourSSID";
const char *password = "yourWLAN";

void setup()
{    
    //Connect to WiFi
    WiFi.begin(ssid, password);

    console.begin(115200);
    console.registerSystemCommands();
    
    //Register network commands
    console.registerNetworkCommands();
}

void loop()
{
    
}