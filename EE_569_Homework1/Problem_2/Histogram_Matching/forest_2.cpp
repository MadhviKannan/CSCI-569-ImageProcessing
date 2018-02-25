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
#include<tgmath.h>
unsigned char forest[413][550][3];
unsigned char forest_transform[413][550][3];
using namespace std;
int main()
{
    FILE *file1, *file2, *file3,*file4,*file5;
    int BytesPerPixel=3;
	int i,j,temp;
	int count_array_red[256]={0};
	int count_array_green[256]={0};
	int count_array_blue[256]={0};
	double prob_arr_red[256]={0.0};
	double prob_arr_green[256]={0.0};
	double prob_arr_blue[256]={0.0};
	double prob_red_norm[256]={0.0};
	double prob_green_norm[256]={0.0};
	double prob_blue_norm[256]={0.0};
	double cdf_red[256]={0.0};
	double cdf_green[256]={0.0};
	double cdf_blue[256]={0.0};
	double cdf_norm[256]={0.0};
	//double cdf_green_norm[256]={0.0};
	//double cdf_blue_norm[256]={0.0};
	/*double enhanced_red[256]={0.0};
	double enhanced_green[256]={0.0};
	double enhanced_blue[256]={0.0};
	double enhanced_red_norm[256]={0.0};
	double enhanced_green_norm[256]={0.0};
	double enhanced_blue_norm[256]={0.0};*/
	if (!(file1=fopen("forest_2.raw","rb"))) {
		cout << "Cannot open file: " << "forest_2.raw" <<endl;
		exit(1);
	}
	fread(forest,sizeof(unsigned char), 413*550*BytesPerPixel, file1);
    fclose(file1);
     ofstream outfile,outfile1,outfile2,outfile3,outfile4,outfile5,outfile6,outfile7,outfile8,outfile9,outfile10,outfile11,outfile12,outfile13,outfile14,outfile15,outfile16,outfile17,outfile18,outfile19,outfile20,outfile21,outfile22,outfile23;
     outfile.open("E:/MATLAB2016/Forest/count_red.csv");
	outfile1.open("E:/MATLAB2016/Forest/count_green.csv");
    outfile2.open("E:/MATLAB2016/Forest/count_blue.csv");
    outfile3.open("E:/MATLAB2016/Forest/prob_red.csv");
    outfile4.open("E:/MATLAB2016/Forest/prob_green.csv");
	outfile5.open("E:/MATLAB2016/Forest/prob_blue.csv");
	outfile6.open("E:/MATLAB2016/Forest/cdf_red.csv");
    outfile7.open("E:/MATLAB2016/Forest/cdf_green.csv");
    outfile8.open("E:/MATLAB2016/Forest/cdf_blue.csv");
    outfile12.open("E:/MATLAB2016/Forest/prob_red_norm.csv");
    outfile15.open("E:/MATLAB2016/Forest/cdf_norm.csv");
    outfile16.open("E:/MATLAB2016/Forest/cdf_green_norm.csv");
    outfile17.open("E:/MATLAB2016/Forest/cdf_blue_norm.csv");
    outfile21.open("E:/MATLAB2016/Forest/count_new_red.csv");
    outfile22.open("E:/MATLAB2016/Forest/count_new_green.csv");
    outfile23.open("E:/MATLAB2016/Forest/count_new_blue.csv");
    for(int j=0;j<413;j++)
        {
           for(int k=0;k<550;k++)
        {

                  count_array_red[(int)forest[j][k][0]]++;
                  count_array_green[(int)forest[j][k][1]]++;
                  count_array_blue[(int)forest[j][k][2]]++;

        }
        }
        double sigma=20.0;
        double mu=70.0;
        for(int y=0;y<256;y++)
        {
            outfile<<count_array_red[y]<<endl;
            outfile1<<count_array_green[y]<<endl;
            outfile2<<count_array_blue[y]<<endl;
            prob_arr_red[y]=(double)count_array_red[y]/(413*550);
            prob_arr_green[y]=(double)count_array_green[y]/(413*550);
            prob_arr_blue[y]=(double)count_array_blue[y]/(413*550);
            prob_red_norm[y]=(double)0.019947114*exp(-0.00125*((y-mu)*(y-mu)));
            outfile3<<prob_arr_red[y]<<endl;
            outfile4<<prob_arr_green[y]<<endl;
            outfile5<<prob_arr_blue[y]<<endl;
             outfile12<<prob_red_norm[y]<<endl;
        }
        cdf_red[0]=prob_arr_red[0];
         cdf_green[0]=prob_arr_green[0];
          cdf_blue[0]=prob_arr_blue[0];
          cdf_norm[0]=prob_red_norm[0];

        for(int m=1;m<256;m++)
        {
            cdf_red[m]=cdf_red[m-1]+prob_arr_red[m];
            cdf_green[m]=cdf_green[m-1]+prob_arr_green[m];
            cdf_blue[m]=cdf_blue[m-1]+prob_arr_blue[m];
            cdf_norm[m]=cdf_norm[m-1]+prob_red_norm[m];
            outfile6<<cdf_red[m]<<endl;
            outfile7<<cdf_green[m]<<endl;
            outfile8<<cdf_blue[m]<<endl;
            outfile15<<cdf_norm[m]<<endl;

        }

for(int f=0;f<413;f++)
{
    for( int g=0;g<550;g++)
    {

            unsigned char pix=forest[f][g][0];
            double pix_cdf=cdf_red[pix];
            for(int h=0;h<255;h++ )
            {
            if(cdf_norm[h]>pix_cdf)
            {
               break;
            }
            forest_transform[f][g][0]=(unsigned char)h;
            }

    }
}

for(int f=0;f<413;f++)
{
    for( int g=0;g<550;g++)
    {

 unsigned char pix=forest[f][g][1];
            double pix_cdf=cdf_green[pix];
            for(int h=0;h<255;h++ )
            {
            if(cdf_norm[h]>pix_cdf)
            {
               break;
            }
            forest_transform[f][g][1]=(unsigned char)h;
            }


        }


    }

for(int f=0;f<413;f++)
{
    for( int g=0;g<550;g++)
    {

 unsigned char pix=forest[f][g][2];
            double pix_cdf=cdf_blue[pix];
            for(int h=0;h<255;h++ )
            {
            if(cdf_norm[h]>pix_cdf)
            {
               break;
            }
            forest_transform[f][g][2]=(unsigned char)h;
            }


        }
    }
int count_new_red[256]={0};
int count_new_green[256]={0};
int count_new_blue[256]={0};
 for(int c=0;c<413;c++)
        {
           for(int v=0;v<550;v++)
           {

                  count_new_red[(int)forest_transform[c][v][0]]++;
                  count_new_green[(int)forest_transform[c][v][1]]++;
                  count_new_blue[(int)forest_transform[c][v][2]]++;

        }
        }
        for(int b=0;b<256;b++)
        {
            outfile21<<count_new_red[b]<<endl;
            outfile22<<count_new_green[b]<<endl;
            outfile23<<count_new_blue[b]<<endl;
        }

        outfile.close();
        outfile1.close();
        outfile2.close();
        outfile3.close();
        outfile4.close();
        outfile5.close();
        outfile6.close();
        outfile7.close();
        outfile8.close();
        outfile9.close();
        outfile10.close();
        outfile11.close();
        outfile12.close();
        outfile13.close();
        outfile14.close();
        outfile15.close();
        outfile16.close();
        outfile17.close();
        outfile18.close();
        outfile19.close();
        outfile20.close();
        outfile21.close();
        outfile22.close();
        outfile23.close();
if (!(file2=fopen("forest_enhanced.raw","wb"))) {
		cout << "Cannot open file: " << "forest_enhanced.raw" << endl;
		exit(1);
	}
	fwrite(forest_transform, sizeof(unsigned char),   413*550*BytesPerPixel, file2);
	printf("File written\n");
	fclose(file2);
    return 0;
}

