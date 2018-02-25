# EE569 :Homework Assignment #1
# Date  : February 5, 2017
# Name  : Madhvi Kannan
# USC ID: 2159965290
# email : mkannan@usc.edu
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
using namespace std;
unsigned char Imagedata[808][1914][3];
	unsigned char Imagesepia[808][1914][3];
	unsigned char Imagedata_grey[808][1914];
int main()
{
    FILE *file;
	int BytesPerPixel=3;
	int i,j,temp;

	if (!(file=fopen("beach.raw","rb"))) {
		cout << "Cannot open file: " << "beach.raw" <<endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), 808*1914*BytesPerPixel, file);
    fclose(file);
	for(int i=0;i<808;i++)
    {
        for(int j=0;j<1914;j++)
        {
            Imagedata_grey[i][j]=0.21*Imagedata[i][j][0]+0.72*Imagedata[i][j][1]+0.07*Imagedata[i][j][2];//convert RGB to grey scale


        }
    }
    if (!(file=fopen("beach_grey.raw","wb"))) {
		cout << "Cannot open file: " << "beach_grey.raw" << endl;
		exit(1);
	}

	fwrite(Imagedata_grey, sizeof(unsigned char),   808*1914, file); //greyscale image
	printf("File written\n");
	fclose(file);
	if (!(file=fopen("beach_grey.raw","rb"))) {
		cout << "Cannot open file: " << "beach_grey.raw" <<endl;
		exit(1);
	}
	fread(Imagedata_grey, sizeof(unsigned char), 808*1914, file);
    fclose(file);

    for(int k=0;k<808;k++)
    {
        for(int l=0;l<1914;l++)
        {

            if((int)(1.351*Imagedata_grey[k][l])>255) //convert red channel grey sclae to sepia
            {
                Imagesepia[k][l][0]=255; //if intensity is greater than 255, lock intensity to 255
            }
            else{
                Imagesepia[k][l][0]=1.351*Imagedata_grey[k][l];
            }
            if((int)(1.204*Imagedata_grey[k][l])>255)//convert green channel grey scale to sepia
            {
                Imagesepia[k][l][1]=255;
            }
            else{
                Imagesepia[k][l][1]=1.204*Imagedata_grey[k][l];
            }
             if((int)(0.937*Imagedata_grey[k][l])>255)
            {
                Imagesepia[k][l][2]=255;
            }
            else{
                Imagesepia[k][l][2]=0.937*Imagedata_grey[k][l];
            }

        }
    }


	if (!(file=fopen("beach_sepia.raw","wb"))) {
		cout << "Cannot open file: " << "beach_sepia.raw" << endl;
		exit(1);
	}
	fwrite(Imagesepia, sizeof(unsigned char),   808*1914*BytesPerPixel, file);
	printf("File written\n");
	fclose(file);


	return 0;
}
