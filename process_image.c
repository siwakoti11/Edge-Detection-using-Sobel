#include <stdio.h>
#include <math.h>
#include <X11/Xlib.h>
#include <stdlib.h>
#include <float.h>

#define DIM 512
#define m 3

/******************************************************************/
/* This structure contains the coordinates of a box drawn with    */
/* the left mouse button on the image window.                     */
/* roi.x , roi.y  - left upper corner's coordinates               */
/* roi.width , roi.height - width and height of the box           */
/******************************************************************/
extern XRectangle roi;


/******************************************************************/
/* Main processing routine. This is called upon pressing the      */
/* Process button of the interface.                               */
/* image  - the original greyscale image                          */
/* size   - the actual size of the image                          */
/* proc_image - the image representation resulting from the       */
/*              processing. This will be displayed upon return    */
/*              from this function.                               */
/******************************************************************/
void process_image(image, size, proc_img)
unsigned char image[DIM][DIM];
int size[2];
unsigned char proc_img[DIM][DIM];
{
	int Gv[m][m]={{-1,0,1},{-2,0,2},{-1,0,1}};
	int Gh[m][m]={{-1,-2,-1},{0,0,0},{1,2,1}};
	int i,j,k,l;
	int sum,sumV,sumH;
	int template = 1; /* 0 = Vertical, 1 = Horizontal, 2 = Combined */

	for (i=0;i<=size[1]-1;i++)
	{
		for (j=0;j<=size[0]-1;j++)
		{
			sum=0;
			for (k=-1;k<=1;k++)
			{
				for (l=-1;l<=1;l++)
				{
					if(template==0){
						sum+=Gv[k+1][l+1]*image[i+k][j+l];
					}
					else if(template==1){			
						sum+=Gh[k+1][l+1]*image[i+k][j+l];
					}
					else if(template==2){
						sumV=Gv[k+1][l+1]*image[i+k][j+l];
						sumH=Gh[k+1][l+1]*image[i+k][j+l];
						sum+=sumV+sumH;
					}			
				}
			}
			sum=abs(sum);
			if (sum > 255) sum=255;
			if (sum < 0) sum=0;
			proc_img[i][j]=(char)sum;
		}
	}
}


