#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#include<math.h>
#include<algorithm>
unsigned char cup1[500][500][3];
unsigned char cup2[500][500][3];
unsigned char cup_inter[500][500][3];
unsigned char cup_output[500][500][3];
unsigned char cup_output1[500][500][3];
using namespace std;
int main()
{
    double col_rat[250]={0.0};
    int count_arr[250]={0};
    FILE *file1, *file2, *file3,*file4,*file5,*file6,*file;
    int BytesPerPixel=3;
    int i,j;
    //---------Read Image------//
    if (!(file1=fopen("cup2.raw","rb"))) {
		cout << "Cannot open file: " << "cup1.raw" <<endl;
		exit(1);
	}
	fread(cup1,sizeof(unsigned char), 500*500*BytesPerPixel, file1);
    fclose(file1);

    //--------Start Warping for Cup 1----//
    int pix_per_row=2; //Set pixel per row to be 2 initially. This depicts the number of pixels in each quarter of the upper half of the image

//-----for the upper half of the triangle---//
    for(int i=0;i<250;i++) //Run loop for the upper half of the cup image
    {
        j=250-(pix_per_row/2)-1; //Start columns from bottom, and keep warping by decrementing 2 pixels on either sides of the second last row(249)
        double rat=500.0/(double)pix_per_row; //find scaling ratio of each row
        int inter=pix_per_row; //keep a count of the pixels per row
        inter=0;
        while(inter<=pix_per_row) //while count is less than equal to number of pixels
        {
            //perform interpolation on the row
            double x=(double)i;
            double y=(double)inter*rat;
            int row_pix=floor(x);
            int col_pix=floor(y);
            float del_x=x-(double)row_pix;
            float del_y=y-(double)col_pix;
            float weight1=(1-del_x)*(1-del_y); //compute the 4 weights
                float weight2=del_y*(1-del_x);
                float weight3=del_x*(1-del_y);
                float weight4=del_x*del_y;
                for(int k=0;k<3;k++)
                {
                cup_output[i][j][k]= weight1*cup1[row_pix][col_pix][k]+weight2*cup1[row_pix][col_pix+1][k]+weight3*cup1[row_pix+1][col_pix][k]+weight4*cup1[row_pix+1][col_pix+1][k];

                }
                j++;
                inter++; //increment count
        }
        pix_per_row=pix_per_row+2; //increment pixels per row to be copied by a factor of 2
    }
    //-----for the lower half of the triangle----//
     for(int i=250;i<500;i++)
    {
        j=250-(pix_per_row/2)-1;
        double rat=500.0/(double)pix_per_row;
        int inter=pix_per_row;
        inter=0;
        while(inter<=pix_per_row)
        {
            double x=(double)i;
            double y=(double)inter*rat;
            int row_pix=floor(x);
            int col_pix=floor(y);
            float del_x=x-(double)row_pix;
            float del_y=y-(double)col_pix;
            float weight1=(1-del_x)*(1-del_y); //compute the 4 weights
                float weight2=del_y*(1-del_x);
                float weight3=del_x*(1-del_y);
                float weight4=del_x*del_y;
                for(int k=0;k<3;k++)
                {
                cup_output[i][j][k]= weight1*cup1[row_pix][col_pix][k]+weight2*cup1[row_pix][col_pix+1][k]+weight3*cup1[row_pix+1][col_pix][k]+weight4*cup1[row_pix+1][col_pix+1][k];

                }
                j++;
                inter++;
        }
        pix_per_row=pix_per_row-2; //Decrement by a factor of two
    }



    if (!(file=fopen("cup_linear_warp.raw","wb"))) {
		cout << "Cannot open file: " << "cup_linear_warp.raw" << endl;
		exit(1);
	}

	fwrite(cup_output, sizeof(unsigned char),   500*500*BytesPerPixel, file);
	printf("File written\n");
	fclose(file);
	if (!(file=fopen("cup2_linear_warp2.raw","wb"))) {
		cout << "Cannot open file: " << "cup2_linear_warp2.raw" << endl;
		exit(1);
	}

	fwrite(cup_output, sizeof(unsigned char),   500*500*BytesPerPixel, file);
	printf("File written\n");
	fclose(file);
	return 0;
}
