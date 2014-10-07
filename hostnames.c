/*
 * Resolve domain.
 *
 * Copyright (C) 2014  Tomasz Kramkowski <tk@the-tk.com>
 *
 * This program is free software. It is licensed under version 3 of the
 * GNU General Public License.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see [http://www.gnu.org/licenses/].
 */

// I once spent 3 hours trying to manually do this by sending DNS name
// resolution requests.

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
