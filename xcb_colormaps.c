#include <stdlib.h>
#include <stdio.h>
#include <xcb/xcb.h>
#include <xcb/xcb_image.h>
#include <xif.h>
#include <time.h>

#define WIDTH 640
#define HEIGHT 480

void perlin(uint8_t * const, uint16_t, uint16_t);

int main(int arg, char **argv)
{
        srand(time(NULL));
        xcb_connection_t *connection = xcb_connect(NULL, NULL);

        xcb_screen_t *screen = xcb_setup_roots_iterator(xcb_get_setup(connection)).data;

        xcb_colormap_t colormap = screen->default_colormap;

        xcb_drawable_t window = xcb_generate_id(connection);
        uint32_t mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
        uint32_t values[] = {screen->black_pixel, XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_BUTTON_PRESS};
        xcb_create_window(connection,
                        /*screen->root_depth,*/
                        24,
                        window,
                        screen->root,
                        0, 0,
                        WIDTH, HEIGHT,
                        1,
                        XCB_WINDOW_CLASS_INPUT_OUTPUT,
                        screen->root_visual,
                        mask, values);

        xcb_pixmap_t pixmap = xcb_generate_id(connection);
        xcb_create_pixmap(connection,
                        24,
                        pixmap,
                        window,
                        WIDTH, HEIGHT);

        uint8_t *img = malloc(WIDTH * HEIGHT * 4);

        uint8_t *limg = img;
        /*for (int y = 0; y < HEIGHT; y++)*/
                /*for (int x = 0; x < WIDTH; x++) {*/
                        /**(limg++) = 128;*/
                        /**(limg++) = 128;*/
                        /**(limg++) = 128;*/
                        /*limg++;*/
                /*}*/
        perlin(img, WIDTH, HEIGHT);

        xcb_image_t *image = xcb_image_create(WIDTH, HEIGHT,
                        XCB_IMAGE_FORMAT_Z_PIXMAP,
                        8, 24, 32,
                        0,
                        /*xcb_get_setup(connection)->image_byte_order,*/
                        XCB_IMAGE_ORDER_MSB_FIRST,
                        XCB_IMAGE_ORDER_LSB_FIRST,
                        img,
                        WIDTH * HEIGHT * 4,
                        img);

        xcb_gcontext_t gc = xcb_generate_id(connection);
        xcb_create_gc(connection,
                        gc,
                        pixmap,
                        0, NULL);

        xcb_image_put(connection, pixmap, gc, image, 0, 0, 0);

        xif_write(image, "test.xif");

        xcb_map_window(connection, window);
        xcb_flush(connection);

        xcb_generic_event_t *event;
        while ((event = xcb_wait_for_event(connection))) {
                switch (event->response_type & ~0x80) {
                case XCB_EXPOSE: ;
                        xcb_expose_event_t *expose = (xcb_expose_event_t *)event;
                        xcb_copy_area(connection,
                                        pixmap,
                                        window,
                                        gc,
                                        expose->x, expose->y,
                                        expose->x, expose->y,
                                        expose->width, expose->height);
                        xcb_flush(connection);
                        break;
                case XCB_BUTTON_PRESS:
                        goto end;
                        break;
                default:
                        break;
                }
                free(event);
        }
end:

        xcb_free_pixmap(connection, pixmap);
        xcb_disconnect(connection);

        xcb_image_destroy(image);

        return 0;
}

int8_t randrange(int8_t from, int8_t to)
{
        int base_random = rand();
        if (RAND_MAX == base_random) return randrange(from, to);
        int range = to - from,
            remainder = RAND_MAX % range,
           bucket = RAND_MAX / range;
        if (base_random < RAND_MAX - remainder) {
                return from + base_random/bucket;
        } else {
                return randrange(from, to);
        }
}

#define lerp(t, a, b) (a + t * (b - a))

void perlin(uint8_t * const img, uint16_t width, uint16_t height)
{
        uint8_t *limg = img;
        for (int y = 0; y < HEIGHT; y++)
                for (int x = 0; x < WIDTH; x++) {
                        *(limg++) = 128;
                        *(limg++) = 128;
                        *(limg++) = 128;
                        limg++;
                }

        int8_t *mipmap = malloc(sizeof(int8_t) * (2 * 2 + 4 * 4 + 8 * 8 + 16 * 16) * 4);

        int8_t *lmipmap = mipmap;
        for (int s = 2; s <= 16; s*=2)
                for (int x = 0; x < s * s; x++) {
                        *(lmipmap++) = randrange(-128 / s, 128 / s);
                        *(lmipmap++) = randrange(-128 / s, 128 / s);
                        *(lmipmap++) = randrange(-128 / s, 128 / s);
                        lmipmap++;
                        printf("S: %d X: %d Y: %d R: %d G: %d B: %d\n", s, x / s, x, *(lmipmap-4), *(lmipmap-3), *(lmipmap-2));
                };

        limg = img;
        lmipmap = mipmap;
        for (int y = 0; y < height; y++)
                for (int x = 0; x < width; x++)
                        for (int bit = 0; bit < 2; bit ++) {
                                for (int s = 2; s <= 16; s*=2) {
                                        size_t offset = 0;
                                        for (int i = s / 2; i >= 2; i/=2)
                                                offset += i * i;
                                        lmipmap = mipmap + offset;
                                        uint16_t xblock = width / (s - 1);
                                        uint16_t yblock = height / (s - 1);

                                        uint8_t xbpos = (float)x / (float)xblock;
                                        uint8_t ybpos = (float)y / (float)yblock;

                                        float xmul = (float)x / (float)width - (float)xbpos;
                                        float ymul = (float)y / (float)height - (float)ybpos;

                                        int8_t valtl, valtr, valbl, valbr;
                                        valtl = lmipmap[bit + 4 * (ybpos * s + xbpos)];
                                        valtr = lmipmap[bit + 4 * (ybpos * s + xbpos + 1)];
                                        valbl = lmipmap[bit + 4 * ((ybpos + 1) * s + xbpos)];
                                        valbr = lmipmap[bit + 4 * ((ybpos + 1) * s + xbpos + 1)];

                                        int8_t wlerpu = lerp(xmul, valtl, valtr);
                                        int8_t wlerpl = lerp(xmul, valbl, valbr);

                                        int8_t endval = lerp(ymul, wlerpl, wlerpu);

                                        limg[bit + 4 * (y * width + x)] = limg[bit + 4 * (y * width + x)] + endval;
                                }
                        }
        free(mipmap);
}
