#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#include<math.h>
#include<algorithm>
unsigned char field[648][972][3];
unsigned char trojans[197][350][3];
unsigned char new_field[648][972][3];
unsigned char field_inter[648][972][3];
unsigned char final_field[648][972][3];
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
    if (!(file1=fopen("field.raw","rb"))) {
		cout << "Cannot open file: " << "field.raw" <<endl;
		exit(1);
	}
	fread(field,sizeof(unsigned char), 972*648*BytesPerPixel, file1);
    fclose(file1);

    if (!(file1=fopen("tartans.raw","rb"))) {
		cout << "Cannot open file: " << "tartans.raw" <<endl;
		exit(1);
	}
	fread(trojans,sizeof(unsigned char), 350*146*BytesPerPixel, file1);
    fclose(file1);
    //------------Making all pixel intensities outside the main text white---------//
    for(int i=0;i<146;i++)
    {
        for(int j=0;j<350;j++)
        {
            if((int)trojans[i][j][0]>240&&(int)trojans[i][j][1]>240&&(int)trojans[i][j][2]>240)
            {
                trojans[i][j][0]=255;
                trojans[i][j][1]=255;
                trojans[i][j][2]=255;
            }
        }
    }
   double h[3][3]={0.1896,1.4668,-234.8454,-0.3882,0.1279,252.1600,0.0003,-0.0031,1.0};
   double x[972]={0.0};
   double y[648]={0.0};
   double x_new,y_new;
   //Copying the image of field to new_field
    for(int i=0;i<648;i++)
    {
        for(int j=0;j<972;j++)
        {
            for(int k=0;k<3;k++)
            {
                new_field[i][j][k]=field[i][j][k];
            }
        }
    }

    for(int i=0;i<648;i++)
    {
        for(int j=0;j<972;j++)
        {
            for(int k=0;k<3;k++)
            {
                 //converting to cartesian coordinates
             x_new=  j+0.5;
             y_new=648-i-0.5;
             if((x_new>=(((137.0/102.0)*(y_new-109.5))+393.5))&&y_new<=(((-6.0/186.0)*(x_new-530.5))+211.5)&&x_new<=(((44.0/132.0)*(y_new-205.5))+716.5)&&y_new>=(((-36.0/279.0)*(x_new-672.5))+73.5))
             {

                             //Getting into the chosen coordinates of the field image
                             double x_new1=((h[0][0]*x_new+h[0][1]*y_new+h[0][2])/(h[2][0]*x_new+h[2][1]*y_new+1.0));
                             double y_new1=((h[1][0]*x_new+h[1][1]*y_new+h[1][2])/(h[2][0]*x_new+h[2][1]*y_new+1.0));
                                //Converting back to image coordinates
                             double tro_j=x_new1-0.5;
                             double tro_i=146-y_new1-0.5;

                            // Converting original image cartesian coordinates to image coordinates
                             int y_field=x_new-0.5;
                             int x_field=648-y_new-0.5;

                             int row_pix=floor(tro_i);
                             int col_pix=floor(tro_j);

                            // cout<<row_pix<<" "<<col_pix<<endl;
                        float del_x=tro_i-row_pix; // find delta x
                        float del_y=tro_j-col_pix; //delta y
                        float weight1=(1-del_x)*(1-del_y); //compute the 4 weights
                        float weight2=del_y*(1-del_x);
                        float weight3=del_x*(1-del_y);
                        float weight4=del_x*del_y;
                        //----Perform bilinear interpolation------//



                new_field[x_field][y_field][k]= weight1*trojans[row_pix][col_pix][k]+weight2*trojans[row_pix][col_pix+1][k]+weight3*trojans[row_pix+1][col_pix][k]+weight4*trojans[row_pix+1][col_pix+1][k];




             }
            }
        }
    }
    if (!(file1=fopen("field.raw","rb"))) {
		cout << "Cannot open file: " << "field.raw" <<endl;
		exit(1);
	}
	fread(field_inter,sizeof(unsigned char), 972*648*BytesPerPixel, file1);
    fclose(file1);
    for(int i=0;i<648;i++)
    {
        for (int j=0;j<972;j++)
        {
           // for(int k=0;k<3;k++)
           // {
                if((int)new_field[i][j][0]<15&&(int)new_field[i][j][0]<15&&(int)new_field[i][j][0]<15)
                {
                    field_inter[i][j][0]=field[i][j][0];
                    field_inter[i][j][1]=field[i][j][1];
                    field_inter[i][j][2]=field[i][j][2];
                }
                else
                {
                    field_inter[i][j][0]=new_field[i][j][0];
                    field_inter[i][j][1]=new_field[i][j][1];
                    field_inter[i][j][2]=new_field[i][j][2];
                }
           // }
        }

    }


     if (!(file=fopen("overlay_tartans.raw","wb"))) {
		cout << "Cannot open file: " << "overlay.raw" << endl;
		exit(1);
	}

	fwrite(field_inter, sizeof(unsigned char),   648*972*BytesPerPixel, file);
	printf("File written\n");
	fclose(file);


    return 0;
}

