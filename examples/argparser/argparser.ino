/**
 * This example demonstrates the usage of OptionsConsoleCommand, which allows you to easily build commands with complex options and argument parsing.
 */

#include <Arduino.h>

#include "ESP32Console.h"

using namespace ESP32Console;

Console console;

void setup()
{
    console.begin(115200);

    // Define a new command. Every command has an --option argument which shows the possible arguments and (if defined) a --version option which shows the version of this command.
    OptionsConsoleCommand test(
        "test",                                                                 // The command name
        [](int argc, char **argv, ParseResult result, Options options) -> int { // The function which is called when command is called. You get the parsed arguments and the options object
            
            printf("Lambda function test\n");

            // Check if argument was passed, then print it:
            if (result.count("i"))
            {
                int i = result["i"].as<int>();
                printf("Selected mode: %d\n", i);
            }

            return EXIT_SUCCESS;
        },
        "Just a test command!",
        "v1.0.0"); //You can define a version number which is shown when the command is called with --version

    //Customize the options of the console object. See https://github.com/jarro2783/cxxopts for explaination
    test.options.add_options()("i,integer", "Int param", cxxopts::value<int>());

    //Register it like any other command
    console.registerCommand(test);
}

void loop()
{
    // Console works async in its own task, so you can do whatever you want in your loop() function.
}