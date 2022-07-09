#include "./CoreCommands.h"
#include "linenoise/linenoise.h"
#include "Arduino.h"
//#include "argparse/argparse.hpp"

static int clear(int argc, char **argv)
{
    // If we are on a dumb erminal clearing does not work
    if (linenoiseProbe())
    {
        printf("\nYour terminal does not support escape sequences. Clearing screen does not work!\n");
        return EXIT_FAILURE;
    }

    linenoiseClearScreen();
    return EXIT_SUCCESS;
}

static int echo(int argc, char **argv)
{
    // Echo implemenation similar to GNU coreutils
    while (argc > 0)
    {
        printf(argv[0]);
        argc--;
        argv++;
        if (argc > 0)
        {
            printf("");
        }
    }
    printf("\n");

    return EXIT_SUCCESS;
}

static int set_multiline_mode(int argc, char **argv)
{
    if (argc != 2) {
        printf("You have to give 'on' or 'off' as an argument!\n");
        return EXIT_FAILURE;
    }

    //Get argument
    auto mode = String(argv[1]);
    //Normalize
    mode.toLowerCase();
    
    if(mode == "on") {
        linenoiseSetMultiLine(1);
    } else if (mode == "off") {
        linenoiseSetMultiLine(0);
    }
    else {
        printf("Unknown option. Pass 'on' or 'off' (without quotes)!\n");
        return EXIT_FAILURE;
    }

    printf("Multiline mode set.\n");

    return EXIT_SUCCESS;
}

namespace ESP32Console::Commands
{
    const ConsoleCommand getClearCommand()
    {
        return ConsoleCommand("clear", &clear, "Clears the screen using ANSI codes");
    }

    const ConsoleCommand getEchoCommand()
    {
        return ConsoleCommand("echo", &echo, "Echos the text supplied as argument");
    }

    const ConsoleCommand getSetMultilineCommand()
    {
        return ConsoleCommand("multiline_mode", &set_multiline_mode, "Sets the multiline mode of the console");
    }
}