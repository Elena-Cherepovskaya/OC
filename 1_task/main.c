//
//  main.c
//  1
//
//  Created by Лена on 09.10.2023.
//

#include <stdio.h>
#include <string.h>

enum status_codes
{
    fsc_ok,
    fsc_overflow,
    fsc_invalid_parameter,
    fsc_unknown,
    error_create_file,
};

int main(int argc, const char * argv[])
{
    
    enum status_codes function_result = argc < 2 ? fsc_invalid_parameter : fsc_ok;
    FILE* file_input = fopen(argv[1], "w");
    
    function_result = (file_input != NULL) ? fsc_ok : error_create_file;
    
    if (function_result == fsc_ok)
    {
        char bytes_list[] = {3,1,4,1,5,9,2,6,5,3,5};
        /*int i = 0;
        while (bytes_list[i] != 0)
        {
            printf("%c\n", bytes_list[i] + '0');
            ++i;
        }*/
        
        fwrite(bytes_list, sizeof(char), sizeof(bytes_list), file_input);
        fclose(file_input);
        
        char c;
        FILE* file_input = fopen(argv[1], "r");

        while (fread(&c, sizeof(char), 1, file_input))
        {
            printf("current position in (some) buffer: %uc\n", *(file_input->_p));
            printf("read space left for getc(): %s\n", file_input->_p);
            printf("write space left for putc(): %d\n", file_input->_w);
            printf("flags, below; this FILE is free if 0: %hd\n", file_input->_flags);
            printf("fileno, if Unix descriptor, else -1: %hd\n", file_input->_file);
            printf("0 or -_bf._size, for inline putc: %d\n", file_input->_lbfsize);
            printf("saved _r when _r is counting ungetc data: %d\n", file_input->_ur);
            
            printf("guarantee an ungetc() buffer: \n");
            for (int i = 0; i < 3; ++i)
                printf("%uc ", file_input->_ubuf[i]);
            printf("\n");
            
            printf("guarantee a getc() buffer: \n");
            for (int i = 0; i < 3; ++i)
                printf("%uc ", file_input->_nbuf[i]);
            printf("\n");
            
            printf("stat.st_blksize (may be != _bf._size: %d\n", file_input->_blksize);
            
            printf("%d", c);
            printf("\n\n");
        }
        fclose(file_input);
        file_input = fopen(argv[1], "r");
        
        fseek(file_input, 3, SEEK_SET);
        char bytes_buffer[5];
        fread(bytes_buffer, sizeof(char), 4, file_input);
        
        fclose(file_input);
        int i = 0;
        while (bytes_buffer[i] != 0)
        {
            printf("%d ", bytes_buffer[i]);
            ++i;
        }
        printf("\n");
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
        case error_create_file:
            printf("Error create file detected\n");
            break;
        default:
            printf("error_create_file\n");
    }
    
    return function_result == fsc_ok ? 0 : 1;
}
