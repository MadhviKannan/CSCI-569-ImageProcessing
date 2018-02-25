# EE569 :Homework Assignment #1
# Date  : February 5, 2017
# Name  : Madhvi Kannan
# USC ID: 2159965290
# email : mkannan@usc.edu
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include<algorithm>
#include<math.h>
unsigned char Imagedata_cat[600][398][3];
	unsigned char cat_hue[600][398];
	unsigned char cat_luminance[600][398];
    unsigned char cat_sat[600][398];
   unsigned char Imagedata_dolphin[640][480][3];
	unsigned char dolphin_hue[640][480];
	unsigned char dolphin_luminance[640][480];
    unsigned char dolphin_sat[640][480];
using namespace std;
int main()
{
    FILE *file,*file1,*file2,*file3,*file4,*file5,*file6,*file7;
	int BytesPerPixel=3;
	int i,j,temp;
	double M,m,C,Hue,luminance,saturation,R1,G1,B1,M1,m1,C1,Hue1,luminance1,saturation1,R,G,B;

	if (!(file=fopen("cat.raw","rb"))) {
		cout << "Cannot open file: " << "cat.raw" <<endl;
		exit(1);
	}
	fread(Imagedata_cat,sizeof(unsigned char), 600*398*BytesPerPixel, file);
    fclose(file);
    if (!(file4=fopen("dolphin.raw","rb"))) {
		cout << "Cannot open file: " << "dolphin.raw" <<endl;
		exit(1);
	}
	fread(Imagedata_dolphin,sizeof(unsigned char), 640*480*BytesPerPixel, file4);
    fclose(file4);

    for(int i=0;i<600;i++)
    {
        for(int j=0;j<398;j++)
        {
           R= ((int)Imagedata_cat[i][j][0])/255.0; //Normalize each intensity value to bring it between 0and 1
           G=((int) Imagedata_cat[i][j][1])/255.0;
           B=((int) Imagedata_cat[i][j][2])/255.0;
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
             cat_hue[i][j]=(int)Hue;
            // cout<<cat_hue[i][j]<<endl;
             cat_luminance[i][j]=(int)luminance;
             cat_sat[i][j]=(int)saturation;
        }
    }
        for(int m=0;m<640;m++)
    {
        for(int n=0;n<480;n++)
        {
           R1= ((int)Imagedata_dolphin[m][n][0])/255.0;
           G1=((int) Imagedata_dolphin[m][n][1])/255.0;
           B1=((int) Imagedata_dolphin[m][n][2])/255.0;
           M1=max(R1,max(G1,B1));
           m1=min(R1,min(G1,B1));

             C1=(M1-m1);
             luminance1=(M1+m1)/2;
             if(luminance1==0)
             {
                 saturation1=0;
             }
             else if(luminance1>0&&luminance1<0.5)
             {
                 saturation1=C1/(2*luminance1);
             }
             else
             {
                 saturation1=C1/(2-2*luminance1);
             }
             if(C1==0)
             {
                 Hue1=0;
             }
             else if(M1==R1)
             {
                 //cout<<"yes"<<endl;
                 Hue1=60.0*fmod(((G1-B1)/C1),6.0);
             }
             else if(M1==G1)
             {
                 Hue1=60.0*(((B1-R1)/C1)+2.0);
                  }
             else if(M1==B1)
             {
                  Hue1=60.0*(((R1-G1)/C1)+4.0);
             }
             else
             {
                 cout<<"invalid"<<endl;
             }
             Hue1=Hue1*(255.0/360.0);
             //cout<<Hue<<endl;
             saturation1=saturation1*255.0;
             luminance1=luminance1*255.0;
             dolphin_hue[m][n]=(int)Hue1;
            // cout<<cat_hue[i][j]<<endl;
             dolphin_luminance[m][n]=(int)luminance1;
             dolphin_sat[m][n]=(int)saturation1;
        }
    }

   if (!(file1=fopen("cat1.raw","wb"))) {
		cout << "Cannot open file: " << "cat1.raw" << endl;
		exit(1);
	}

	fwrite(cat_hue, sizeof(unsigned char),   600*398, file1);
	printf("File written\n");
	fclose(file1);
	if (!(file2=fopen("cat_luminance.raw","wb"))) {
		cout << "Cannot open file: " << "cat_luminance.raw" << endl;
		exit(1);
	}

	fwrite(cat_luminance, sizeof(unsigned char),   600*398, file2);
	printf("File written\n");
	fclose(file2);
	if (!(file3=fopen("cat_sat.raw","wb"))) {
		cout << "Cannot open file: " << "cat_sat.raw" << endl;
		exit(1);
	}

	fwrite(cat_sat, sizeof(unsigned char),   600*398, file3);
	printf("File written\n");
	fclose(file3);

	if (!(file5=fopen("dolphin_hue.raw","wb"))) {
		cout << "Cannot open file: " << "dolphin_hue.raw" << endl;
		exit(1);
	}

	fwrite(dolphin_hue, sizeof(unsigned char),   640*480, file5);
	printf("File written\n");
	fclose(file5);
	if (!(file6=fopen("dolphin_luminance.raw","wb"))) {
		cout << "Cannot open file: " << "dolphin_luminance.raw" << endl;
		exit(1);
	}

	fwrite(dolphin_luminance, sizeof(unsigned char),   640*480, file6);
	printf("File written\n");
	fclose(file6);
	if (!(file7=fopen("dolphin_sat.raw","wb"))) {
		cout << "Cannot open file: " << "dolphin_sat.raw" << endl;
		exit(1);
	}

	fwrite(dolphin_sat, sizeof(unsigned char),   640*480, file7);
	printf("File written\n");
	fclose(file7);


	return 0;
}








