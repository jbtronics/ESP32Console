#include "./InputParser.h"

#include <Arduino.h>

namespace ESP32Console
{
    String interpolateLine(const char *in_)
    {
        String in(in_);
        String out = in;

        // Add a space at end of line, this does not change anything for our consoleLine and makes parsing easier
        in = in + " ";

        // Interpolate each $ with the env variable if existing. If $ is the first character in a line it is not interpolated
        int var_index = 1;
        while ((var_index = in.indexOf("$", var_index + 1)) > 0)
        {
            /**
             * Extract the possible env variable
             */
            int variable_start = var_index + 1;
            // If the char after $ is a { we look for an closing }. Otherwise we just look for an space
            char delimiter = ' ';
            if (in.charAt(variable_start) == '{')
            {
                // Our variable starts then at the character after ${
                variable_start++;
            }

            int variable_end = in.indexOf(delimiter, variable_start + 1);
            // If delimiter not found look for next possible env variable
            if (variable_end == -1)
            {
                continue;
            }

            String env_var = in.substring(variable_start, variable_end);
            env_var.trim();
            // Depending on whether this is an variable string, we have to include the next character
            String replace_target = in.substring(var_index, delimiter == '}' ? variable_end + 1 : variable_end);

            // Check if we have an env with this name, then replace it
            const char *value = getenv(env_var.c_str());
            if (value)
            {
                out.replace(replace_target.c_str(), value);
            }
        }

        return out.c_str();
    }
}