# EE569 :Homework Assignment #1
# Date  : February 5, 2017
# Name  : Madhvi Kannan
# USC ID: 2159965290
# email : mkannan@usc.edu
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include<vector>
#include<iostream>
unsigned char Imagedata_beach[808][1914][3];
	unsigned char temp_image_beach[808][1914][3];
	unsigned char Imagedata1_beach[808][1914][3];
    unsigned char Imagedata[300][300][3];
    unsigned char Imagedata_dog[300][300][3];
using namespace std;
//Function for mirroring the dog
void mirror()
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

}

int main()
{
    mirror();

	int i,j,temp;
	int BytesPerPixel=3;
	unsigned char Imagedata_dog[300][300][BytesPerPixel];
    unsigned char Imagedata1_dog[300][300][BytesPerPixel];
    FILE *file,*file2,*file1,*file3,*file4,*file5,*file6;
	if (!(file=fopen("dog_mirror.raw","rb"))) {
		cout << "Cannot open file: " << "dog_mirror.raw" <<endl;
		exit(1);
	}
	fread(Imagedata_dog, sizeof(unsigned char), 300*300*BytesPerPixel, file);
	fclose(file);
cout<<(int)Imagedata_dog[0][0][2]<<endl;
//Removing blue background and replacing it with white backdrop
    for(i=0;i<300;i++)
        {
        for(j=0;j<300;j++)
            {
        if((((int)Imagedata_dog[i][j][2]>200)||((int)Imagedata_dog[i][j]<255))) //Check for the pixels with blue intensities in the dog
        {
            Imagedata1_dog[i][j][0]=255; //replace all intensities of with white background
            Imagedata1_dog[i][j][1]=255;
            Imagedata1_dog[i][j][2]=255;
        }
        else //else, preserve intensities of image
        {
            Imagedata1_dog[i][j][0]=Imagedata_dog[i][j][0];
            Imagedata1_dog[i][j][1]=Imagedata_dog[i][j][1];
            Imagedata1_dog[i][j][2]=Imagedata_dog[i][j][2];
        }
                }
            }

	if (!(file1=fopen("dog1.raw","wb"))) {
		cout << "Cannot open file: " << "dog1.raw" << endl;
		exit(1);
	}
	fwrite(Imagedata1_dog, sizeof(unsigned char),   300*300*BytesPerPixel, file1);
	fclose(file1);
 if (!(file2=fopen("beach.raw","rb"))) {
		cout << "Cannot open file: " << "beach.raw" << endl;
		exit(1);
	}
	fread(Imagedata_beach, sizeof(unsigned char), 808*1914*BytesPerPixel, file2);
	fclose(file2);
	if (!(file1=fopen("dog1.raw","rb"))) {
		cout << "Cannot open file: " << "dog1.raw" << endl;
		exit(1);
	}
    fread(Imagedata1_dog, sizeof(unsigned char), 300*300*BytesPerPixel, file1);
    fclose(file1);
int start_width=1100; //Set width and height of beach image
int start_height=400;
    for(int m=0;m<300;m++)
        {
        for(int n=0;n<300;n++)
            {
                Imagedata_beach[start_height][start_width][0]=Imagedata1_dog[m][n][0]; //Replace dog image at the specified location of beach (1100x400)
                 Imagedata_beach[start_height][start_width][1]=Imagedata1_dog[m][n][1];
                 Imagedata_beach[start_height][start_width][2]=Imagedata1_dog[m][n][2];
                start_width++; //Increment column
                        }
                       start_width=1100; //Reset column to 1100
            start_height++; //Increment row

                    }
                    start_width=1100;

                    if (!(file3=fopen("temp_beach.raw","wb"))) {
		cout << "Cannot open file: " << "temp_beach.raw" << endl;
		exit(1);
	}
	fwrite(Imagedata_beach, sizeof(unsigned char),   808*1914*BytesPerPixel, file3);
	fclose(file3);
	if (!(file4=fopen("beach.raw","rb"))) {
		cout << "Cannot open file: " << "beach.raw" << endl;
		exit(1);
	}
	fread(temp_image_beach, sizeof(unsigned char), 808*1914*BytesPerPixel, file4);
	fclose(file4);
	if (!(file5=fopen("temp_beach.raw","rb"))) {
		cout << "Cannot open file: " << "temp_beach.raw" << endl;
		exit(1);
	}
	fread(Imagedata_beach, sizeof(unsigned char), 808*1914*BytesPerPixel, file5);
	fclose(file5);
	//replacing white backdrop of dog image with the backdrop of the beach image
	for(int k=0;k<808;k++)
    {
        for(int l=0;l<1914;l++)
        {
            //check if image backdrop in beach is white(255)
            if((int)Imagedata_beach[k][l][0]==255||(int)Imagedata_beach[k][l][1]==255||(int)Imagedata_beach[k][l][2]==255)
            {
                Imagedata_beach[k][l][0]=temp_image_beach[k][l][0];  //replace with backdrop of original beach image
                Imagedata_beach[k][l][1]=temp_image_beach[k][l][1];
                Imagedata_beach[k][l][2]=temp_image_beach[k][l][2];
            }
        }
    }
     if (!(file6=fopen("final_beach.raw","wb"))) {
		cout << "Cannot open file: " << "final_beach.raw" << endl;
		exit(1);
	}
	fwrite(Imagedata_beach, sizeof(unsigned char),   808*1914*BytesPerPixel, file6);
	fclose(file6);

	return 0;
}
