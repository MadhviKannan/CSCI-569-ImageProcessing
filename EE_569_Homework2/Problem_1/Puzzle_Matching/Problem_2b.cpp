#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#include<math.h>
#include<algorithm>
unsigned char hillary[512][512][3];
unsigned char piece[500][500][3];
unsigned char piece_inter[500][500][3];
unsigned char piece_inter1[500][500][3];
unsigned char piece_inter3[500][500][3];
unsigned char piece_inter2[500][500][3];
unsigned char piece_average[500][500][3];
unsigned char piece_final[512][512][3];
unsigned char piece_final1[512][512][3];
unsigned char piece_final4[512][512][3];
unsigned char trump[512][512][3];
unsigned char mean[3][3]={1};
using namespace std;
int main()
{
FILE *file1, *file2, *file3,*file4,*file5,*file6,*file;
    int BytesPerPixel=3;
    int i,j;
    if (!(file1=fopen("Hillary.raw","rb"))) {
		cout << "Cannot open file: " << "Hillary.raw" <<endl;
		exit(1);
	}
	fread(hillary,sizeof(unsigned char), 512*512*BytesPerPixel, file1);
    fclose(file1);
    if (!(file1=fopen("piece.raw","rb"))) {
		cout << "Cannot open file: " << "piece.raw" <<endl;
		exit(1);
	}
	fread(piece,sizeof(unsigned char), 500*500*BytesPerPixel, file1);
    fclose(file1);
     if (!(file1=fopen("Trump.raw","rb"))) {
		cout << "Cannot open file: " << "Trump.raw" <<endl;
		exit(1);
	}
	fread(trump,sizeof(unsigned char), 512*512*BytesPerPixel, file1);
    fclose(file1);
    //----------Finding corner coordinates of hillary in puzzle piece---------//
    int h_x1,h_y1,h_x2,h_y2,h_x3,h_y3,h_x4,h_y4;
    for(int i=0;i<250;i++)
    {
        for(int j=0;j<250;j++)
        {
            if(piece[i][j][0]!=255&&piece[i][j][1]!=255&&piece[i][j][2]!=255)
            {
                h_x1=i;
                h_y1=j;
                goto label1;
            }
        }
    }
    label1:
     for(int i=250;i>0;i--)
     {
         for(int j=250;j>0;j--)
         {
            if(piece[i][j][0]!=255&&piece[i][j][1]!=255&&piece[i][j][2]!=255)
            {
                h_x3=i;
                h_y3=j;
                goto label2;
            }
         }

     }
      label2:
     for(int j=0;j<250;j++)
     {
         for(int i=0;i<250;i++)
         {
             if(piece[i][j][0]!=255&&piece[i][j][1]!=255&&piece[i][j][2]!=255)
            {
                h_x4=i;
                h_y4=j;
                goto label3;
            }
         }
     }
     label3:
      for(int j=250;j>0;j--)
     {
         for(int i=0;i<250;i++)
         {
             if(piece[i][j][0]!=255&&piece[i][j][1]!=255&&piece[i][j][2]!=255)
            {
                h_x2=i;
                h_y2=j;
                goto label4;
            }
         }
     }
     label4:

        //-----------------Coordinates for Hillary image----//
        int hill_x1,hill_y1,hill_x2,hill_y2,hill_x3,hill_y3,hill_x4,hill_y4;
        for(int i=0;i<512;i++)
        {
            for(int j=0;j<512;j++)
            {
                if(hillary[i][j][0]==255&&hillary[i][j][1]==255&&hillary[i][j][2]==255)
                {
                    hill_x1=i;
                    hill_y1=j;
                    goto label5;
                }
            }
        }
        label5:
            hill_x2=hill_x1;
            hill_y2=hill_y1+99;
            hill_x4=hill_x1+99;
            hill_y4=hill_y1;
            hill_x3=hill_x4;
            hill_y3=hill_y4+99;

//--------------------------Coordinates for the trump in puzzle piece----------//
    int t_x1,t_y1,t_x2,t_y2,t_x3,t_y3,t_x4,t_y4;
    for(int j=250;j<499;j++)
    {
        for(int i=250;i<499;i++)
        {
             if(piece[i][j][0]!=255&&piece[i][j][1]!=255&&piece[i][j][2]!=255)
            {
                t_x1=i;
                t_y1=j;
                goto label7;
            }
        }
    }
label7:
    for(int i=250;i<499;i++)
    {
        for(int j=499;j>250;j--)
        {
             if(piece[i][j][0]!=255&&piece[i][j][1]!=255&&piece[i][j][2]!=255)
            {
                t_x2=i;
                t_y2=j;
                goto label6;
            }
        }
    }
label6:
        for(int i=499;i>250;i--)
    {
        for(int j=250;j<499;j++)
        {
             if(piece[i][j][0]!=255&&piece[i][j][1]!=255&&piece[i][j][2]!=255)
            {
                t_x4=i;
                t_y4=j;
                goto label8;
            }
        }
    }
label8:

     for(int j=499;i>250;j--)
    {
        for(int i=499;i>250;i--)
        {
             if(piece[i][j][0]!=255&&piece[i][j][1]!=255&&piece[i][j][2]!=255)
            {
                t_x3=i;
                t_y3=j;
                goto label9;
            }
        }
    }
label9:
//---------------------Coordinates for Trump image-----------//

int trump_x1,trump_y1,trump_x2,trump_y2,trump_x3,trump_y3,trump_x4,trump_y4;
        for(int i=0;i<512;i++)
        {
            for(int j=0;j<512;j++)
            {
                if(trump[i][j][0]==255&&trump[i][j][1]==255&&trump[i][j][2]==255)
                {
                    trump_x1=i;
                    trump_y1=j;
                    goto label10;
                }
            }
        }
        label10:
            trump_x2=trump_x1;
            trump_y2=trump_y1+99;
            trump_x4=trump_x1+99;
            trump_y4=trump_y1;
            trump_x3=trump_x4;
            trump_y3=trump_y4+99;
//--------------------Translating, Rotating and Scaling Hillary puzzle piece----//
int i_trans,j_trans;
int i_new,j_new;
float i_rot,j_rot;
float i_scale,j_scale;
float theta;
int i_final,j_final;
 for(int i=0;i<250;i++)
    {
        for(int j=0;j<250;j++)
        {
            if(piece[i][j][0]!=255&&piece[i][j][1]!=255&&piece[i][j][2]!=255)
            {
                i_new=i;
                j_new=j;
                i_trans=i_new-h_x1; //Translating to origin
                j_trans=j_new-h_y1;
                i_scale=i_trans*(100.0/150.0); //Scaling down the image
                j_scale=j_trans*(100.0/150.0);
                theta=15.33*(3.14/180);
                i_rot=cos(theta)*i_scale-sin(theta)*j_scale; //rotating the image by an angle of 15.3 degrees
                j_rot=sin(theta)*i_scale+cos(theta)*j_scale;
                i_final=(int)i_rot+hill_x1; //translating back to the coordinates of the hillary image
                j_final=(int)j_rot+hill_y1;
                piece_inter[(int)i_final][(int)j_final][0]=piece[i_new][j_new][0];
                piece_inter[(int)i_final][(int)j_final][1]=piece[i_new][j_new][1];
                piece_inter[(int)i_final][(int)j_final][2]=piece[i_new][j_new][2];
            }
        }
    }
    //---------Copying transformed image to main hillary image-----//

for(int i=0;i<512;i++)
{
    for(int j=0;j<512;j++)
    {
        for(int k=0;k<3;k++)
        {
            if(hillary[i][j][k]==255)
            {
                piece_final[i][j][k]=piece_inter[i][j][k];

            }
            else
            {
                piece_final[i][j][k]=hillary[i][j][k];
            }
            }
    }
}
//------Further Processing of final image to remove white background----//
for(int i=200;i<243;i++)
{
    for(int j=160;j<260;j++)
    {

            if((int)piece_final[i][j][0]>170&&(int)piece_final[i][j][1]>170&&(int)piece_final[i][j][2]>170)
            {
                piece_final[i][j][0]=piece_final[i-3][j][0];
                piece_final[i][j][1]=piece_final[i-3][j][1];
                piece_final[i][j][2]=piece_final[i-3][j][2];
            }

    }
}
//----------------Translating Rotating and Scaling for Trump-------//
int i_trans1,j_trans1,i_new1,j_new1;
float i_rot1,j_rot1,i_rot2,j_rot2;
float theta2;
float theta3;
float row_rat=60.0/100.0;
float col_rat=60.0/100.0;
for(int j=250;j<499;j++)
{
    for(int i=250;i<499;i++)
    {
        if(piece[i][j][0]!=255&&piece[i][j][1]!=255&&piece[i][j][2]!=255)
        {
            i_new1=i;
            j_new1=j;
            i_trans1=i_new1-t_x1; //reason for not going to the (0,0) location during translation is because of difference
            j_trans1=j_new1-t_x2;
            float scale_i=i_trans1*(60.0/75.23);
            float scale_j=j_trans1*(60.0/75.23);
            theta2=4.83*(3.14/180.0);
            float theta3=360.0*(3.14/180.0);
            i_rot1=cos(theta3-theta2)*scale_i-sin(theta3-theta2)*scale_j; //Rotation by an angle of -4.83 degrees
            j_rot1=sin(theta3-theta2)*scale_i+cos(theta3-theta2)*scale_j;
            float theta4=90.0*(3.14/180.0);
            float i_rot2=cos(theta3-theta4)*i_rot1-sin(theta3-theta4)*j_rot1; //Rotation by an angle of -4.83 degrees
            float j_rot2=sin(theta3-theta4)*i_rot1+cos(theta3-theta4)*j_rot1;
            float i_trans2=i_rot2+t_x1-80;
            float j_trans2=j_rot2+t_x2-50;
           // float scale_i1=i_trans2*(75.23/60.0);
            //float scale_j1=j_trans2*(75.23/60.0);
           piece_inter1[(int)i_trans2][(int)j_trans2][0]=piece[i_new1][j_new1][0];
            piece_inter1[(int)i_trans2][(int)j_trans2][1]=piece[i_new1][j_new1][1];
            piece_inter1[(int)i_trans2][(int)j_trans2][2]=piece[i_new1][j_new1][2];
        }

    }
}
for(int i=0;i<500;i++)
{

    for(int j=0;j<500;j++)
    {
         float old_row=row_rat*i;
            float old_col=col_rat*j;
            int row_pix= (int)old_row;
            int col_pix=(int)old_col;
            float del_x=old_row-row_pix; // find delta x
            float del_y=old_col-col_pix; //delta y

            float weight1=(1-del_x)*(1-del_y); //compute the 4 weights
            float weight2=del_y*(1-del_x);
            float weight3=del_x*(1-del_y);
            float weight4=del_x*del_y;

           piece_inter2[i][j][0]= weight1*piece_inter1[row_pix][col_pix][0]+weight2*piece_inter1[row_pix][col_pix+1][0]+weight3*piece_inter1[row_pix+1][col_pix][0]+weight4*piece_inter1[row_pix+1][col_pix+1][0];
           piece_inter2[i][j][1]= weight1*piece_inter1[row_pix][col_pix][1]+weight2*piece_inter1[row_pix][col_pix+1][1]+weight3*piece_inter1[row_pix+1][col_pix][1]+weight4*piece_inter1[row_pix+1][col_pix+1][1];
           piece_inter2[i][j][2]= weight1*piece_inter1[row_pix][col_pix][2]+weight2*piece_inter1[row_pix][col_pix+1][2]+weight3*piece_inter1[row_pix+1][col_pix][2]+weight4*piece_inter1[row_pix+1][col_pix+1][2];

    }
}
for(int i=375;i<475;i++)
{
    for(int j=298;j<398;j++)
    {
        for(int k=0;k<3;k++)
        {
            int i_trans=i-140;
            int j_trans=j-135;
            piece_inter3[i_trans][j_trans][k]=piece_inter2[i][j][k];
        }
    }
}
//------Copying into trump image----//

for(int i=0;i<512;i++)
{
    for(int j=0;j<512;j++)
    {
        for(int k=0;k<3;k++)
        {
            if(trump[i][j][k]==255)
            {
                piece_final1[i][j][k]=piece_inter3[i][j][k];

            }
            else
            {
                piece_final1[i][j][k]=trump[i][j][k];
            }
            }
    }
}

//---------------Averaging out the black pixels in the trump image---------//
for(int i=321;i<336;i++)
{
    for(int j=161;j<262;j++)
    {
        if((int)piece_final1[i][j][0]>210||(int)piece_final1[i][j][0]<15||(int)piece_final1[i][j][1]>210||(int)piece_final1[i][j][1]<15||(int)piece_final1[i][j][2]>210||(int)piece_final1[i][j][2]<15)
        {
            piece_final1[i][j][0]=(piece_final1[i-1][j][0]+piece_final1[i+1][j][0]+piece_final1[i][j-1][0]+piece_final1[i][j+1][0])/4;
            piece_final1[i][j][1]=(piece_final1[i-1][j][1]+piece_final1[i+1][j][1]+piece_final1[i][j-1][1]+piece_final1[i][j+1][1])/4;
            piece_final1[i][j][2]=(piece_final1[i-1][j][2]+piece_final1[i+1][j][2]+piece_final1[i][j-1][2]+piece_final1[i][j+1][2])/4;
        }
    }
}

 if (!(file=fopen("hillary_modify.raw","wb"))) {
		cout << "Cannot open file: " << "hillary_modify.raw" << endl;
		exit(1);
	}

	fwrite(piece_final, sizeof(unsigned char),   512*512*BytesPerPixel, file);
	printf("File written\n");
	fclose(file);
	if (!(file=fopen("trump_final.raw","wb"))) {
		cout << "Cannot open file: " << "trump_final.raw" << endl;
		exit(1);
	}

	fwrite(piece_final1        , sizeof(unsigned char),   512*512*BytesPerPixel, file);
	printf("File written\n");
	fclose(file);
    return 0;
}
