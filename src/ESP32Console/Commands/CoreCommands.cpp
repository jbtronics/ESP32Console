#include "./CoreCommands.h"
#include "linenoise/linenoise.h"
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
    /*
    argparse::ArgumentParser program(argv[0]);
    
    program.add_argument("mode")
        .help("Set to 1 to activate multiline mode, set to 0 set to singleline mode.")
        .scan<'i', int>();

    try
    {
        program.parse_args(argc, argv);

        auto mode = program.get<int>("mode");
        if (mode != 0 && mode != 1)
        {
            throw std::runtime_error("Invalid argument value. mode must be either 0 or 1!");
            return EXIT_FAILURE;
        }

        linenoiseSetMultiLine(mode);
        printf("Multiline mode set.\n");
    }
    catch (const std::runtime_error &err)
    {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        return EXIT_FAILURE;
    }*/

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
        return ConsoleCommand("set_multiline_mode", &set_multiline_mode, "Sets the multiline mode of the console", "(See set_multiline_mode --help for more infos.)");
    }
}