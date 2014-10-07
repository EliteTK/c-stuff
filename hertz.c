/*
 * Some sound testing.
 *
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
#include <stdbool.h>
#include <math.h>

static long int sfreq;

void playtone(long int, int, long int, float);
void playtone_pwm(long int, long int, int, long int);
void sinetone(float, int, float);

int main(int argc, char **argv)
{
        if (argc != 2) {
                fprintf(stderr, "Usage: %s <frequency>\n", argv[0]);
                exit(1);
        }

        sfreq = strtol(argv[1], NULL, 10);

        /*for (int i = 1; i < 3000; i++)*/
                /*sinetone(i, 127, 5);*/

        for (int i = 1; i < 3000; i++)
                sinetone(i, 127, 1.0/i * 1000.0);

        /*for (int i = 0; i < 1000; i++) {*/
                /*long int pulse_width = 441;*/

                /*float duty_cycle = (sinf(i / 5.0 * M_PI) + 1.0) / 2.0;*/

                /*for (int ii = 0; ii < ceilf(duty_cycle * pulse_width); ii++)*/
                        /*putchar(0);*/
                /*for (int ii = 0; ii < floorf((1.0 - duty_cycle) * pulse_width); ii++)*/
                        /*putchar(255);*/
        /*}*/

        /*playtone_pwm(160, 80, 127, 10000);*/
        /*for (float i = 0; i < 1; i+=0.01)*/
                /*playtone(100, 127, 10, i);*/
        return 0;
}

void playtone(long int freq, int ampl, long int time, float duty_cycle)
{
        if (ampl > 127)
                ampl = 127;
        long int pulse_width = sfreq / freq;

        long int total_waves = time * freq / 1000;

        for (long int wi = 0; wi < total_waves; wi++) {
                int i;
                for (i = 0; i < (int)((float)pulse_width * duty_cycle); i++)
                        putchar(128-ampl);
                for (i = 0; i < (int)((float)pulse_width * (1.0 - duty_cycle)); i++)
                        putchar(255+ampl);
        }
}

void playtone_pwm(long int freq, long int freq_pwm, int ampl, long int time)
{
        if (ampl > 127)
                ampl = 127;

        long int pulse_width = sfreq / freq;

        long int total_waves = time * freq / 1000;

        for (long int wi = 0; wi < total_waves; wi++) {
                int i;
                float pulse_proportion = (sinf((float)wi / (float)total_waves * time / freq_pwm * 2 * M_PI) + 1) / 2;
                for (i = 0; i < (int)((float)pulse_width * pulse_proportion); i++)
                        putchar(128-ampl);
                for (i = 0; i < (int)((float)pulse_width * (1.0 - pulse_proportion)); i++)
                        putchar(255+ampl);
        }
}

void sinetone(float freq, int ampl, float time)
{
        if (ampl > 127) ampl = 127;

        float wave_length = sfreq / freq;

        for (long int wi = 0; wi < time * sfreq / 1000; wi++)
                putchar((char)((sinf((float)wi / wave_length * M_PI_2 * 4) + 1) * ampl));
}
