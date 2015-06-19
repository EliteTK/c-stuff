/*
 * This is an attempt at implementing md5 in c, so far it doesn't work :(.
 * I took the values from wikipedia (https://en.wikipedia.org/wiki/MD5).
 *
 * Copyright (C) 2015  Tomasz Kramkowski <tk@the-tk.com>
 *
 * This program is free software. It is licensed under version 3 of the
 * GNU General Public License.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see [http://www.gnu.org/licenses/].
 */
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void shuffle_bytes(char *buf, size_t length)
{
	length = length - length % 4;

	for (size_t i = 0; i < length / 4; i++) {
		char *bufc = buf + i * 4;
		char chars[4] = {
			bufc[3],
			bufc[2],
			bufc[1],
			bufc[0]
		};
		strncpy(bufc, chars, 4);
	}
}

int main(void)
{
	uint32_t *s, *K, a0, b0, c0, d0, length;
	char input[64] = "";

	length = strlen(input);

	s = (uint32_t []){
		7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
		5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
		4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
		6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21};

	K = (uint32_t []){
		0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
		0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
		0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
		0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
		0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
		0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
		0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
		0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
		0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
		0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
		0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
		0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
		0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
		0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
		0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
		0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

	a0 = 0x67452301;
	b0 = 0xefcdab89;
	c0 = 0x98badcfe;
	d0 = 0x10325476;

	input[length] = 128;

	for (uint8_t i = length + 1; i < 56; i++)
		input[i] = 0;

	/*((uint64_t *)input)[7] = (uint64_t)length;*/
	input[63] = 0;

	for (uint8_t i = 0; i < 64; i++)
		putchar(input[i]);

	/*shuffle_bytes(input, 64);*/
	uint32_t *M = (uint32_t *)input;

	uint32_t A = a0, B = b0, C = c0, D = d0;

	for (uint32_t i = 0; i < 64; i ++) {
		uint16_t F, g, dTemp;

		switch (i) {
		case 0 ... 15:
			F = (B & C) | ((~B) & D);
			g = i;
			break;
		case 16 ... 31:
			F = (D & B) | ((~D) & C);
			g = (5 * i + 1) % 16;
			break;
		case 32 ... 47:
			F = B ^ C ^ D;
			g = (3 * i + 5) % 16;
			break;
		case 48 ... 63:
			F = C ^ (B | (~D));
			g = (7 * i) % 16;
			break;
		}

		dTemp = D;

		D = C;
		C = B;
		B += ((A + F + K[i] + M[g]) << s[i]) | ((A + F + K[i] + M[g]) >> (32-s[i]));
		A = dTemp;
	}

	a0 += A;
	b0 += B;
	c0 += C;
	d0 += D;

	/*shuffle_bytes((char *)&a0, 4);*/
	/*shuffle_bytes((char *)&b0, 4);*/
	/*shuffle_bytes((char *)&c0, 4);*/
	/*shuffle_bytes((char *)&d0, 4);*/

	printf("%.8x%.8x%.8x%.8x\n", a0, b0, c0, d0);

	return EXIT_SUCCESS;
}
