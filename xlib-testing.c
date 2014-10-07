/*
 * Copyright (C) 2014  Tomasz Kramkowski <tk@the-tk.com>
 *
 * This program is free software. It is licensed under version 3 of the
 * GNU General Public License.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see [http://www.gnu.org/licenses/].
 */

#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    Display *d = XOpenDisplay(NULL);
    if (!d) {
        fprintf(stderr, "Could not open display.");
        exit(1);
    }

    unsigned long int black = BlackPixel(d, DefaultScreen(d));
    unsigned long int white = WhitePixel(d, DefaultScreen(d));

    Window w = XCreateSimpleWindow(d, DefaultRootWindow(d), 0, 0, 300, 300, 0, black, white);

    XSelextInput(d, w, StructureNotifyMask);

    XMapWindow(d, w);

    GC gc = XCreateGC(d, w, 0, NULL);

    XSetForeground(d, gc, white);

    while(1) {
        XEvent e;
        XNextEvent(d, &e);
        if (e.type == MapNotify)
            break;
    }

    XDrawLine(d, w, gc, 10, 60, 180, 20);

    XFlush(d);

    sleep(10);

    XCloseDisplay(d);
}
