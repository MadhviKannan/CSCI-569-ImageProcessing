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
unsigned char bedroom[400][940][3];
unsigned char bedroom_enhanced[400][940][3];
unsigned char bedroom_hue[400][940];
double bedroom_luminance1[400][940];
unsigned char bedroom_luminance[400][940];
unsigned char bedroom_sat[400][940];

unsigned char final_image[400][940][3];

using namespace std;
int main()
{
    FILE *file1, *file2, *file3,*file4,*file5;
    int BytesPerPixel=3;
    double bedroom_hue_hsl;
double bedroom_luminance_hsl;
double bedroom_sat_hsl;
	int i,j,temp;
	int count_array_red[256]={0};
	int count_array_green[256]={0};
	int count_array_blue[256]={0};
	int count1=0,count2=0;
	double prob_arr_red[256]={0.0};
	double prob_arr_green[256]={0.0};
	double prob_arr_blue[256]={0.0};
	double cdf_red[256]={0.0};
	double cdf_green[256]={0.0};
	double cdf_blue[256]={0.0};
	double enhanced_red[256]={0.0};
	double enhanced_green[256]={0.0};
	double enhanced_blue[256]={0.0};
	double M,m,C,Hue,luminance,saturation,R1,G1,B1,M1,m1,C1,Hue1,luminance1,saturation1,R,G,B;
	if (!(file1=fopen("bedroom.raw","rb"))) {
		cout << "Cannot open file: " << "bedroom.raw" <<endl;
		exit(1);
	}
	fread(bedroom,sizeof(unsigned char), 400*940*BytesPerPixel, file1);
    fclose(file1);

    //HSL conversion of bedroom image to RGB
     for(int i=0;i<400;i++)
    {
        for(int j=0;j<940;j++)
        {
           R= ((int)bedroom[i][j][0])/255.0; //Normalize each intensity value to bring it between 0and 1
           G=((int) bedroom[i][j][1])/255.0;
           B=((int) bedroom[i][j][2])/255.0;
           M=max(R,max(G,B)); //find max of each of the 3 intensities
           m=min(R,min(G,B)); //find min of each of the 3 intensities

             C=(M-m);
             luminance=(M+m)/2; //luminance
             if(luminance==0)
             {
                 saturation=0;
             }
             else if(luminance>0&&luminance<0.5)
             {
                 saturation=C/(2*luminance);
             }
             else
             {
                 saturation=C/(2-2*luminance);
             }
             if(C==0)
             {
                 Hue=0;
             }
             else if(M==R)
             {
                 //cout<<"yes"<<endl;
                 Hue=60.0*fmod(((G-B)/C),6.0);
             }
             else if(M==G)
             {
                 Hue=60.0*(((B-R)/C)+2.0);
                  }
             else if(M==B)
             {
                  Hue=60.0*(((R-G)/C)+4.0);
             }
             else
             {
                 cout<<"invalid"<<endl;
             }
            Hue=Hue*(255.0/360.0);
             //cout<<Hue<<endl;
             saturation=saturation*255.0;
             luminance=luminance*255.0;
             bedroom_hue[i][j]=(int)Hue;
           // outfile<<bedroom_hue[i][j]<<endl;
             //cout<<(int)bedroom_hue[i][j]<<endl;
             bedroom_luminance[i][j]=(int)luminance;
             bedroom_sat[i][j]=(int)saturation;
            // cout<<(int)bedroom_luminance[i][j]<<endl;
        }
    }
    for(int j=0;j<400;j++)
        {
           for(int k=0;k<940;k++)
           {
                 // count_array_red[(int)bedroom_hue[j][k][0]]++;
                  count_array_green[(int)bedroom_luminance[j][k]]++;
                  //count_array_blue[(int)bedroom_sat[j][k][2]]++;

        }
        }
        for(int y=0;y<256;y++)
        {

        prob_arr_green[y]=(double)count_array_green[y]/(400*940);


        }
       // cdf_red[0]=prob_arr_red[0];
         cdf_green[0]=prob_arr_green[0];

        for(int m=1;m<256;m++)
        {
           // cdf_red[m]=cdf_red[m-1]+prob_arr_red[m];
            cdf_green[m]=cdf_green[m-1]+prob_arr_green[m];

            enhanced_green[m]=(int)(255*(cdf_green[m]));

        }

   for(int d=0;d<256;d++)
    {
    for(int g=0;g<400;g++)
    {
        for(int h=0;h<940;h++)
        {
                if(bedroom_luminance[g][h]==d)
                {

            bedroom_luminance1[g][h]=enhanced_green[d];
            //cout<<bedroom_luminance1[g][h]<<endl;
            }

    }
    }
    }
    //--------------------HSL TO RGB---------------------------------
    double X,C2,m2,r_inter,g_inter,b_inter;
    for(int f=0;f<400;f++)
    {
        for(int g=0;g<940;g++)
        {
            bedroom_hue_hsl= (bedroom_hue[f][g]*(360.0/255.0));

            bedroom_luminance_hsl= (bedroom_luminance1[f][g]*(1.0/255.0));

            bedroom_sat_hsl= (bedroom_sat[f][g]*(1.0/255.0));
            C2 = ((1 - fabs(2.0*bedroom_luminance_hsl - 1) )* bedroom_sat_hsl);

            X = C2 * (1 - (fabs(fmod((bedroom_hue_hsl/60.0),2.0) - 1)));

            m2=bedroom_luminance_hsl-(C2/2.0);
            //cout<<m2<<endl;

            if(bedroom_hue_hsl>=0.0&&bedroom_hue_hsl<60.0)
            {
                r_inter=C2;
                g_inter=X;
                b_inter=0;
            }
            if(bedroom_hue_hsl>=60.0&&bedroom_hue_hsl<120.0)
            {
                r_inter=X;
                g_inter=C2;
                b_inter=0;
            }
            if(bedroom_hue_hsl>=120.0&&bedroom_hue_hsl<180.0)
            {
                r_inter=0;
                g_inter=C2;
                b_inter=X;
            }
            if(bedroom_hue_hsl>=180.0&&bedroom_hue_hsl<240.0)
            {
                r_inter=0;
                g_inter=X;
                b_inter=C2;
            }
            if(bedroom_hue_hsl>=240&&bedroom_hue_hsl<300)
            {
                r_inter=X;
                g_inter=0;
                b_inter=C2;
            }
            if(bedroom_hue_hsl>=300.0&&bedroom_hue_hsl<360.0)
            {
                r_inter=C2;
                g_inter=0;
                b_inter=X;
            }
            final_image[f][g][0]=(int)(255*(r_inter+m2));
            final_image[f][g][1]=(int)(255*(g_inter+m2));
            final_image[f][g][2]=(int)(255*(b_inter+m2));
            //cout<<final_image[g][h][0]<<endl;

        }
    }



if (!(file2=fopen("bedroom_enhanced.raw","wb"))) {
		cout << "Cannot open file: " << "bedroom_enhanced.raw" << endl;
		exit(1);
	}
	fwrite(final_image, sizeof(unsigned char),   400*940*BytesPerPixel, file2);
	printf("File written\n");
	fclose(file2);
        return 0;

}
