#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

unsigned long long int get_seconds(char *);

void usage(char *cmd)
{
    printf("Usage:\n"
           "    %s <n>{s,m,h,D,M,Y} ...\n", cmd);
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Not enough arguments.\n");
        usage(argv[0]);
        exit(1);
    }

    unsigned long long int total_seconds = 0;

    int i;
    for (i = 1; i < argc; i++)
        total_seconds += get_seconds(argv[i]);

    printf("Total time: %llu second(s).\n", total_seconds);

    return 0;
}

unsigned long long int get_seconds(char *code)
{
    int length = strlen(code);
    if (length < 2) {
        return 0;
    }

    int multiplier = 0;
    char suffix = code[length - 1];
    switch (suffix) {
        case 's': multiplier = 1; break; // 1 second
        case 'm': multiplier = 60; break; // 1 minute
        case 'h': multiplier = 3600; break; // 1 hour
        case 'D': multiplier = 86400; break; // 1 day
        case 'M': multiplier = 2419200; break; // 28 days
        case 'Y': multiplier = 31536000; break; // 365 days
        default : return 0;
    }

    char value[length + 1];
    strcpy(value, code);

    value[length - 1] = '\0';

    return strtoull(value, NULL, 10) * multiplier;
}
