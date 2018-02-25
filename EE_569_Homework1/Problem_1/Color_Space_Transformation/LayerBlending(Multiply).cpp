# EE569 :Homework Assignment #1
# Date  : February 5, 2017
# Name  : Madhvi Kannan
# USC ID: 2159965290
# email : mkannan@usc.edu
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
unsigned char top_layer[900][890][3];
unsigned char bottom_layer[900][890][3];
double inter_top[900][890][3];
double inter_bottom[900][890][3];
unsigned char product_both[900][890][3];
double final_output[900][890][3];
unsigned char final1[900][890][3];
using namespace std;
int main()
{
    FILE *file,*file1,*file2,*file3;
	int BytesPerPixel=3;
	int i,j,temp;
	if (!(file=fopen("top_layer.raw","rb"))) {
		cout << "Cannot open file: " << "top_layer.raw" <<endl;
		exit(1);
	}
	fread(top_layer, sizeof(unsigned char), 890*900*BytesPerPixel, file);
    fclose(file);
    if (!(file1=fopen("bottom_layer.raw","rb"))) {
		cout << "Cannot open file: " << "bottom_layer.raw" <<endl;
		exit(1);
	}
	fread(bottom_layer, sizeof(unsigned char), 890*900*BytesPerPixel, file1);
    fclose(file1);
    for(int i=0;i<900;i++)
    {
        for(int j=0;j<890;j++)
        {

        for(int x=0;x<3;x++)
        {
            inter_top[i][j][x]=((int)top_layer[i][j][x]/255.0);
            inter_bottom[i][j][x]=((int)bottom_layer[i][j][x]/255.0);
            product_both[i][j][x]= (int)(255.0*(inter_top[i][j][x]*inter_bottom[i][j][x]));
           // final_output[i][j][x]=1-product_both[i][j][x];

            //final1[i][j][x]=255*((int)final_output[i][j][x]);


        }
        }
    }
 //cout<<(int)final1[400][890][1]<<endl;

    if (!(file2=fopen("final_blend.raw","wb"))) {
		cout << "Cannot open file: " << "final_blend.raw" << endl;
		exit(1);
	}

	fwrite(product_both, sizeof(unsigned char),   890*900*BytesPerPixel, file2);
	printf("File written\n");
	fclose(file2);

    return 0;
}
