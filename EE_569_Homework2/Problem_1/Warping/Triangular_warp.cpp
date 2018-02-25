#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#include<math.h>
#include<algorithm>
unsigned char cup1[500][500][3];
unsigned char cup_output[500][500][3];
unsigned char pepper_denoised[512][512][3];
unsigned char pepper_denoised_median[512][512][3];
unsigned char pepper_denoised_gauss[512][512][3];
unsigned char pepper_free[512][512][3];
using namespace std;
int main()
{
     FILE *file1, *file2, *file3,*file4,*file5,*file6,*file;
    int BytesPerPixel=3;
    int i,j;
    if (!(file1=fopen("cup1.raw","rb"))) {
		cout << "Cannot open file: " << "cup1.raw" <<endl;
		exit(1);
	}
	fread(cup1,sizeof(unsigned char), 500*500*BytesPerPixel, file1);
    fclose(file1);
    double mat1[3][3]={1.0,0.9920,-247.0080,0.0,1.9920,-249.0080,0.0,0.0,1.0};
    double mat2[3][3]={1.0,-0.9920,247.0080,0.0,2.0,-249.0,0.0,0.0,1.0};
    double mat3[3][3]={1.9920,0.0,-247.0080,-1.0,1.0,249.0,0.0,0.0,1.0};
    double mat4[3][3]={2.0,0.0,-249.0,1.0,1.0,-249.0,0.0,0.0,1.0};
    double mat5[3][3]={1.0,1.0,-249.0,0.0,2.0,-249.0,0.0,0.0,1.0};
    double mat6[3][3]={1.0,-1.0,249.0,0.0,1.9920,-247.0080,0.0,0.0,1.0};
    double mat7[3][3]={2.0,0.0,-249.0,-0.9920,1.0,247.0080,0.0,0.0,1.0};
    double mat8[3][3]={1.9920,0.0,-247.0080,0.9920,1.0,-247.0080,0.0,0.0,1.0};
    double input_1[125][125];
    double output_1[125][125];
//TRIANGLE 8
    for(int i=0;i<250;i++) //rows of new matrix
    {
        for(int j=0;j<250;j++)
        {
            if(i>=j)
            {
                if(i<=249)
                {
                    if(i>=-j+249)
                    {
                        double row1=mat8[0][0]*i+mat8[0][1]*j+mat8[0][2];
                        double col1=mat8[1][0]*i+mat8[1][1]*j+mat8[1][2];
                        int row_pix= int(floor(row1)); //floor the value of x coordinates to find the previous two pixel coordinates
                        int col_pix=int(floor(col1)); //floor the value of y coordinate to previous pixel coordinate
                        float del_x=row1-row_pix; // find delta x
                        float del_y=col1-col_pix; //delta y
                        float weight1=(1-del_x)*(1-del_y); //compute the 4 weights
                        float weight2=del_y*(1-del_x);
                        float weight3=del_x*(1-del_y);
                        float weight4=del_x*del_y;
                        for(int k=0;k<3;k++)
                {
                cup_output[i][j][k]= weight1*cup1[row_pix][col_pix][k]+weight2*cup1[row_pix][col_pix+1][k]+weight3*cup1[row_pix+1][col_pix][k]+weight4*cup1[row_pix+1][col_pix+1][k];

                }

                    }
                }
            }
    }
    }
    //TRIANGLE 1
    for(int i=0;i<250;i++) //rows of new matrix
    {
        for(int j=0;j<250;j++)
        {
            if(j>=i)
            {
                if(j<=249)
                {
                    if(j>=-i+249)
                    {
                        double row1=mat1[0][0]*i+mat1[0][1]*j+mat1[0][2];
                        double col1=mat1[1][0]*i+mat1[1][1]*j+mat1[1][2];
                        int row_pix= int(floor(row1)); //floor the value of x coordinates to find the previous two pixel coordinates
                        int col_pix=int(floor(col1)); //floor the value of y coordinate to previous pixel coordinate
                        float del_x=row1-row_pix; // find delta x
                        float del_y=col1-col_pix; //delta y
                        float weight1=(1-del_x)*(1-del_y); //compute the 4 weights
                        float weight2=del_y*(1-del_x);
                        float weight3=del_x*(1-del_y);
                        float weight4=del_x*del_y;
                        for(int k=0;k<3;k++)
                {
                cup_output[i][j][k]= weight1*cup1[row_pix][col_pix][k]+weight2*cup1[row_pix][col_pix+1][k]+weight3*cup1[row_pix+1][col_pix][k]+weight4*cup1[row_pix+1][col_pix+1][k];

                }

                    }
                }
            }
    }
    }
    //TRIANGLE 4
     for(int i=250;i<500;i++) //rows of new matrix
    {
        for(int j=250;j<500;j++)
        {
            if(i<=-j+748)
            {
                if(i>=249)
                {
                    if(i<=j)
                    {
                        double row1=mat4[0][0]*i+mat4[0][1]*j+mat4[0][2];
                        double col1=mat4[1][0]*i+mat4[1][1]*j+mat4[1][2];
                        int row_pix= int(floor(row1)); //floor the value of x coordinates to find the previous two pixel coordinates
                        int col_pix=int(floor(col1)); //floor the value of y coordinate to previous pixel coordinate
                        float del_x=row1-row_pix; // find delta x
                        float del_y=col1-col_pix; //delta y
                        float weight1=(1-del_x)*(1-del_y); //compute the 4 weights
                        float weight2=del_y*(1-del_x);
                        float weight3=del_x*(1-del_y);
                        float weight4=del_x*del_y;
                        for(int k=0;k<3;k++)
                {
                cup_output[i][j][k]= weight1*cup1[row_pix][col_pix][k]+weight2*cup1[row_pix][col_pix+1][k]+weight3*cup1[row_pix+1][col_pix][k]+weight4*cup1[row_pix+1][col_pix+1][k];

                }

                    }
                }
            }
    }
    }
    //TRIANGLE 5
     for(int i=250;i<500;i++) //rows of new matrix
    {
        for(int j=250;j<500;j++)
        {
            if(i<=-j+748)
            {
                if(j>=249)
                {
                    if(i>=j)
                    {
                        double row1=mat5[0][0]*i+mat5[0][1]*j+mat5[0][2];
                        double col1=mat5[1][0]*i+mat5[1][1]*j+mat5[1][2];
                        int row_pix= int(floor(row1)); //floor the value of x coordinates to find the previous two pixel coordinates
                        int col_pix=int(floor(col1)); //floor the value of y coordinate to previous pixel coordinate
                        float del_x=row1-row_pix; // find delta x
                        float del_y=col1-col_pix; //delta y
                        float weight1=(1-del_x)*(1-del_y); //compute the 4 weights
                        float weight2=del_y*(1-del_x);
                        float weight3=del_x*(1-del_y);
                        float weight4=del_x*del_y;
                        for(int k=0;k<3;k++)
                {
                cup_output[i][j][k]= weight1*cup1[row_pix][col_pix][k]+weight2*cup1[row_pix][col_pix+1][k]+weight3*cup1[row_pix+1][col_pix][k]+weight4*cup1[row_pix+1][col_pix+1][k];

                }

                    }
                }
            }
    }
    }
   /* //TRIANGLE 7
     for(int i=250;i<500;i++) //rows of new matrix
    {
        for(int j=0;j<250;j++)
        {
            if(i<=-j+498)
            {
                    if(i>=j-249)
                    {
                        //cout<<"yes"<<endl;
                        double row1=mat7[0][0]*i+mat7[0][1]*j+mat7[0][2];
                        double col1=mat7[1][0]*i+mat7[1][1]*j+mat7[1][2];
                        int row_pix= int(floor(row1)); //floor the value of x coordinates to find the previous two pixel coordinates
                        int col_pix=int(floor(col1)); //floor the value of y coordinate to previous pixel coordinate
                        float del_x=row1-row_pix; // find delta x
                        float del_y=col1-col_pix; //delta y
                        float weight1=(1-del_x)*(1-del_y); //compute the 4 weights
                        float weight2=del_y*(1-del_x);
                        float weight3=del_x*(1-del_y);
                        float weight4=del_x*del_y;
                        for(int k=0;k<3;k++)
                {
                cup_output[i][j][k]= weight1*cup1[row_pix][col_pix][k]+weight2*cup1[row_pix][col_pix+1][k]+weight3*cup1[row_pix+1][col_pix][k]+weight4*cup1[row_pix+1][col_pix+1][k];

                }

                    }
            }
    }
    }*/
    //TRIANGLE 3
     for(int i=0;i<250;i++) //rows of new matrix
    {
        for(int j=250;j<500;j++)
        {
            if(j<=i+249)
            {
                    if(j>=-i+498)
                    {

                        double row1=mat3[0][0]*i+mat3[0][1]*j+mat3[0][2];
                        double col1=mat3[1][0]*i+mat3[1][1]*j+mat3[1][2];
                        int row_pix= int(floor(row1)); //floor the value of x coordinates to find the previous two pixel coordinates
                        int col_pix=int(floor(col1)); //floor the value of y coordinate to previous pixel coordinate
                        float del_x=row1-row_pix; // find delta x
                        float del_y=col1-col_pix; //delta y
                        float weight1=(1-del_x)*(1-del_y); //compute the 4 weights
                        float weight2=del_y*(1-del_x);
                        float weight3=del_x*(1-del_y);
                        float weight4=del_x*del_y;
                        for(int k=0;k<3;k++)
                {
                cup_output[i][j][k]= weight1*cup1[row_pix][col_pix][k]+weight2*cup1[row_pix][col_pix+1][k]+weight3*cup1[row_pix+1][col_pix][k]+weight4*cup1[row_pix+1][col_pix+1][k];

                }

                    }
            }
    }
    }
     //TRIANGLE 2
     for(int i=0;i<250;i++) //rows of new matrix
    {
        for(int j=250;j<500;j++)
        {
            if(j<=i+249)
            {
                    if(j<=-i+498)
                    {

                        double row1=mat2[0][0]*i+mat2[0][1]*j+mat2[0][2];
                        double col1=mat2[1][0]*i+mat2[1][1]*j+mat2[1][2];
                        int row_pix= int(floor(row1)); //floor the value of x coordinates to find the previous two pixel coordinates
                        int col_pix=int(floor(col1)); //floor the value of y coordinate to previous pixel coordinate
                        float del_x=row1-row_pix; // find delta x
                        float del_y=col1-col_pix; //delta y
                        float weight1=(1-del_x)*(1-del_y); //compute the 4 weights
                        float weight2=del_y*(1-del_x);
                        float weight3=del_x*(1-del_y);
                        float weight4=del_x*del_y;
                        for(int k=0;k<3;k++)
                {
                cup_output[i][j][k]= weight1*cup1[row_pix][col_pix][k]+weight2*cup1[row_pix][col_pix+1][k]+weight3*cup1[row_pix+1][col_pix][k]+weight4*cup1[row_pix+1][col_pix+1][k];

                }

                    }
            }
    }
    }
     //TRIANGLE 7
     for(int i=250;i<500;i++) //rows of new matrix
    {
        for(int j=0;j<250;j++)
        {
            if(j>=i-249)
            {
                    if(j<=-i+498)
                    {

                        double row1=mat7[0][0]*i+mat7[0][1]*j+mat7[0][2];
                        double col1=mat7[1][0]*i+mat7[1][1]*j+mat7[1][2];
                        int row_pix= int(floor(row1)); //floor the value of x coordinates to find the previous two pixel coordinates
                        int col_pix=int(floor(col1)); //floor the value of y coordinate to previous pixel coordinate
                        float del_x=row1-row_pix; // find delta x
                        float del_y=col1-col_pix; //delta y
                        float weight1=(1-del_x)*(1-del_y); //compute the 4 weights
                        float weight2=del_y*(1-del_x);
                        float weight3=del_x*(1-del_y);
                        float weight4=del_x*del_y;
                        for(int k=0;k<3;k++)
                {
                cup_output[i][j][k]= weight1*cup1[row_pix][col_pix][k]+weight2*cup1[row_pix][col_pix+1][k]+weight3*cup1[row_pix+1][col_pix][k]+weight4*cup1[row_pix+1][col_pix+1][k];

                }

                    }
            }
    }
    }
     //TRIANGLE 6
     for(int i=250;i<500;i++) //rows of new matrix
    {
        for(int j=0;j<250;j++)
        {
            if(j>=i-249)
            {
                    if(j>=-i+498)
                    {

                        double row1=mat6[0][0]*i+mat6[0][1]*j+mat6[0][2];
                        double col1=mat6[1][0]*i+mat6[1][1]*j+mat6[1][2];
                        int row_pix= int(floor(row1)); //floor the value of x coordinates to find the previous two pixel coordinates
                        int col_pix=int(floor(col1)); //floor the value of y coordinate to previous pixel coordinate
                        float del_x=row1-row_pix; // find delta x
                        float del_y=col1-col_pix; //delta y
                        float weight1=(1-del_x)*(1-del_y); //compute the 4 weights
                        float weight2=del_y*(1-del_x);
                        float weight3=del_x*(1-del_y);
                        float weight4=del_x*del_y;
                        for(int k=0;k<3;k++)
                {
                cup_output[i][j][k]= weight1*cup1[row_pix][col_pix][k]+weight2*cup1[row_pix][col_pix+1][k]+weight3*cup1[row_pix+1][col_pix][k]+weight4*cup1[row_pix+1][col_pix+1][k];

                }

                    }
            }
    }
    }

    if (!(file=fopen("cup_new.raw","wb"))) {
		cout << "Cannot open file: " << "cup_new.raw" << endl;
		exit(1);
	}

	fwrite(cup_output, sizeof(unsigned char),   500*500*BytesPerPixel, file);
	printf("File written\n");
	fclose(file);

    return 0;
}
