# EE569 :Homework Assignment #1
# Date  : February 5, 2017
# Name  : Madhvi Kannan
# USC ID: 2159965290
# email : mkannan@usc.edu
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
unsigned char Imagedata_building[789][600][3];
	unsigned char building_image_cyan[789][600];
	unsigned char building_image_magenta[789][600];
	unsigned char building_image_yellow[789][600];
using namespace std;
int main()
{
    FILE *file;
	int BytesPerPixel=3;
	int i,j,temp;
	unsigned char Imagedata[512][384][BytesPerPixel];
	unsigned char output_image_cyan[512][384];
	unsigned char output_image_magenta[512][384];
	unsigned char output_image_yellow[512][384];

	//unsigned char temp_image1[512][384][BytesPerPixel];
	unsigned char Imagedata1[512][384][BytesPerPixel];
	if (!(file=fopen("parrot.raw","rb"))) {
		cout << "Cannot open file: " << "parrot.raw" <<endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), 512*384*BytesPerPixel, file);
    fclose(file);
    if (!(file=fopen("building.raw","rb"))) {
		cout << "Cannot open file: " << "building.raw" <<endl;
		exit(1);
	}
	fread(Imagedata_building, sizeof(unsigned char), 789*600*BytesPerPixel, file);
    fclose(file);
	for(int i=0;i<512;i++)
    {
        for(int j=0;j<384;j++)
        {
            output_image_cyan[i][j]=255-Imagedata[i][j][0];
            output_image_magenta[i][j]=255-Imagedata[i][j][1];
            output_image_yellow[i][j]=255-Imagedata[i][j][2];
            //cout<<(int)temp_image[i][j][0]<<endl;

        }
    }
    for(int m=0;m<789 ;m++)
    {
        for(int n=0;n<600;n++)
        {
            building_image_cyan[m][n]=255-Imagedata_building[m][n][0];
            building_image_magenta[m][n]=255-Imagedata_building[m][n][1];
            building_image_yellow[m][n]=255-Imagedata_building[m][n][2];
            //cout<<(int)temp_image[i][j][0]<<endl;

        }
    }
   if (!(file=fopen("parrot_cyan.raw","wb"))) {
		cout << "Cannot open file: " << "parrot_cyan.raw" << endl;
		exit(1);
	}

	fwrite(output_image_cyan, sizeof(unsigned char),   512*384, file);
	printf("File written\n");
	fclose(file);
	 if (!(file=fopen("parrot_magenta.raw","wb"))) {
		cout << "Cannot open file: " << "parrot_magenta.raw" << endl;
		exit(1);
	}

	fwrite(output_image_magenta, sizeof(unsigned char),   512*384, file);
	printf("File written\n");
	fclose(file);
	 if (!(file=fopen("parrot_yellow.raw","wb"))) {
		cout << "Cannot open file: " << "parrot_yellow.raw" << endl;
		exit(1);
	}

	fwrite(output_image_yellow, sizeof(unsigned char),   512*384, file);
	printf("File written\n");
	fclose(file);

   if (!(file=fopen("building_cyan.raw","wb"))) {
		cout << "Cannot open file: " << "building_cyan.raw" << endl;
		exit(1);
	}

	fwrite(building_image_cyan, sizeof(unsigned char),   789*600, file);
	printf("File written\n");
	fclose(file);
	 if (!(file=fopen("building_magenta.raw","wb"))) {
		cout << "Cannot open file: " << "building_magenta.raw" << endl;
		exit(1);
	}

	fwrite(building_image_magenta, sizeof(unsigned char),   789*600, file);
	printf("File written\n");
	fclose(file);
	 if (!(file=fopen("building_yellow.raw","wb"))) {
		cout << "Cannot open file: " << "building_yellow.raw" << endl;
		exit(1);
	}

	fwrite(building_image_yellow, sizeof(unsigned char),   789*600, file);
	printf("File written\n");
	fclose(file);
	return 0;
}


