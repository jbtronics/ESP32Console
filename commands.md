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

## Network commands (loaded by calling registerNetworkCommands())

* `ipconfig`: Shows information about WiFi connection

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