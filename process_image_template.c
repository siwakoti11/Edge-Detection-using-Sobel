
#include <stdio.h>
#include <math.h>
#include <X11/Xlib.h>

#define DIM 512
#define MAX_PIXEL 255

extern XRectangle roi;

void process_image(image, size, proc_img)
unsigned char image[DIM][DIM];
int size[2];

unsigned char proc_img[DIM][DIM];
{

	int i,j,k,l,isum,tsum,temp;

	int check = 1;

	int wid = size[0] - (roi.width - 1);

	int hig = size[1] - (roi.height - 1);

	float win, tem, win_std, tem_std, a, num, fnum, den, max, min;

	unsigned char temp_image[roi.width][roi.height];

	for (i = roi.x; i < (roi.width + roi.x); i++) {
		for (j = roi.y; j < (roi.height + roi.y); j++) {
			temp = image[i][j];
			tsum = tsum + temp;
		}
	}
	
	for (i = 0; i < wid; i++) {
		for (j = 0; j < hig; j++) {

			for (k = i; k < roi.width + i; k++) {
				for (l = j; l < roi.height + j; l++) {
					isum += image[k][l];
				}
			}
			fnum=isum;	
			isum=0;

			for (k = i; k < roi.width + i; k++) {
				for (l = j; l < roi.height + j; l++) {

					win_std += powf( (image[k][l] - fnum/(roi.width * roi.height)), 2);
					tem_std += powf( (temp_image[k][l] - (tsum / (roi.width * roi.height))), 2);
					num += fabs(((image[k][l] - fnum/(roi.width * roi.height)) * (temp_image[k][l] - (tsum / (roi.width * roi.height)))));
				}
			}

			if (win_std == 0 || tem_std == 0) a=0;
			else {
				a = num / sqrt(win_std * tem_std);
				if (check == 1) {
					max = min = a;
					check = 0;
				}
				if (a > max) max=a;
				if (a < min) min=a;
			}
			
			for (k = i; k < roi.width + i; k++) {
				for (l = j; l < roi.height + j; l++) {
					proc_img[k][l] = ( (a - min) / (max - min) ) * 255;
				}
			}

			win_std = tem_std = num = a = 0;
		}
		check = 1;
	}
}

