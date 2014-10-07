// Imlib2 stuff which I think I copied from somewhere.

#include <Imlib2.h>
#include <X11/Xlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

Display *disp;
Window win;
Visual *vis;
Colormap cm;
int depth;

int main(int argc, char **argv)
{
        XEvent ev;

        Imlib_Updates updates, current_update;
        Imlib_Image buffer;
        Imlib_Font font;
        Imlib_Color_Range range;
        int mouse_x = 0, mouse_y = 0;

        disp = XOpenDisplay(NULL);

        vis = DefaultVisual(disp, DefaultScreen(disp));
        depth = DefaultDepth(disp, DefaultScreen(disp));
        cm = DefaultColormap(disp, DefaultScreen(disp));

        win = XCreateSimpleWindow(disp, DefaultRootWindow(disp),
                        0, 0, 640, 480, 0, 0, 0);

        XSelectInput(disp, win, ButtonPressMask | ButtonReleaseMask |
                        PointerMotionMask | ExposureMask);

        XMapWindow(disp, win);

        imlib_set_cache_size(2048 * 1024);

        imlib_set_font_cache_size(512 * 1024);

        imlib_add_path_to_font_path("./ttfonts");

        imlib_set_color_usage(128);

        imlib_context_set_dither(1);

        imlib_context_set_display(disp);
        imlib_context_set_visual(vis);
        imlib_context_set_colormap(cm);
        imlib_context_set_drawable(win);

        while(true) {
                Imlib_Image image;
                int w, h, text_w, text_h;

                updates = imlib_updates_init();

                do {
                        XNextEvent(disp, &ev);
                        switch (ev.type) {
                                case Expose:
                                        updates = imlib_update_append_rect(updates,
                                                        ev.xexpose.x, ev.xexpose.y,
                                                        ev.xexpose.width, ev.xexpose.height);
                                        break;
                                case ButtonPress:
                                        exit(0);
                                        break;
                                case MotionNotify:
                                        image = imlib_load_image("./test_images/mush.png");
                                        imlib_context_set_image(image);
                                        w = imlib_image_get_width();
                                        h = imlib_image_get_height();

                                        imlib_context_set_image(image);
                                        imlib_free_image();

                                        updates = imlib_update_append_rect(updates,
                                                        mouse_x - (w / 2), mouse_y - (h / 2),
                                                        w, h);
                                        font = imlib_load_font("notepad/30");
                                        if (font) {
                                                char text[4096];
                                                imlib_context_set_font(font);
                                                sprintf(text, "Mouse is at %i, %i", mouse_x, mouse_y);
                                                imlib_get_text_size(text, &text_w, &text_h);
                                                imlib_free_font();

                                                updates = imlib_update_append_rect(updates,
                                                                320 - text_w / 2, 240 - text_h / 2,
                                                                text_w, text_h);
                                        }

                                        mouse_x = ev.xmotion.x;
                                        mouse_y = ev.xmotion.y;

                                        updates = imlib_update_append_rect(updates,
                                                        mouse_x - w / 2, mouse_y - h / 2,
                                                        w, h);
                                        font = imlib_load_font("notepad/30");
                                        if (font) {
                                                char text[4096];

                                                imlib_context_set_font(font);
                                                sprintf(text, "Mouse is at %i, %i", mouse_x, mouse_y);
                                                imlib_get_text_size(text, &text_w, &text_h);
                                                imlib_free_font();
                                                updates = imlib_update_append_rect(updates,
                                                                320 - text_w / 2, 240 - text_h / 2,
                                                                text_w, text_h);
                                        }
                                default:
                                        break;
                        }
                } while (XPending(disp));


                updates = imlib_updates_merge_for_rendering(updates, 640, 480);
                for (current_update = updates;
                                current_update;
                                current_update = imlib_updates_get_next(current_update)) {
                        int up_x, up_y, up_w, up_h;

                        imlib_updates_get_coordinates(current_update, &up_x, &up_y, &up_w, &up_h);

                        buffer = imlib_create_image(up_w, up_h);

                        imlib_context_set_blend(1);

                        image = imlib_load_image("./test_images/bg.png");

                        imlib_context_set_image(image);

                        w = imlib_image_get_width();
                        h = imlib_image_get_height();

                        imlib_context_set_image(buffer);

                        if (image) {
                                imlib_blend_image_onto_image(image, 0, 0, 0,
                                                w, h, -up_x, -up_y, 640, 480);

                                imlib_context_set_image(image);

                                imlib_free_image();
                        }

                        image = imlib_load_image("./test_images/mush.png");
                        imlib_context_set_image(image);
                        w = imlib_image_get_width();
                        h = imlib_image_get_height();
                        imlib_context_set_image(image);
                        if (image) {
                                imlib_blend_image_onto_image(image, 0, 0, 0, w, h,
                                                mouse_x - w / 2 - up_x,
                                                mouse_y - h / 2 - up_y,
                                                w, h);
                                imlib_context_set_image(image);
                                imlib_free_image();
                        }

                        range = imlib_create_color_range();
                        imlib_context_set_color_range(range);

                        imlib_context_set_color(255, 255, 255, 255);
                        imlib_add_color_to_color_range(0);

                        imlib_context_set_color(255, 200, 10, 100);
                        imlib_add_color_to_color_range(10);

                        imlib_context_set_color(0, 0, 0, 0);
                        imlib_add_color_to_color_range(20);

                        imlib_context_set_image(buffer);
                        imlib_image_fill_color_range_rectangle(-up_x, -up_y, 128, 128, -45);

                        imlib_free_color_range();

                        font = imlib_load_font("notepad/30");
                        if (font) {
                                char text[4096];

                                imlib_context_set_font(font);
                                imlib_context_set_image(buffer);
                                imlib_context_set_color(0, 0, 0, 255);
                                sprintf(text, "Mouse is at %i, %i", mouse_x, mouse_y);
                                imlib_get_text_size(text, &text_w, &text_h);
                                imlib_text_draw(320 - text_w / 2 - up_x,
                                                240 - text_h / 2 - up_y,
                                                text);
                                imlib_free_font();
                        }

                        imlib_context_set_blend(0);
                        imlib_context_set_image(buffer);
                        imlib_render_image_on_drawable(up_x, up_y);
                        imlib_free_image();
                }
                if (updates)
                        imlib_updates_free(updates);
        }
        return 0;
}

        /*Imlib_Image image = imlib_create_image(640, 480);*/

        /*imlib_context_set_image(image);*/

        /*imlib_context_set_color(255, 255, 255, 255);*/

        /*imlib_image_fill_rectangle(0, 0, 640, 480);*/

        /*imlib_context_set_color(255, 128, 0, 255);*/

        /*ImlibPolygon poly = imlib_polygon_new();*/

        /*imlib_polygon_add_point(poly, 0, 0);*/
        /*imlib_polygon_add_point(poly, 10, 440);*/
        /*imlib_polygon_add_point(poly, 600, 10);*/

        /*imlib_image_fill_polygon(poly);*/

        /*imlib_polygon_free(poly);*/

        /*imlib_save_image("imlibtest.png");*/

        /*imlib_free_image();*/

        /*return 0;*/
/*}*/
