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
unsigned char pepper_extend[516][516][3];
unsigned char pepper_denoised[512][512][3];
unsigned char pepper_denoised_median[512][512][3];
unsigned char pepper_denoised_gauss[512][512][3];
unsigned char pepper_free[512][512][3];
unsigned char mean[3][3]={1};
//unsigned median[3][3];
//mean_median
using namespace std;
int main()
{
    FILE *file1, *file2, *file3,*file4,*file5,*file6;
    int BytesPerPixel=3;
    int i,j;
    if (!(file1=fopen("pepper_noisy.raw","rb"))) {
		cout << "Cannot open file: " << "pepper_noisy.raw" <<endl;
		exit(1);
	}
	fread(pepper,sizeof(unsigned char), 512*512*BytesPerPixel, file1);
    fclose(file1);
    if (!(file1=fopen("pepper.raw","rb"))) {
		cout << "Cannot open file: " << "pepper.raw" <<endl;
		exit(1);
	}
	fread(pepper_free,sizeof(unsigned char), 512*512*BytesPerPixel, file1);
    fclose(file1);
//----------------------BOUNDARY EXTENSION-------------------------//
    for(int m=0;m<512;m++)
    {
        for(int n=0;n<512;n++)
        {
            for(int bytes=0;bytes<3;bytes++)
            {
                pepper_extend[m+1][n+1][bytes]=pepper[m][n][bytes];
            }
        }
    }
    for(int i=1;i<513;i++)
    {
        for(int bytes1=0;bytes1<3;bytes1++)
            {
                pepper_extend[0][i][bytes1]=pepper_extend[1][i][bytes1];
                pepper_extend[513][i][bytes1]=pepper_extend[512][i][bytes1];
            }

    }
    for(int j=1;j<514;j++)
    {
        for(int bytes2=0;bytes2<3;bytes2++)
            {
                pepper_extend[j][0][bytes2]=pepper_extend[j][1][bytes2];
                pepper_extend[j][513][bytes2]=pepper_extend[j][512][bytes2];
            }

    }
     //------------------GAUSSIAN FILTERING---------------------//
int gauss[3][3]={1,2,1,2,4,2,1,2,1}; //Gaussian kernel for 3x3 mask
double sum_val=0.0;
for(int row=0;row<514;row++)
    {
    for(int col=0;col<514;col++)
        {
            for(int x=0;x<3;x++)
        {
    for(int temp_row=0;temp_row<3;temp_row++)
    {

    for(int temp_col=0;temp_col<3;temp_col++)
        {
            sum_val=sum_val+((int)pepper_extend[row+temp_row][col+temp_col][x]*gauss[temp_row][temp_col]);
        }
        }
        pepper_denoised_gauss[row][col][x]=(int)((1.0/16.0)*sum_val);
               sum_val=0;
    }
        }
    }


    if (!(file3=fopen("pepper_denoised_gauss.raw","wb"))) {
		cout << "Cannot open file: " << "pepper_denoised_gauss.raw" << endl;
		exit(1);
	}
	fwrite(pepper_denoised_gauss, sizeof(unsigned char),   512*512*BytesPerPixel, file3);
	printf("File written\n");
	fclose(file3);
	   if (!(file1=fopen("pepper_denoised_gauss.raw","rb"))) {
		cout << "Cannot open file: " << "pepper_denoised_gauss.raw" <<endl;
		exit(1);
	}
	fread(pepper_denoised_gauss,sizeof(unsigned char), 512*512*BytesPerPixel, file1);
    fclose(file1);
    //----------------------BOUNDARY EXTENSION-------------------------//
    for(int m=0;m<512;m++)
    {
        for(int n=0;n<512;n++)
        {
            for(int bytes=0;bytes<3;bytes++)
            {
                pepper_extend[m+1][n+1][bytes]=pepper_denoised_gauss[m][n][bytes];
            }
        }
    }
    for(int i=1;i<513;i++)
    {
        for(int bytes1=0;bytes1<3;bytes1++)
            {
                pepper_extend[0][i][bytes1]=pepper_extend[1][i][bytes1];
                pepper_extend[513][i][bytes1]=pepper_extend[512][i][bytes1];
            }

    }
    for(int j=1;j<514;j++)
    {
        for(int bytes2=0;bytes2<3;bytes2++)
            {
                pepper_extend[j][0][bytes2]=pepper_extend[j][1][bytes2];
                pepper_extend[j][513][bytes2]=pepper_extend[j][512][bytes2];
            }

    }
    //-------------------------------MEDIAN FILTERING------------------//
         int temp[9]={0};
     int run;
     for(int x=0;x<3;x++)
     {
for(int row=0;row<512;row++)
    {
    for(int col=0;col<512;col++)
        {
            run=0;

        for(int temp_row=0;temp_row<3;temp_row++)
            {
            for(int temp_col=0;temp_col<3;temp_col++)
            {
            temp[run]=pepper_extend[row+temp_row][col+temp_col][x];
            run=run+1;
        }
        }
        for(int i=0;i<9;i++) //Bubble sorting algorithm
        {
            for(j=i+1;j<9;j++)
            {
                if(temp[i]>temp[j])
                {
                    int a=temp[i];
                    temp[i]=temp[j];
                    temp[j]=a;
                }
            }
        }
        pepper_denoised_median[row][col][x]=temp[4]; //Replace with middle value
        }
    }
        }
         if (!(file3=fopen("pepper_denoised_gaussmedian.raw","wb"))) {
		cout << "Cannot open file: " << "pepper_denoised_gaussmedian.raw" << endl;
		exit(1);
	}
	fwrite(pepper_denoised_median, sizeof(unsigned char),   512*512*BytesPerPixel, file3);
	printf("File written\n");
	fclose(file3);


		double val_mse=0.0;
	double psnr_red=0.0;
	for(int noise_row=0;noise_row<512;noise_row++)
    {
        for(int noise_col=0;noise_col<512;noise_col++)
        {

          val_mse=val_mse+(1.0/(512.0*512.0))*((int)pepper_denoised_median[noise_row][noise_col][0]-(int)pepper_free[noise_row][noise_col][0])*((int)pepper_denoised_median[noise_row][noise_col][0]-(int)pepper_free[noise_row][noise_col][0]);
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

          val_mse1=val_mse1+(1.0/(512.0*512.0))*((int)pepper_denoised_median[noise_row][noise_col][1]-(int)pepper_free[noise_row][noise_col][1])*((int)pepper_denoised_median[noise_row][noise_col][1]-(int)pepper_free[noise_row][noise_col][1]);
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

          val_mse2=val_mse2+(1.0/(512.0*512.0))*((int)pepper_denoised_median[noise_row][noise_col][2]-(int)pepper_free[noise_row][noise_col][2])*((int)pepper_denoised_median[noise_row][noise_col][2]-(int)pepper_free[noise_row][noise_col][2]);
    }
    }
    psnr_blue=10.0*log10((255.0*255.0)/val_mse2);
    cout<<psnr_blue<<endl;

    return 0;
}
