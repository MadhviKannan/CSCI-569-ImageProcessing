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
unsigned char tulip_mix[366][400];
unsigned char tulip_mix_enhanced[366][400];

using namespace std;

int main()
{
     FILE *file1, *file2, *file3,*file4,*file5;
    int BytesPerPixel=3;
	int i,j,temp;
	int count_array[256]={0};
	//int count_array1[256]={0};
	int count1=0,count2=0;
	double prob_arr[256]={0.0};
	//double prob_arr1[256]={0.0};
	double cdf[256]={0.0};
	//double cdf_white[256]={0.0};
	double enhanced[256]={0.0};
	if (!(file1=fopen("tulip_mix.raw","rb"))) {
		cout << "Cannot open file: " << "tulip_mix.raw" <<endl;
		exit(1);
	}
	fread(tulip_mix,sizeof(unsigned char), 366*400, file1);
    fclose(file1);
    ofstream outfile,outfile1,outfile2,outfile3;
	outfile.open("E:/MATLAB2016/TulipMix/count.csv");
	outfile1.open("E:/MATLAB2016/TulipMix/count_prob.csv");
    outfile2.open("E:/MATLAB2016/TulipMix/result_cdf.csv");
    outfile3.open("E:/MATLAB2016/TulipMix/result_enhanced.csv");
    for(int j=0;j<366;j++)
        {
           for(int k=0;k<400;k++)
           {
                  count_array[(int)tulip_mix[j][k]]++;

           }
        }

    for(int y=0;y<256;y++)
        {

        outfile<<count_array[y]<<endl;
        prob_arr[y]=(double)count_array[y]/(366*400);
        outfile1<<prob_arr[y]<<endl;
        }
        cdf[0]=prob_arr[0];

        for(int m=1;m<256;m++)
        {
            cdf[m]=cdf[m-1]+prob_arr[m];
            outfile2<<cdf[m]<<endl;
            enhanced[m]=(int)(100*cdf[m]);
            outfile3<<enhanced[m]<<endl;
        }
         outfile.close();
    outfile1.close();
    outfile2.close();
    outfile3.close();
for(int d=0;d<256;d++)
    {
    for(int g=0;g<366;g++)
    {
        for(int h=0;h<400;h++)
        {
                if((int)tulip_mix[g][h]==d)
                {


            tulip_mix_enhanced[g][h]=enhanced[d];}

        }
    }
    }
if (!(file2=fopen("tulip_mix_enhanced.raw","wb"))) {
		cout << "Cannot open file: " << "tulip_mix_enhanced.raw" << endl;
		exit(1);
	}
	fwrite(tulip_mix_enhanced, sizeof(unsigned char),   366*400, file2);
	printf("File written\n");
	fclose(file2);



   return 0;
}
