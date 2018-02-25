# EE569 :Homework Assignment #1
# Date  : February 5, 2017
# Name  : Madhvi Kannan
# USC ID: 2159965290
# email : mkannan@usc.edu
#include <iostream>
#include<stdlib.h>
#include<math.h>
#include<stdio.h>
unsigned char Imagedata[300][300][3];
unsigned char Imagedata_dog[300][300][3];
using namespace std;
int main()
{
    FILE *file, *file6;
    int width=300;
    int height=300;


	// Read image (filename specified by first argument) into image data matrix
	int BytesPerPixel=3;
	if (!(file=fopen("dog.raw","rb"))) {
		cout << "Cannot open file: " << "dog.raw" <<endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), 300*300*BytesPerPixel, file);
	fclose(file);
	for(int i=0;i<height;i++)
    {
       int temp = width;
        for(int j=0;j<width;j++)
        {

            //unsigned int temp=Imagedata[i][j][BytesPerPixel];
            Imagedata_dog[i][j][0]=Imagedata[i][temp][0];
            Imagedata_dog[i][j][1]=Imagedata[i][temp][1];
            Imagedata_dog[i][j][2]=Imagedata[i][temp][2];
            temp --;
            //Imagedata[i][j][BytesPerPixel]=temp;
            //cout<<"width"<<width<<endl;
        }
    }
      if (!(file6=fopen("dog_mirror.raw","wb"))) {
		cout << "Cannot open file: " << "dog_mirror.raw" << endl;
		exit(1);
	}
	fwrite(Imagedata_dog, sizeof(unsigned char),   300*300*BytesPerPixel, file6);
	fclose(file6);
	return 0;
}
