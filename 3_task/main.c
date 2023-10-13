//
//  main.c
//  3
//
//  Created by Лена on 12.10.2023.
//

#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE_OF_BUFFER 16384

enum status_codes
{
    fsc_ok,
    fsc_overflow,
    fsc_invalid_parameter,
    fsc_unknown,
    fsc_memory_error_detected,
};

int main(int argc, const char * argv[])
{
    enum status_codes function_result = fsc_unknown;
    
    function_result = (argc < 3) ? fsc_invalid_parameter : fsc_ok;
    
    if (function_result == fsc_ok)
    {
        FILE* file_input = fopen(argv[1], "rb");
        FILE* file_output;
        if (file_input == NULL)
            function_result = fsc_memory_error_detected;
        else
        {
            file_output = fopen(argv[2], "wb");
            if (file_output == NULL)
            {
                function_result = fsc_memory_error_detected;
                fclose(file_input);
            }
            else
            {
                char buffer[MAX_SIZE_OF_BUFFER];
                unsigned long col_of_read_correctly = MAX_SIZE_OF_BUFFER;
                while (col_of_read_correctly != 0)
                {
                    fread(buffer, sizeof(char), MAX_SIZE_OF_BUFFER, file_input);
                    fwrite(buffer, sizeof(char), col_of_read_correctly, file_output);
                }
                fclose(file_input);
                fclose(file_output);
            }
        }
    }
    
    switch (function_result)
    {
        case fsc_ok:
            break;
        case fsc_overflow:
            printf("Overflow detected\n");
            break;
        case fsc_invalid_parameter:
            printf("Invalid parameter detected\n");
            break;
        case fsc_memory_error_detected:
            printf("Memory error detected\n");
            break;
        default:
            printf("function_result is unknown\n");
    }
    
    return function_result == fsc_ok ? 0 : 1;
}
