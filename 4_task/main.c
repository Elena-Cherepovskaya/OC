//
//  main.c
//  4
//
//  Created by Лена on 12.10.2023.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

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
        const char* list_of_flag[] = {"xor8", "xor32", "mask"};
        const char* flag;
        FILE* file_input = fopen(argv[1], "rb");
        if (file_input == NULL)
            function_result = fsc_memory_error_detected;
        else
        {
            flag = argv[2];
            int num_of_flag = -1;
            int i = 0;
            while (list_of_flag[i] != 0)
            {
                if (strcmp(flag, list_of_flag[i]) == 0)
                {
                    num_of_flag = i;
                    break;
                }
                ++i;
            }
            
            switch (num_of_flag)
            {
                case 0:
                {
                    uint8_t c;
                    uint8_t res = 0;
                    while (fread(&c, sizeof(c), 1, file_input))
                        res ^= c;
                    printf("%d\n", res);
                    break;
                }
                case 1:
                {
                    uint32_t c;
                    uint32_t res = 0;
                    while(fread(&c, sizeof(c), 1, file_input))
                    {
                        res ^= c;
                        c = 0;
                    }
                    printf("%d\n", res);
                    break;
                }
                case 2:
                {
                    if (argc < 3)
                        function_result = fsc_invalid_parameter;
                    else
                    {
                        uint32_t mask;
                        uint32_t value;
                        mask = (unsigned int)strtol(argv[2], NULL, 16);
                        int col = 0;
                        while(fread(&value, sizeof(value), 1, file_input))
                        {
                            if ((mask & value) == mask)
                                ++col;
                            value = 0;
                        }
                        printf("%d\n", col);
                    }
                    break;
                }
                default:
                    break;
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
