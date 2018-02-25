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
    for(int m=0;m<512;m++)
    {
        for(int n=0;n<512;n++)
        {
            for(int bytes=0;bytes<3;bytes++)
            {
                pepper_extend[m+2][n+2][bytes]=pepper[m][n][bytes];

            }
        }
    }
    for(int i=2;i<514;i++)
    {
        for(int bytes1=0;bytes1<3;bytes1++)
            {
                pepper_extend[1][i][bytes1]=pepper_extend[2][i][bytes1];
                pepper_extend[514][i][bytes1]=pepper_extend[514][i][bytes1];
            }

    }
    for(int j=1;j<515;j++)
    {
        for(int bytes2=0;bytes2<3;bytes2++)
            {
                pepper_extend[j][1][bytes2]=pepper_extend[j][2][bytes2];
                pepper_extend[j][514][bytes2]=pepper_extend[j][513][bytes2];
            }

    }
    for(int k=1;k<515;k++)
    {
        for(int bytes1=0;bytes1<3;bytes1++)
            {
                pepper_extend[0][k][bytes1]=pepper_extend[1][k][bytes1];
                pepper_extend[515][k][bytes1]=pepper_extend[515][k][bytes1];
            }

    }
    for(int l=0;l<516;l++)
    {
        for(int bytes1=0;bytes1<3;bytes1++)
            {
                pepper_extend[l][0][bytes1]=pepper_extend[l][1][bytes1];
                pepper_extend[l][515][bytes1]=pepper_extend[l][514][bytes1];
            }

    }
    //Mean filter
     int temp_row=0;
    int temp_col=0;
    int sum_val=0;
for(int row=0;row<514;row++)
    {
    for(int col=0;col<514;col++)
        {
            for(int x=0;x<3;x++)
        {
    for(int temp_row=0;temp_row<5;temp_row++)
    {

    for(int temp_col=0;temp_col<5;temp_col++)
        {
            sum_val=sum_val+((int)pepper_extend[row+temp_row][col+temp_col][x]);
        }
        }
        pepper_denoised[row][col][x]=(int)((1.0/25.0)*sum_val);
               sum_val=0;
    }
        }
    }
     //Gaussian filter
int gauss[5][5]={1,4,7,4,1,4,16,26,16,4,7,26,41,26,7,4,16,26,16,4,1,4,7,4,1};
for(int row=0;row<514;row++)
    {
    for(int col=0;col<514;col++)
        {
            for(int x=0;x<3;x++)
        {
    for(int temp_row=0;temp_row<5;temp_row++)
    {

    for(int temp_col=0;temp_col<5;temp_col++)
        {
            sum_val=sum_val+((int)pepper_extend[row+temp_row][col+temp_col][x]*gauss[temp_row][temp_col]);
        }
        }
        pepper_denoised_gauss[row][col][x]=(int)((1.0/273.0)*sum_val);
               sum_val=0;
    }
        }
    }
//Median
//Median filter
     int temp[25]={0};
     int run;
     for(int x=0;x<3;x++)
     {
for(int row=0;row<512;row++)
    {
    for(int col=0;col<512;col++)
        {
            run=0;

        for(int temp_row=0;temp_row<5;temp_row++)
            {
            for(int temp_col=0;temp_col<5;temp_col++)
            {
            temp[run]=pepper_extend[row+temp_row][col+temp_col][x];
            run=run+1;
        }
        }
        for(int i=0;i<25;i++)
        {
            for(j=i+1;j<25;j++)
            {
                if(temp[i]>temp[j])
                {
                    int a=temp[i];
                    temp[i]=temp[j];
                    temp[j]=a;
                }
            }
        }
        pepper_denoised_median[row][col][x]=temp[12];
        }
    }
        }
    if (!(file5=fopen("pepper_extend.raw","wb"))) {
		cout << "Cannot open file: " << "pepper_extend.raw" << endl;
		exit(1);
	}
    fwrite(pepper_extend, sizeof(unsigned char),   516*516*BytesPerPixel, file5);
	printf("File written\n");
	fclose(file5);
	if (!(file5=fopen("pepper_extend_mean.raw","wb"))) {
		cout << "Cannot open file: " << "pepper_extend_mean.raw" << endl;
		exit(1);
	}
    fwrite(pepper_denoised, sizeof(unsigned char),   512*512*BytesPerPixel, file5);
	printf("File written\n");
	fclose(file5);
	if (!(file5=fopen("pepper_extend_gauss.raw","wb"))) {
		cout << "Cannot open file: " << "pepper_extend_gauss.raw" << endl;
		exit(1);
	}
    fwrite(pepper_denoised_gauss, sizeof(unsigned char),   512*512*BytesPerPixel, file5);
	printf("File written\n");
	fclose(file5);
	if (!(file5=fopen("pepper_extend_median.raw","wb"))) {
		cout << "Cannot open file: " << "pepper_extend_median.raw" << endl;
		exit(1);
	}
    fwrite(pepper_denoised_median, sizeof(unsigned char),   512*512*BytesPerPixel, file5);
	printf("File written\n");
	fclose(file5);
		double val_mse=0.0;
	double psnr_red=0.0;
	for(int noise_row=0;noise_row<512;noise_row++)
    {
        for(int noise_col=0;noise_col<512;noise_col++)
        {

          val_mse=val_mse+(1.0/(512.0*512.0))*((int)pepper_denoised_gauss[noise_row][noise_col][0]-(int)pepper_free[noise_row][noise_col][0])*((int)pepper_denoised_gauss[noise_row][noise_col][0]-(int)pepper_free[noise_row][noise_col][0]);
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

          val_mse1=val_mse1+(1.0/(512.0*512.0))*((int)pepper_denoised_gauss[noise_row][noise_col][1]-(int)pepper_free[noise_row][noise_col][1])*((int)pepper_denoised_gauss[noise_row][noise_col][1]-(int)pepper_free[noise_row][noise_col][1]);
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

          val_mse2=val_mse2+(1.0/(512.0*512.0))*((int)pepper_denoised_gauss[noise_row][noise_col][2]-(int)pepper_free[noise_row][noise_col][2])*((int)pepper_denoised_gauss[noise_row][noise_col][2]-(int)pepper_free[noise_row][noise_col][2]);
    }
    }
    psnr_blue=10.0*log10((255.0*255.0)/val_mse2);
    cout<<psnr_blue<<endl;
return 0;
}
