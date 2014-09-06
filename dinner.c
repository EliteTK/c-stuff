#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {
        sleep(1);
        printf("Start:\a\n");
        for (int i = 0; i < 45; i += 5) {
                sleep(300);
                printf("Check water levels.\a\n");
                if (i == 24) {
                        printf("Add stuff from plate.\n");
                }
        }

        printf("All done.\a\n");

        return 0;
}
