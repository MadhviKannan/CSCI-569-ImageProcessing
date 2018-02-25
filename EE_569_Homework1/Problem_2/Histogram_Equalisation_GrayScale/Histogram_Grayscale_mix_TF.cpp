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
	double count_array_dark[256]={0};
	double prob_arr[256]={0.0};
	double cdf[256]={0.0};
	double enhanced[256]={0.0};
	int min_mix,max_mix;

    if (!(file1=fopen("tulip_mix.raw","rb"))) {
		cout << "Cannot open file: " << "tulip_mix.raw" <<endl;
		exit(1);
	}
	fread(tulip_mix,sizeof(unsigned char), 366*400, file1);
    fclose(file1);
    ofstream outfile,outfile2,outfile3,outfile4,outfile6,outfile7;
	outfile.open("E:/MATLAB2016/result_count.csv"); //csv file for count of dark image
    outfile2.open("E:/MATLAB2016/result_tf_dark.csv"); //csv file for linear tf of dark image
    outfile3.open("E:/MATLAB2016/result_enhanced.csv");
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
        if(count_array[y]!=0)
        {
             max_mix=y;
        }

        }
        for(int t=256;t>0;t--)
        {
            if(count_array[t]!=0)
            {
                min_mix=t-1;
            }

        }
        cout<<min_mix<<endl;
        cout<<max_mix<<endl;
         double slope_mix=(255.0)/(max_mix-min_mix);
         cout<<slope_mix<<endl;
          outfile.close();

    for(int g=0;g<366;g++)
    {
        for(int h=0;h<400;h++)
        {

            tulip_mix_enhanced[g][h]=slope_mix*(tulip_mix[g][h]-min_mix);

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
