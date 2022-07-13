/**
 * This example demonstrates the usage of the builtin VFS commands and persistent history
 */

#include <Arduino.h>
#include "ESP32Console.h"
#include <FS.h>
#include "SPIFFS.h"
#include "ESP32Console/Helpers/PWDHelpers.h"

using namespace ESP32Console;

Console console;

void setup()
{
    //Initalize SPIFFS and mount it on /spiffs
    SPIFFS.begin(true, "/spiffs");

    //Modify prompt to show current file path (%pwd% get replaced by the filepath)
    console.setPrompt("ESP32 %pwd%> ");
    
    //Set HOME env for easier navigating (type cd to jump to home)
    setenv("HOME", "/spiffs", 1);
    //Set PWD to env
    console_chdir("/spiffs");
    
    console.begin(115200);

    //Enable the saving of our command history to SPIFFS. You will be able to see it, when you type ls in your console.
    console.enablePersistentHistory("/spiffs/.history.txt");

    console.registerSystemCommands();

    //Register the VFS specific commands
    console.registerVFSCommands();
}

void loop()
{
}