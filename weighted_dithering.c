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
	FILE *f = fopen("out.ppm", "wb");
	uint16_t shifts[3] = {11,5,0};
	uint16_t rgbErrors[3] = {0,0,0};
	uint16_t mymask[3] = {0xF800,0x07E0,0x001F};
	uint16_t out[HEIGHT][WIDTH];
	uint16_t current_pixel;
	uint16_t currentRGB[3] = {0,0,0};
	uint16_t neighbourRGB[3] = {0,0,0};
	uint16_t trial_error=0;
	uint8_t final_dec = 0x00;
	uint16_t real_errorRGB[3];
	int16_t neighbors[3][4] = {0,1,1,1,
								1,-1,0,1,
								7,1,5,3};
	int total, current;
	int x,y,z,k;
	fprintf(f, "P6\n%i %i 255\n", WIDTH, HEIGHT);
	for (x=0; x<HEIGHT; x++) 
	{
    	for (y=0; y<WIDTH; y++) 
		{
			image_map[x][y] = (rand() % 0xFFFF - (0xFFFF-image_map[x][y])) < 0 ? 0x0000 : 0xFFFF;
			
			fputc(image_map[x][y]>>8, f);   
        	fputc(image_map[x][y]>>8, f); 
        	fputc(image_map[x][y]>>8, f);
		
			/*printf("\n");*/
    	}
    }
	fclose(f);

	
}


