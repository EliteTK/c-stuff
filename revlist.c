#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if(argc != 3){
        fprintf(stderr, "Incorrect argument count.\nUsage: %s <string> <separator>\n"\
               , argv[0]);
        exit(1);
    }

    char *input = argv[1];
    char separator = argv[2][0];
    int length = strlen(input), startpos = 0, strpos;

    char *output = malloc(length);

    for(strpos = 0; strpos <= length; strpos ++){
        if(input[strpos] == separator || strpos == length){
            strncpy(output + length - strpos, input + startpos, strpos - startpos);
            if(strpos != length)
                output[length - strpos - 1] = separator;
            startpos = strpos + 1;
        }
    }

    printf("%s\n", output);
    free(output);
    return 0;
}
