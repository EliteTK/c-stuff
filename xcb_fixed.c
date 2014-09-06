/* XCB application drawing an updating bitmap in a window
*
* Inspired by the xcb black rectangle in a window example
*
* Copyright 2010 V. R. Sanders, released under the MIT licence
*/

/* compile with:
*   gcc -Wall -lxcb-icccm -lxcb -lxcb-image -o disp disp.c
*/

#include <string.h>

#include <xcb/xcb.h>
#include <xcb/xcb_image.h>
#include <xcb/xcb_atom.h>
#include <xcb/xcb_icccm.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

static xcb_format_t *
find_format (xcb_connection_t * c, uint8_t depth, uint8_t bpp)
{
 const xcb_setup_t *setup = xcb_get_setup(c);
 xcb_format_t *fmt = xcb_setup_pixmap_formats(setup);
 xcb_format_t *fmtend = fmt + xcb_setup_pixmap_formats_length(setup);
 for(; fmt != fmtend; ++fmt)
  if((fmt->depth == depth) && (fmt->bits_per_pixel == bpp)) {
   /* printf("fmt %p has pad %d depth %d, bpp %d\n",
      fmt,fmt->scanline_pad, depth,bpp); */
   return fmt;
  }
 return 0;
}

void
fillimage(unsigned char *p, int width, int height)
{
 int i, j;
 for(j=0; j < height; j++)
 {
  for(i=0; i < width; i++)
  {
   if((i < 256)&&(j < 256))
   {
    *p++=rand()%256; // blue
    *p++=rand()%256; // green
    *p++=rand()%256; // red
   } else {
    *p++=i%256; // blue
    *p++=j%256; // green
    if(i < 256)
     *p++=i%256; // red
    else if(j < 256)
     *p++=j%256; // red
    else
     *p++=(256-j)%256; // red
   }
   p++; /* unused byte */
  }
 }
}

xcb_image_t *
CreateTrueColorImage(xcb_connection_t *c,
       int width,
       int height)
{
 const xcb_setup_t *setup = xcb_get_setup(c);
 unsigned char *image32=(unsigned char *)malloc(width*height*4);
 xcb_format_t *fmt = find_format(c, 24, 32);
 if (fmt == NULL)
  return NULL;

 fillimage(image32, width, height);

 return xcb_image_create(width,
    height,
    XCB_IMAGE_FORMAT_Z_PIXMAP,
    fmt->scanline_pad,
    fmt->depth,
    fmt->bits_per_pixel,
    0,
    setup->image_byte_order,
    XCB_IMAGE_ORDER_LSB_FIRST,
    image32,
    width*height*4,
    image32);
}

int
main (int argc, char **argv)
{
 xcb_connection_t *c;
 xcb_screen_t *s;
 xcb_window_t w;
 xcb_pixmap_t pmap;
 xcb_gcontext_t gc;
 xcb_generic_event_t *e;
 uint32_t mask;
 uint32_t values[2];
 int done=0;
 xcb_image_t *image;
 uint8_t *image32;
 xcb_expose_event_t *ee;
 char *title="Hello World!";
 xcb_size_hints_t *hints;

 /* open connection with the server */
 c = xcb_connect (NULL, NULL);

 if (!c) {
  printf ("Cannot open display\n");
  exit (1);
 }

 s = xcb_setup_roots_iterator (xcb_get_setup (c)).data;

 /* printf("root depth %d\n",s->root_depth); */

 /* create image */
 image = CreateTrueColorImage(c, 640, 480);
 if (image == NULL) {
  printf ("Cannot create iamge\n");
  xcb_disconnect(c);
  return 1;
 }
 image32 = image->data;

 /* create window */
 mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
 values[0] = s->white_pixel;
 values[1] = XCB_EVENT_MASK_EXPOSURE |
  XCB_EVENT_MASK_KEY_PRESS |
  XCB_EVENT_MASK_BUTTON_PRESS;

 w = xcb_generate_id (c);
 xcb_create_window (c, XCB_COPY_FROM_PARENT, w, s->root,
      10, 10, image->width, image->height, 1,
      XCB_WINDOW_CLASS_INPUT_OUTPUT,
      s->root_visual,
      mask, values);

 /*[> set size hits on window <]*/
 /*hints = xcb_alloc_size_hints();*/
 /*xcb_size_hints_set_max_size(hints, image->width,image->height);*/
 /*xcb_size_hints_set_min_size(hints, image->width,image->height);*/
 /*xcb_set_wm_size_hints(c, w, WM_NORMAL_HINTS, hints);*/

 /* create backing pixmap */
 pmap = xcb_generate_id(c);
 xcb_create_pixmap(c, 24, pmap, w, image->width, image->height);

 /* create pixmap plot gc */
 mask = XCB_GC_FOREGROUND | XCB_GC_BACKGROUND;
 values[0] = s->black_pixel;
 values[1] = 0xffffff;

 gc = xcb_generate_id (c);
 xcb_create_gc (c, gc, pmap, mask, values);

 /* put the image into the pixmap */
 xcb_image_put(c, pmap, gc, image, 0, 0, 0);

 /* show the window */
 xcb_map_window (c, w);
 xcb_flush (c);

 /* event loop */
 while (!done && (e = xcb_wait_for_event (c))) {
  switch (e->response_type) {
  case XCB_EXPOSE:
   ee=(xcb_expose_event_t *)e;
   /* printf ("expose %d,%d - %d,%d\n",
      ee->x,ee->y,ee->width,ee->height); */
   xcb_copy_area(c, pmap, w, gc,
          ee->x,
          ee->y,
          ee->x,
          ee->y,
          ee->width,
          ee->height);
   xcb_flush (c);
   image32+=16;
   break;

  /*case XCB_KEY_PRESS:*/
   /*[> exit on keypress <]*/
   /*done = 1;*/
   /*break;*/

  case XCB_BUTTON_PRESS:
   fillimage(image->data, image->width, image->height);
   memset(image->data, 0, image32 - image->data);
   xcb_image_put(c, pmap, gc, image, 0, 0, 0);
   xcb_copy_area(c, pmap, w, gc, 0,0,0,0,image->width,image->height);
   xcb_flush (c);
   break;
  }
  free (e);
 }

 /* free pixmap */
 xcb_free_pixmap(c, pmap);

 /* close connection to server */
 xcb_disconnect (c);

 return 0;
}
