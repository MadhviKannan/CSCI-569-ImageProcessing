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
unsigned char tulip_dark[366][400];
unsigned char tulip_white[366][400];
unsigned char tulip_mix[366][400];
unsigned char tulip_dark_enhanced[366][400];
unsigned char tulip_white_enhanced[366][400];
using namespace std;
int main()
{
    FILE *file1, *file2, *file3,*file4,*file5;
    int BytesPerPixel=3;
	int i,j,temp;
	int count_array[256]={0};
	int count_array1[256]={0};
	int count1=0,count2=0;
	double prob_arr[256]={0.0};
	double prob_arr1[256]={0.0};
	double cdf[256]={0.0};
	double cdf_white[256]={0.0};
	double enhanced[256]={0.0};
	double enhanced_white[256]={0.0};
	double cdf_white_temp[256]={0.0};
	if (!(file1=fopen("tulip_dark.raw","rb"))) {
		cout << "Cannot open file: " << "tulip_dark.raw" <<endl;
		exit(1);
	}
	fread(tulip_dark,sizeof(unsigned char), 366*400*BytesPerPixel, file1);
    fclose(file1);

    if (!(file4=fopen("tulip_bright.raw","rb"))) {
		cout << "Cannot open file: " << "tulip_bright.raw" <<endl;
		exit(1);
	}
	fread(tulip_white,sizeof(unsigned char), 366*400*BytesPerPixel, file4);
    fclose(file4);
    ofstream outfile,outfile1,outfile2,outfile3,outfile4,outfile5,outfile6,outfile7;
	outfile.open("E:/MATLAB2016/result.csv");
	outfile1.open("E:/MATLAB2016/result_prob.csv");
    outfile2.open("E:/MATLAB2016/result_cdf.csv");
    outfile3.open("E:/MATLAB2016/result_enhanced.csv");
    outfile4.open("E:/MATLAB2016/result_bright.csv");
	outfile5.open("E:/MATLAB2016/result_prob_bright.csv");
    outfile6.open("E:/MATLAB2016/result_cdf_bright.csv");
    outfile7.open("E:/MATLAB2016/result_enhanced_bright.csv");
        for(int j=0;j<366;j++)
        {
           for(int k=0;k<400;k++)
           {
                  count_array[(int)tulip_dark[j][k]]++;
                  count_array1[(int)tulip_white[j][k]]++;
           }
        }
        for(int y=0;y<256;y++)
        {

        outfile<<count_array[y]<<endl;
        prob_arr[y]=(double)count_array[y]/(366*400);
        prob_arr1[y]=(double)count_array1[y]/(366*400);
        outfile1<<prob_arr[y]<<endl;
        outfile4<<count_array1[y]<<endl;
        outfile5<<prob_arr1[y]<<endl;
        }

        cdf[0]=prob_arr[0];
        //outfile2<<cdf[0]<<endl;
        cdf_white[0]=prob_arr1[256];
        //outfile6<<cdf_white[0]<<endl;
        //int flag = 0;
        //cdf_white[0]=prob_arr1[0];
        for(int m=1;m<256;m++)
        {
            cdf[m]=cdf[m-1]+prob_arr[m];

            cdf_white[m]=cdf_white[m-1]+prob_arr1[m];
            outfile2<<cdf[m]<<endl;
            outfile6<<cdf_white[m]<<endl;
            enhanced[m]=(int)(256*cdf[m]);
            enhanced_white[m]=(int)(256*(cdf_white[m]));
            outfile3<<enhanced[m]<<endl;
            outfile7<<enhanced_white[m]<<endl;

        }


    outfile.close();
    outfile1.close();
    outfile2.close();
    outfile3.close();
    outfile4.close();
    outfile5.close();
    outfile6.close();
    outfile7.close();

    for(int d=0;d<256;d++)
    {
    for(int g=0;g<366;g++)
    {
        for(int h=0;h<400;h++)
        {
                if((int)tulip_dark[g][h]==d)
                {


            tulip_dark_enhanced[g][h]=enhanced[d];}
              if((int)tulip_white[g][h]==d)
                {


            tulip_white_enhanced[g][h]=enhanced_white[d];}

        }
    }
    }
     if (!(file2=fopen("tulip_dark_enhanced.raw","wb"))) {
		cout << "Cannot open file: " << "tulip_dark_enhanced.raw" << endl;
		exit(1);
	}
	fwrite(tulip_dark_enhanced, sizeof(unsigned char),   366*400, file2);
	printf("File written\n");
	fclose(file2);
	 if (!(file5=fopen("tulip_mix_enhanced.raw","wb"))) {
		cout << "Cannot open file: " << "tulip_mix_enhanced.raw" << endl;
		exit(1);
	}
	fwrite(tulip_white_enhanced, sizeof(unsigned char),   366*400, file5);
	printf("File written\n");
	fclose(file5);
	    return 0;

}
