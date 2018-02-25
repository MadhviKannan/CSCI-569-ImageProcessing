# EE569 :Homework Assignment #1
# Date  : February 5, 2017
# Name  : Madhvi Kannan
# USC ID: 2159965290
# email : mkannan@usc.edu
#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#include<math.h>
#include<algorithm>
unsigned char pepper[512][512][3];
unsigned char pepper_extend[532][532][3];
unsigned char pepper_denoised[512][512][3];
unsigned char pepper_free[512][512][3];
unsigned char sailboat[512][512][3];
unsigned char sailboat_extend[516][516][3];
unsigned char sailboat_denoised[512][512][3];
 double vec[19*19]={};
 double weight[19*19]={};
 double image[18*18*18]={};
//unsigned median[3][3];
using namespace std;
int main()
{
    FILE *file1, *file2, *file3,*file4,*file5,*file6;
    int BytesPerPixel=3;
    int i,j;
    if (!(file1=fopen("sailboat_noisy.raw","rb"))) {
		cout << "Cannot open file: " << "sailboat_noisy.raw" <<endl;
		exit(1);
	}
	fread(pepper,sizeof(unsigned char), 512*512*BytesPerPixel, file1);
    fclose(file1);
    if (!(file1=fopen("sailboat.raw","rb"))) {
		cout << "Cannot open file: " << "sailboat.raw" <<endl;
		exit(1);
	}
	fread(pepper_free,sizeof(unsigned char), 512*512*BytesPerPixel, file1);
    fclose(file1);
    //--------------------  BOUNDARY EXTENSION ----------------------//
int ext=21; //Search window size
int extend=(ext-1)/2; //Number of additional rows and columns to add to the original image

    for(int m=0;m<512;m++)
    {
        for(int n=0;n<512;n++)
        {
            for(int bytes=0;bytes<3;bytes++)
            {
                pepper_extend[m+extend][n+extend][bytes]=pepper[m][n][bytes];

            }
        }
    }

    for(int i=extend;i>0;i--)
    {
         for(int j=extend;j<(512+extend-1);j++)
         {

        for(int bytes1=0;bytes1<3;bytes1++)
            {
                pepper_extend[i-1][j][bytes1]=pepper_extend[i][j][bytes1];

            }

    }
    }
    for(int i_bottom=(512+extend-1);i_bottom<(512+(2*extend)-1);i_bottom++)
    {
    for(int j_bottom=extend;j_bottom<(512+extend-1);j_bottom++)
    {
        for(int bytes2=0;bytes2<3;bytes2++)
            {
                pepper_extend[i_bottom+1][j_bottom][bytes2]=pepper_extend[i_bottom][j_bottom][bytes2];
                //pepper_extend[j][514][bytes2]=pepper_extend[j][513][bytes2];
            }

    }
    }

    for(int row_left=0;row_left<(512+(2*extend)-1);row_left++)
    {
        for(int col_left=extend;col_left>0;col_left--)
        {

        for(int bytes3=0;bytes3<3;bytes3++)
            {
                pepper_extend[row_left][col_left-1][bytes3]=pepper_extend[row_left][col_left][bytes3];
                //pepper_extend[515][k][bytes3]=pepper_extend[515][k][bytes3];
            }
        }
    }
    for(int col_right=0;col_right<(512+(2*extend)-1);col_right++)
    {

    for(int row_right=(512+extend-1);row_right<(512+(2*extend)-1);row_right++)
    {

        for(int bytes4=0;bytes4<3;bytes4++)
            {
                pepper_extend[col_right][row_right+1][bytes4]=pepper_extend[col_right][row_right][bytes4];
                //pepper_extend[l][515][bytes4]=pepper_extend[l][514][bytes4];
            }

    }
    }
 //--------------------------- NLM ALGORITHM-----------------//
    int sum_val=0;
    int temp=0;
    double norm=0.0;
    int temp1=0;

double final_val=0.0;
for(int row=10;row<522;row++) //Original noisy image coordinates
    {
    for(int col=10;col<522;col++)
        {
            for(int x=0;x<3;x++)
        {
    for(int temp_row=row-10;temp_row<row+9;temp_row++) //big sliding window
    {
    for(int temp_col=col-10;temp_col<col+9;temp_col++)
    {
        for(int small_row=0;small_row<3;small_row++) //small fixed window
        {
            for(int small_col=0;small_col<3;small_col++)
            {
           sum_val=sum_val+(int)pepper_extend[temp_row+small_row][temp_col+small_col][x]; //Computing sum of patch window size

        }
        }
        image[temp1]=(int)pepper_extend[temp_row+1][temp_col+1][x]; //Storing the central pixel intensities of each moving patch
        temp1++;
        vec[temp]=(double)sum_val/9.0; //storing mean of moving patch
        temp++;
        sum_val=0;
        }
        }
        temp=0;
        temp1=0;
        for(int h=0;h<(19*19);h++)
        {
            norm=norm+exp(-1*(fabs(pow((vec[200]-vec[h]),2.0))/(80.0*80.0))); //Calculating overall normalised weight C(p)
        }
        for(int d=0;d<(19*19);d++)
        {
            weight[d]=exp(-1*(fabs(pow((vec[200]-vec[d]),2.0))/(80.0*80.0))); //Gaussian weighting function
            final_val= final_val+(weight[d]*image[d]); //Applying NLM forumla

        }

        pepper_denoised[row-10][col-10][x]=(int)(final_val/norm); //Normalising final val
        norm=0;
        final_val=0.0;
        }
}
    }
    //----------------------PSNR ratio calculation for each channel-------//
    double val_mse=0.0;
	double psnr_red=0.0;
	for(int noise_row=0;noise_row<512;noise_row++)
    {
        for(int noise_col=0;noise_col<512;noise_col++)
        {

          val_mse=val_mse+(1.0/(512.0*512.0))*((int)pepper_denoised[noise_row][noise_col][0]-(int)pepper_free[noise_row][noise_col][0])*((int)pepper_denoised[noise_row][noise_col][0]-(int)pepper_free[noise_row][noise_col][0]);
    }
    }
    psnr_red=10.0*log10((255.0*255.0)/val_mse);
    cout<<psnr_red<<endl;
    double val_mse1=0.0;
	double psnr_green=0.0;
	for(int noise_row=0;noise_row<512;noise_row++)
    {
        for(int noise_col=0;noise_col<512;noise_col++)
        {

          val_mse1=val_mse1+(1.0/(512.0*512.0))*((int)pepper_denoised[noise_row][noise_col][1]-(int)pepper_free[noise_row][noise_col][1])*((int)pepper_denoised[noise_row][noise_col][1]-(int)pepper_free[noise_row][noise_col][1]);
    }
    }
    psnr_green=10.0*log10((255.0*255.0)/val_mse1);
    cout<<psnr_green<<endl;
    double val_mse2=0.0;
	double psnr_blue=0.0;
	for(int noise_row=0;noise_row<512;noise_row++)
    {
        for(int noise_col=0;noise_col<512;noise_col++)
        {

          val_mse2=val_mse2+(1.0/(512.0*512.0))*((int)pepper_denoised[noise_row][noise_col][2]-(int)pepper_free[noise_row][noise_col][2])*((int)pepper_denoised[noise_row][noise_col][2]-(int)pepper_free[noise_row][noise_col][2]);
    }
    }
    psnr_blue=10.0*log10((255.0*255.0)/val_mse2);
    cout<<psnr_blue<<endl;
    if (!(file5=fopen("sailboat_denoised_nlm.raw","wb"))) {
		cout << "Cannot open file: " << "pepper_denoised_nlm.raw" << endl;
		exit(1);
	}
	fwrite(pepper_denoised, sizeof(unsigned char),   512*512*BytesPerPixel, file5);
	printf("File written\n");
	fclose(file5);
 return 0;
}
