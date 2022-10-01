#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "mona_lisa.h"
#define WIDTH 320
#define HEIGHT 240

uint16_t min(uint16_t a, uint16_t b)
{
	return (a > b) ? b : a;
}

int main()
{
	uint16_t shifts[3] = { 11, 5, 0 };

	uint16_t rgbErrors[3] = { 0, 0, 0 };

	uint16_t mymask[3] = { 0xF800, 0x07E0, 0x001F
	};

	uint16_t output[HEIGHT][WIDTH];
	uint16_t current_pixel;
	uint16_t currentRGB[3] = { 0, 0, 0 };

	uint16_t neighbourRGB[3] = { 0, 0, 0 };

	uint16_t trial_error = 0;
	uint8_t final_dec = 0x00;
	uint16_t real_errorRGB[3];
	int16_t neighbors[3][4] = { 0, 1, 1, 1,
		1, -1, 0, 1,
		7, 1, 5, 3
	};

	int total, current;
	int x, y, z, k;

	for (x = 0; x < HEIGHT; x++)
	{
		for (y = 0; y < WIDTH; y++)
		{
			if ((x == HEIGHT - 1) || (y == WIDTH - 1) || (y == 0))
			{
				fputc(final_dec, f);
				fputc(final_dec, f);
				fputc(final_dec, f);
				continue;
			}

			current_pixel = image_map[x][y];
			trial_error = 0;
			for (z = 0; z < sizeof(shifts) / sizeof(uint16_t); z++)
			{
				currentRGB[z] = ((image_map[x][y] &mymask[z]) >> shifts[z]);
			}

			for (z = 0; z < sizeof(shifts) / sizeof(uint16_t); z++)
			{
				switch (z)
				{
					case 1:
						trial_error += currentRGB[z] / 2;
						break;
					default:
						trial_error += currentRGB[z];
				}
			}

			final_dec = trial_error > 51 ? 0xFF : 0x00;
			output[x][y] = (final_dec << 8) | final_dec;
			for (z = 0; z < sizeof(shifts) / sizeof(uint16_t); z++)
			{
				real_errorRGB[z] = currentRGB[z] - ((final_dec != 0) ? 255 : 0);
			}

			total = 16;
			for (z = 0; z < sizeof(neighbors[0]) / sizeof(neighbors[0][0]); z++)
			{
				current = rand() % total;
				if (z == sizeof(neighbors[0]) / sizeof(neighbors[0][0]) - 1)
				{
					current = total;
				}
				else
				{
					total -= current;
				}

				/*printf("%d\n",current); */
				for (k = 0; k < sizeof(shifts) / sizeof(uint16_t); k++)
				{
					neighbourRGB[k] = ((image_map[x + neighbors[0][z]][y + neighbors[1][z]] &mymask[k]) >> shifts[k]);
					neighbourRGB[k] += current *real_errorRGB[k] / 64;
				}

				image_map[x + neighbors[0][z]][y + neighbors[1][z]] = ((neighbourRGB[0] << shifts[0]) &mymask[0]) | ((neighbourRGB[1] << shifts[1]) &mymask[1]) | ((neighbourRGB[2] << shifts[2]) &mymask[2]);
			}
		}
	}
}
