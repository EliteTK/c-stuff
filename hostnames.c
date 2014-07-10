#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
        if (argc != 2) {
                fprintf(stderr, "Usage: %s <domain-name>\n", argv[0]);
                exit(1);
        }

        struct hostent* he;

        he = gethostbyname(argv[1]);

        if (!he) {
                fputs("Error, could not resolve.\n", stderr);
                exit(1);
        }

        char str[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, he->h_addr, str, INET_ADDRSTRLEN);

        printf("%s\n", str);
        return 0;
}
