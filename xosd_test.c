/*
 * Copyright (C) 2014  Tomasz Kramkowski <tk@the-tk.com>
 *
 * This program is free software. It is licensed under version 3 of the
 * GNU General Public License.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see [http://www.gnu.org/licenses/].
 */
#include <stdio.h>
#include <stdlib.h>
#include <xosd.h>

int main(void)
{
	xosd *osd = xosd_create(1);

	xosd_set_font(osd, "fixed");
	xosd_set_colour(osd, "LawnGreen");
	xosd_set_timeout(osd, 3);
	xosd_set_shadow_offset(osd, 1);

	xosd_display(osd, 0, XOSD_string, "Example XOSD output");

	xosd_wait_until_no_display(osd);

	xosd_destroy(osd);

	return EXIT_SUCCESS;
}

