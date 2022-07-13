# Included command reference

## Core commands (automatically loaded, when begin() is called)

* `help`: Show a list of all possible commands with descriptions
* `clear`: Clear terminal screen using ANSI commands (only working when using an ANSI compatible terminal)
* `echo`: Echo the parameter strings
* `history`: Show the recent command history
* `multiline_mode`: Switch multiline mode on or off. When it is on, lines get break into a second line, if it gets too long.
* `env`: List all environment variables
* `declare`: Change the value of an environment variable (syntax: `declare VARIABLE Value` or `declare VARIABLE "Long Value"`)

## System commands (loaded by calling registerSystemCommands())

* `sysinfo`: Prints info about the chip model, revision, ESP-IDF version, EFuse MAC, flash and PSRAM
* `restart`: Restarts the system
* `meminfo`: Show informations about used and free Heap
* `date`: Shows and set the current system time. Change time with `date -s "2022-07-13 22:47:00"`. Timezone can be set by changing the `TZ` env variable (e.g. `declare TZ CET-1`).

## Network commands (loaded by calling registerNetworkCommands())

* `ipconfig`: Shows information about WiFi connection
* `ping [HOST]`: Pings a hostname. You can change the number of pings done with `-n`parameter. Use `-n 0` for infinite pinging. You can stop the ping by `Strg + C` or `Strg + D`.

## VFS commands (loaded by calling registerVFSCommands())

This functions allows you to navigate through and edit files in ESP-IDFs Virtual Filesystem. Things likes SPIFF, SDCards, some hardware and more are getting mounted into VFS with different prefixes.
The following commands allow an unified access on it.

* `pwd`: Show the current working directory (the directory we are currently in)
* `cd [PATH]`: Change the current directory
* `ls [PATH]`: List the contents of the current or given directory
* `cat [FILES...]`: Show the content of the given files
* `rm [FILE]`: Delete the given file
* `rmdir [DIR]`: Delete the given director
* `mv [ORIGIN] [TARGET]`: Moves/Rename the file to new name/posiion
* `cp [ORIGIN] [TARGET]`: Copies the contents of origin to target file
* `edit [FILE]`: Opens a file editor with a visual editor. Use `Strg + S` to save, `Strg + Q` to quit and `Strg + F` to search in file.

## GPIO commands (loaded by calling registerGPIOCommands())
The commands allow you to read and change the states of the ESPs GPIO pins. They are similar to the arduino included functions:

* `pinMode [PIN] [MODE]`: Change the pinMode of an GPIO
* `digitalRead [PIN]`: Reads the state of an digital GPIO
* `digitalWrite [PIN] [LEVEL]`: Changes the state of an digital GPIO
* `analogRead [PIN]`: Reads the voltage applied to an analog GPIO in millivolts