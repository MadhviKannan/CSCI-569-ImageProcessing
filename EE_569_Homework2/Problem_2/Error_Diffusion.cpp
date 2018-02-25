
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include<vector>
#include<iostream>
#include<math.h>
#include<algorithm>
unsigned char man[512][512];
double man_new[516][516];
unsigned char man_error[516][516];
unsigned char pepper[512][512];
unsigned char pepper_extend[514][514];
unsigned char pepper_extend1[516][516];
unsigned char man_new1[512][512];
unsigned char man_new2[512][512];
unsigned char man_new_a[512][512];
using namespace std;
int main()
{
    int i,j;
	int BytesPerPixel=3;
    FILE *file,*file2,*file1,*file3,*file4,*file5,*file6;
	if (!(file=fopen("man.raw","rb"))) {
		cout << "Cannot open file: " << "man.raw" <<endl;
		exit(1);
	}
	fread(pepper, sizeof(unsigned char), 512*512, file);
	fclose(file);
	int ext=3;//variable indicating window size
	//--------------------Extending the boundary for 3x3 or 5x5 window------------------//
int extend=(ext-1)/2;

    for(int m=0;m<512;m++)
    {
        for(int n=0;n<512;n++)
        {

                pepper_extend[m+extend][n+extend]=pepper[m][n];

        }
    }

    for(int i=extend;i>0;i--)
    {
         for(int j=extend;j<(512+extend-1);j++)
         {


                pepper_extend[i-1][j]=pepper_extend[i][j];

    }
    }
    for(int i_bottom=(512+extend-1);i_bottom<(512+(2*extend)-1);i_bottom++)
    {
    for(int j_bottom=extend;j_bottom<(512+extend-1);j_bottom++)
    {


                pepper_extend[i_bottom+1][j_bottom]=pepper_extend[i_bottom][j_bottom];
                //pepper_extend[j][514][bytes2]=pepper_extend[j][513][bytes2];


    }
    }

    for(int row_left=0;row_left<(512+(2*extend)-1);row_left++)
    {
        for(int col_left=extend;col_left>0;col_left--)
        {


                pepper_extend[row_left][col_left-1]=pepper_extend[row_left][col_left];
                //pepper_extend[515][k][bytes3]=pepper_extend[515][k][bytes3];

        }
    }
    for(int col_right=0;col_right<(512+(2*extend)-1);col_right++)
    {

    for(int row_right=(512+extend-1);row_right<(512+(2*extend)-1);row_right++)
    {
                pepper_extend[col_right][row_right+1]=pepper_extend[col_right][row_right];
                //pepper_extend[l][515][bytes4]=pepper_extend[l][514][bytes4];
    }
    }
    int ext1=5;//variable indicating window size
	//--------------------Extending the boundary for 3x3 or 5x5 window------------------//
int extend1=(ext1-1)/2;

    for(int m=0;m<512;m++)
    {
        for(int n=0;n<512;n++)
        {

                pepper_extend1[m+extend1][n+extend1]=pepper[m][n];

        }
    }

    for(int i=extend1;i>0;i--)
    {
         for(int j=extend1;j<(512+extend1-1);j++)
         {


                pepper_extend1[i-1][j]=pepper_extend1[i][j];

    }
    }
    for(int i_bottom=(512+extend1-1);i_bottom<(512+(2*extend1)-1);i_bottom++)
    {
    for(int j_bottom=extend1;j_bottom<(512+extend1-1);j_bottom++)
    {


                pepper_extend1[i_bottom+1][j_bottom]=pepper_extend1[i_bottom][j_bottom];
                //pepper_extend[j][514][bytes2]=pepper_extend[j][513][bytes2];


    }
    }

    for(int row_left=0;row_left<(512+(2*extend1)-1);row_left++)
    {
        for(int col_left=extend1;col_left>0;col_left--)
        {


                pepper_extend1[row_left][col_left-1]=pepper_extend1[row_left][col_left];
                //pepper_extend[515][k][bytes3]=pepper_extend[515][k][bytes3];

        }
    }
    for(int col_right=0;col_right<(512+(2*extend1)-1);col_right++)
    {

    for(int row_right=(512+extend1-1);row_right<(512+(2*extend1)-1);row_right++)
    {
                pepper_extend1[col_right][row_right+1]=pepper_extend1[col_right][row_right];
                //pepper_extend[l][515][bytes4]=pepper_extend[l][514][bytes4];
    }
    }
    double error_mat[3][3]={0,0,0,0,0,0.4375,0.1875,0.3125,0.0625}; //Normalised floyd Steinberg matrix
    int old_pixel,new_pixel;
    double error;
    //-----------------Floyd Steinberg-----------------//
   for(int i=2;i<513;i++)
    {
    for(int j=2;j<513;j++)
    {
        old_pixel=(int)pepper_extend[i][j]; //assigning old pixel to the central pixel
        if(old_pixel>127) //checking condition
        {
            pepper_extend[i][j]=255;
            error=old_pixel-255; //error quantization
        }
        else
        {
            pepper_extend[i][j]=0;
            error=old_pixel;
        }
        //----diffusing the error to other locations to the right and bottom of the central pixel using certain normalisation constants
        pepper_extend[i][j+1]=((double)pepper_extend[i+1][j] +error*0.4375);
        pepper_extend[i+1][j-1]=((double)pepper_extend[i-1][j+1] +error*0.1875);
        pepper_extend[i+1][j]=((double)pepper_extend[i][j+1] +error*0.3125);
        pepper_extend[i+1][j+1]=((double)pepper_extend[i+1][j+1] +error*0.0625);

    }
    }
//-----------------------JJN----------------//

    for(int i=2;i<514;i++)
    {
    for(int j=2;j<514;j++)
    {
        old_pixel=(int)pepper_extend1[i][j];
        if(old_pixel>127)
        {
            pepper_extend1[i][j]=255;
            error=old_pixel-255;
        }
        else
        {
            pepper_extend1[i][j]=0;
            error=old_pixel;
        }
        pepper_extend1[i+1][j]=((double)pepper_extend1[i+1][j] +error*(double)(7.0/48.0));
        pepper_extend1[i+2][j]=((double)pepper_extend1[i+2][j] +error*(double)(5.0/48.0));
        pepper_extend1[i][j+1]=((double)pepper_extend1[i][j+1] +error*(double)(7.0/48.0));
        pepper_extend1[i][j+2]=((double)pepper_extend1[i][j+2] +error*(double)(5.0/48.0));
        pepper_extend1[i+1][j+1]=((double)pepper_extend1[i+1][j+1] +error*(double)(5.0/48.0));
         pepper_extend1[i+1][j+2]=((double)pepper_extend1[i+1][j+2] +error*(double)(3.0/48.0));
        pepper_extend1[i+2][j+1]=((double)pepper_extend1[i+2][j+1] +error*(double)(3.0/48.0));
        pepper_extend1[i+2][j+2]=((double)pepper_extend1[i+2][j+2] +error*(double)(1.0/48.0));
        pepper_extend1[i+1][j-1]=((double)pepper_extend1[i+1][j-1] +error*(double)(5.0/48.0));
        pepper_extend1[i+2][j-1]=((double)pepper_extend1[i+2][j-1] +error*(double)(3.0/48.0));
        pepper_extend1[i+1][j-2]=((double)pepper_extend1[i+1][j-2] +error*(double)(3.0/48.0));
        pepper_extend1[i+2][j-2]=((double)pepper_extend1[i+2][j-2] +error*(double)(1.0/48.0));

    }
    }
 /*   //--------------Stucki------------//

    for(int i=2;i<514;i++)
    {
    for(int j=2;j<514;j++)
    {
        old_pixel=(int)pepper_extend[i][j];
        if(old_pixel>127)
        {
            pepper_extend[i][j]=255;
            error=old_pixel-255;
        }
        else
        {
            pepper_extend[i][j]=0;
            error=old_pixel;
        }
        pepper_extend[i+1][j]=((double)pepper_extend[i+1][j] +error*(double)(8.0/42.0));
        pepper_extend[i+2][j]=((double)pepper_extend[i+2][j] +error*(double)(4.0/42.0));
        pepper_extend[i][j+1]=((double)pepper_extend[i][j+1] +error*(double)(8.0/42.0));
        pepper_extend[i][j+2]=((double)pepper_extend[i][j+2] +error*(double)(4.0/42.0));
        pepper_extend[i+1][j+1]=((double)pepper_extend[i+1][j+1] +error*(double)(4.0/42.0));
         pepper_extend[i+1][j+2]=((double)pepper_extend[i+1][j+2] +error*(double)(2.0/42.0));
        pepper_extend[i+2][j+1]=((double)pepper_extend[i+2][j+1] +error*(double)(2.0/42.0));
        pepper_extend[i+2][j+2]=((double)pepper_extend[i+2][j+2] +error*(double)(1.0/42.0));
        pepper_extend[i+1][j-1]=((double)pepper_extend[i+1][j-1] +error*(double)(4.0/42.0));
        pepper_extend[i+2][j-1]=((double)pepper_extend[i+2][j-1] +error*(double)(2.0/42.0));
        pepper_extend[i+1][j-2]=((double)pepper_extend[i+1][j-2] +error*(double)(2.0/42.0));
        pepper_extend[i+2][j-2]=((double)pepper_extend[i+2][j-2] +error*(double)(1.0/42.0));

    }
    }*/
   // cout<<(man_new[120][100])<<endl;
     if (!(file2=fopen("Man_Floyd_Steinberg.raw","wb"))) {
		cout << "Cannot open file: " << "man_Stucki.raw" << endl;
		exit(1);
	}
	fwrite(pepper_extend, sizeof(unsigned char),   514*514, file2);
	printf("File written\n");
	fclose(file2);
	if (!(file2=fopen("Man_JJN.raw","wb"))) {
		cout << "Cannot open file: " << "man_Stucki.raw" << endl;
		exit(1);
	}
	fwrite(pepper_extend1, sizeof(unsigned char),   516*516, file2);
	printf("File written\n");
	fclose(file2);
	 if (!(file2=fopen("man_new1.raw","wb"))) {
		cout << "Cannot open file: " << "man_new1.raw" << endl;
		exit(1);
	}
	fwrite(man_new, sizeof(unsigned char),   514*514, file2);
	printf("File written\n");
	fclose(file2);
    return 0;
}
