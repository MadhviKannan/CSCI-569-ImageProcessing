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
    FILE *file;
	int BytesPerPixel=3;
	int i,j,temp;
	int old_width=300;
	int old_height=300;
	int new_width=400;
	int new_height=400;
	unsigned char Imagedata[old_width][old_height][BytesPerPixel];
	unsigned char Imagedata1[new_width][new_height][BytesPerPixel];
	if (!(file=fopen("dog_mirror.raw","rb"))) {
		cout << "Cannot open file: " << "dog_mirror.raw" <<endl;
		exit(1);}
		fread(Imagedata, sizeof(unsigned char), 300*300*BytesPerPixel, file);
    fclose(file);
		float row_rat=(float(old_width)/new_width); //ratio of old width/new width=old row coordinate
		cout<<row_rat<<endl;
		float col_rat=(float(old_height)/new_height); //ratio of old height/new height=old column coordinate
		for(int i=0;i<new_width;i++)
        {
            float old_row=row_rat*i; //x- pixel coordinate of original image
            for(int j=0;j<new_height;j++)
            {

                float old_col=col_rat*j; //y-pixel coordinate of original image
                int row_pix= int(floor(old_row)); //floor the value of x coordinates to find the previous two pixel coordinates
                int col_pix=int(floor(old_col)); //floor the value of y coordinate to previous pixel coordinate
                float del_x=old_row-row_pix; // find delta x
                float del_y=old_col-col_pix; //delta y
                float weight1=(1-del_x)*(1-del_y); //compute the 4 weights
                float weight2=del_y*(1-del_x);
                float weight3=del_x*(1-del_y);
                float weight4=del_x*del_y;
                for(int k=0;k<3;k++)
                {
                Imagedata1[i][j][k]= weight1*Imagedata[row_pix][col_pix][k]+weight2*Imagedata[row_pix][col_pix+1][k]+weight3*Imagedata[row_pix+1][col_pix][k]+weight4*Imagedata[row_pix+1][col_pix+1][k];

                }
            }
        }
        if (!(file=fopen("dog1.raw","wb"))) {
		cout << "Cannot open file: " << "dog1.raw" << endl;
		exit(1);
	}

	fwrite(Imagedata1, sizeof(unsigned char),   400*400*BytesPerPixel, file);
	printf("File written\n");
	fclose(file);

        return 0;
}
