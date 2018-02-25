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
	double count_array_dark[256]={0};
	double count_array_bright[256]={0};
	int count1=0,count2=0;
	double prob_arr[256]={0.0};
	double prob_arr1[256]={0.0};
	double cdf[256]={0.0};
	double cdf_white[256]={0.0};
	double enhanced[256]={0.0};
	double enhanced_white[256]={0.0};
	double cdf_white_temp[256]={0.0};
	int min_dark, min_bright,max_dark,max_bright;
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
    ofstream outfile,outfile2,outfile3,outfile4,outfile6,outfile7;
	outfile.open("E:/MATLAB2016/result.csv"); //csv file for count of dark image
    outfile2.open("E:/MATLAB2016/result_tf_dark.csv"); //csv file for linear tf of dark image
    outfile3.open("E:/MATLAB2016/result_enhanced.csv");
    outfile4.open("E:/MATLAB2016/result_bright.csv"); //csv file for count of bright image
    outfile6.open("E:/MATLAB2016/result_tf_bright.csv"); //csv file for tf of bright image
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
        outfile4<<count_array1[y]<<endl;
        if(count_array[y]!=0)
        {
             max_dark=y;
        }
        if(count_array1[y]!=0)
        {
            max_bright=y;
        }
        }
        for(int t=256;t>0;t--)
        {
            if(count_array[t]!=0)
            {
                min_dark=t-1;
            }
            if(count_array1[t]!=0)
            {
                min_bright=t-1;
            }
        }
        cout<<min_dark<<endl;
        cout<<min_bright<<endl;
         double slope_dark=(255.0)/(max_dark-min_dark);
         cout<<slope_dark<<endl;
         double slope_bright=255.0/(max_bright-min_bright);
         cout<<slope_bright<<endl;

      /*  for(int m=0;m<256;m++)
        {
            count_array_dark[m]=slope_dark*(count_array[m]-min_dark);
            count_array_bright[m]=abs(slope_bright*(count_array1[m]-min_bright));
            if((int)count_array[m]>256)
            {
                count_array[m]=256;
            }
            if(count_array1[m]>256)
            {
                count_array1[m]=256;
            }
            outfile2<<count_array_dark[m]<<endl;
            outfile6<<count_array_bright[m]<<endl;


        }*/


    outfile.close();

    //outfile2.close();
    outfile3.close();
    outfile4.close();

    //outfile6.close();
    outfile7.close();


    for(int g=0;g<366;g++)
    {
        for(int h=0;h<400;h++)
        {



            tulip_dark_enhanced[g][h]=slope_dark*(tulip_dark[g][h]-min_dark);



            tulip_white_enhanced[g][h]=slope_bright*(tulip_white[g][h]-min_bright);

        }
    }

    


	 if (!(file5=fopen("tulip_white_enhanced.raw","wb"))) {
		cout << "Cannot open file: " << "tulip_white_enhanced.raw" << endl;
		exit(1);
	}
	fwrite(tulip_white_enhanced, sizeof(unsigned char),   366*400, file5);
	printf("File written\n");
	fclose(file5);
	    return 0;

}
