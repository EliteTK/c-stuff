/*
 * Copyright (C) 2014  Tomasz Kramkowski <tk@the-tk.com>
 *
 * This program is free software. It is licensed under version 3 of the
 * GNU General Public License.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see [http://www.gnu.org/licenses/].
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>

int main()
{
        int fbfd = 0;
        struct fb_var_screeninfo vinfo;
        struct fb_fix_screeninfo finfo;
        long int screensize = 0;
         char *fbp = 0;
        int x = 0, y = 0;
        long int location = 0;
        int count ;

        /* Open the file for reading and writing */
        fbfd = open("/dev/fb0", O_RDWR);
        if (!fbfd) {
                printf("Error: cannot open framebuffer device.\n");
                exit(1);
        }
        printf("The framebuffer device was opened successfully.\n");
     /* Get fixed screen information */
        if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo)) {
               printf("Error reading fixed information.\n");
                exit(2);
        }

        /* Get variable screen information */
        if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo)) {
                printf("Error reading variable information.\n");
                exit(3);
        }

        /* Figure out the size of the screen in bytes */
        screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;
        printf("\nScreen size is %d",screensize);
        printf("\nVinfo.bpp = %d",vinfo.bits_per_pixel);

        /* Map the device to memory */
        fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED,fbfd, 0);
        if ((int)fbp == -1) {
                printf("Error: failed to map framebuffer device to memory.\n");
                exit(4);
        }
         printf("The framebuffer device was mapped to memory successfully.\n");


        x = 100; y = 100; /* Where we are going to put the pixel */

        /* Figure out where in memory to put the pixel */
        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (y+vinfo.yoffset) * finfo.line_length;
        for(count = 1 ;count < 100 ;count++)
        {
                *(fbp + location) = 255;    /* Some blue */
                *(fbp + location + count) = 0; /* A little green */
                *(fbp + location + count + 1) = 0; /* A lot of red */
                *(fbp + location + count + 2) = 0; /* No transparency */
        }
        munmap(fbp, screensize);
        close(fbfd);
        return 0;
}
