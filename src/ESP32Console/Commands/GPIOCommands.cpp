#include "./GPIOCommands.h"
#include "Arduino.h"

static int _pinmode(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("You have to pass a pin number and mode. Syntax: pinMode [GPIO] [MODE]\n");
        return 1;
    }

    char *pin_str = argv[1];
    String mode_str = String(argv[2]);

    unsigned long pin = 0;

    try
    {
        pin = std::stoul(pin_str);
    }
    catch (std::invalid_argument ex)
    {
        fprintf(stderr, "Invalid argument for pin: %s\n", ex.what());
        return 1;
    }

    if (pin > 255 || !digitalPinIsValid(pin)) {
        fprintf(stderr, "%d is not a GPIO pin\n", pin);
        return 1;
    }

    int mode = INPUT;

    if (mode_str.equalsIgnoreCase("INPUT"))
    {
        mode = INPUT;
    }
    else if (mode_str.equalsIgnoreCase("OUTPUT"))
    {
        mode = OUTPUT;
    }
    else if (mode_str.equalsIgnoreCase("INPUT_PULLUP"))
    {
        mode = INPUT_PULLUP;
    }
    else if (mode_str.equalsIgnoreCase("INPUT_PULLDOWN"))
    {
        mode = INPUT_PULLDOWN;
    }
    else if (mode_str.equalsIgnoreCase("OUTPUT_OPEN_DRAIN"))
    {
        mode = OUTPUT_OPEN_DRAIN;
    }
    else
    {
        fprintf(stderr, "Invalid mode: Allowed modes are INPUT, OUTPUT, INPUT_PULLUP, INPUT_PULLDOWN, OUTPUT_OPEN_DRAIN\n");
    }

    pinMode(pin, mode);
    printf("Mode set successful.\n");

    return 0;
}

static int _digitalWrite(int argc, char** argv)
{
    if (argc != 3)
    {
        printf("You have to pass an pin number and level. Syntax: digitalWrite [GPIO] [Level]\n");
        return 1;
    }

    char *pin_str = argv[1];
    String mode_str = String(argv[2]);

    unsigned long pin = 0;

    try
    {
        pin = std::stoul(pin_str);
    }
    catch (std::invalid_argument ex)
    {
        fprintf(stderr, "Invalid argument for pin: %s\n", ex.what());
        return 1;
    }

    if (pin > 255 || !digitalPinCanOutput(pin)) {
        fprintf(stderr, "%d is not a GPIO pin\n", pin);
        return 1;
    }

    int mode = LOW;

    if (mode_str.equalsIgnoreCase("HIGH")  || mode_str.equalsIgnoreCase("1"))
    {
        mode = HIGH;
    }
    else if (mode_str.equalsIgnoreCase("LOW") || mode_str.equalsIgnoreCase("0"))
    {
        mode = LOW;
    } else
    {
        fprintf(stderr, "Invalid mode: Allowed levels are HIGH, LOW, 0 and 1\n");
    }

    pinMode(pin, mode);
    printf("Output set successful.\n");

    return 0;
}

static int _digitalRead(int argc, char** argv)
{
    if (argc != 2)
    {
        printf("You have to pass an pin number to read\n");
        return 1;
    }

    char *pin_str = argv[1];

    unsigned long pin = 0;

    try
    {
        pin = std::stoul(pin_str);
    }
    catch (std::invalid_argument ex)
    {
        fprintf(stderr, "Invalid argument for pin: %s\n", ex.what());
        return 1;
    }

    if (pin > 255 || !digitalPinCanOutput(pin)) {
        fprintf(stderr, "%d is not a GPIO pin\n", pin);
        return 1;
    }

    auto level = digitalRead(pin);

    if(level == HIGH) {
        printf("HIGH\n");
    } else if(level == LOW) {
        printf("LOW\n");
    } else {
        fprintf(stderr, "Unknown state (%u) of pin %u!\n", level, pin);
        return 1;
    }

    return 0;
}

static int _analogRead(int argc, char** argv)
{
    if (argc != 2)
    {
        printf("You have to pass an pin number to read\n");
        return 1;
    }

    char *pin_str = argv[1];

    unsigned long pin = 0;

    try
    {
        pin = std::stoul(pin_str);
    }
    catch (std::invalid_argument ex)
    {
        fprintf(stderr, "Invalid argument for pin: %s\n", ex.what());
        return 1;
    }

    if (pin > 255 || digitalPinToAnalogChannel(pin) == -1) {
        fprintf(stderr, "%d is not a ADC pin\n", pin);
        return 1;
    }

    auto value = analogReadMilliVolts(pin);
    
    printf("%u mV\n", value);

    return 0;
}



namespace ESP32Console::Commands
{
    const ConsoleCommand getPinModeCommand()
    {
        return ConsoleCommand("pinMode", &_pinmode, "Changes the pinmode of an GPIO pin (similar to Arduino function)");
    }

    const ConsoleCommand getDigitalWriteCommand()
    {
        return ConsoleCommand("digitalWrite", &_digitalWrite, "Writes the state of an ouput pin (similar to Arduino function)");
    }

    const ConsoleCommand getDigitalReadCommand()
    {
        return ConsoleCommand("digitalRead", &_digitalRead, "Reads the state of an input pin (similar to Arduino function)");
    }

    const ConsoleCommand getAnalogReadCommand()
    {
        return ConsoleCommand("analogRead", &_analogRead, "Show the voltage at an analog pin in millivollts.");
    }
}