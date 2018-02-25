#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include<vector>
#include<iostream>
#include<math.h>
#include<algorithm>
unsigned char man[512][512];
unsigned char man_new[512][512];
unsigned char man_new1[512][512];
unsigned char man_new2[512][512];
unsigned char man_new_a[512][512];
unsigned char man_four[512][512];
using namespace std;

int main()
{
    int i,j;
	int BytesPerPixel=3;
    FILE *file,*file2,*file1,*file3,*file4,*file5,*file6;
	if (!(file=fopen("man.raw","rb"))) {
		cout << "Cannot open file: " << "man.raw" <<endl;
		exit(1);
	}
	fread(man, sizeof(unsigned char), 512*512, file);
	fclose(file);
	unsigned int temp1[2][2];
	int man_2[2][2]={0,2,3,1};
	double temp[2][2]={};
	//Generating T(X,Y) for 2x2
	for(int m=0;m<2;m++)
    {
        for(int n=0;n<2;n++)
        {
            temp[m][n]=((man_2[m][n]+0.5)/(2*2));
            temp1[m][n]=255*temp[m][n];
        }
    }
    //Creating 4x4 bayer index matrix
unsigned int man_4[4][4];
for(int r=0;r<2;r++)
{
    for(int q=0;q<2;q++)
    {
        man_4[r][q]=4*man_2[r][q];
    }
}
for(int r=0;r<2;r++)
{
    for(int q=2;q<4;q++)
    {
        man_4[r][q]=(4*man_2[r][q-2])+2;
    }
}
for(int r=2;r<4;r++)
{
    for(int q=0;q<2;q++)
    {
        man_4[r][q]=(4*man_2[r-2][q])+3;
    }
}
for(int r=2;r<4;r++)
{
    for(int q=2;q<4;q++)
    {
        man_4[r][q]=(4*man_2[r-2][q-2])+1;
    }
}
//computing T(x,y) for 4x4
unsigned int A4[4][4]={14,10,11,15,9,3,0,4,8,2,1,5,13,7,6,12};
double temp_4[4][4]={};
unsigned int temp_4_final[4][4];
double temp_a[4][4];
unsigned int temp_a_final[4][4];
for(int r=0;r<4;r++)
{
    for(int q=0;q<4;q++)
    {
         temp_4[r][q]=((man_4[r][q]+0.5)/(4*4));
        temp_4_final[r][q]=255*temp_4[r][q];
        temp_a[r][q]=((A4[r][q]+0.5)/(4*4));
         temp_a_final[r][q]=255*temp_a[r][q];
         cout<<temp_a_final[r][q]<<endl;
    }
}
//Creating 8x8 bayer index matrix
unsigned int man_8[8][8];
for(int r=0;r<4;r++)
{
    for(int q=0;q<4;q++)
    {
        man_8[r][q]=4*man_4[r][q];
    }
}
for(int r=0;r<4;r++)
{
    for(int q=4;q<8;q++)
    {
        man_8[r][q]=(4*man_4[r][q-4])+2;
    }
}
for(int r=4;r<8;r++)
{
    for(int q=0;q<4;q++)
    {
        man_8[r][q]=(4*man_4[r-4][q])+3;
    }
}
for(int r=4;r<8;r++)
{
    for(int q=4;q<8;q++)
    {
        man_8[r][q]=(4*man_4[r-4][q-4])+1;
    }
}

double temp2[8][8]={};
unsigned int temp3[8][8];
for(int row=0;row<8;row++)
{
    for(int col=0;col<8;col++)
    {
        temp2[row][col]=((man_8[row][col]+0.5)/(8*8));
        temp3[row][col]=255*temp2[row][col];
        //cout<<temp3[row][col]<<endl;
    }
}
//Assigning 0 or 1 after threshold checking
 for(int i=0;i<512;i++)
    {
        for(int j=0;j<512;j++)
        {

            if(((int)man[i][j])>(temp1[i%2][j%2])) //For the 2x2 threshold matrix
               {
                   //cout<<"yes"<<endl;
                   man_new[i][j]=255;

               }
               else
               {
                   man_new[i][j]=0;
               }
               if((int)man[i][j]>(temp3[i%8][j%8])) //For 8x8 threshold matrix
               {
                   man_new1[i][j]=255;

               }
               else
               {
                   man_new1[i][j]=0;
               }
               if((int)man[i][j]>(temp_4_final[i%4][j%4])) //For the 4x4 dithered matrix
               {
                   man_new2[i][j]=255;

               }
               else{
                man_new2[i][j]=0;
               }
               if((int)man[i][j]>(temp_a_final[i%4][j%4])) //For the 4x4 A matrix
               {
                   man_new_a[i][j]=255;
               }
               else{
                man_new_a[i][j]=0;
               }
               if((int)man[i][j]<42)// For the 4 greyscale intensity matrix
               {
                   man_four[i][j]=0;
               }
               if((int)man[i][j]>42&&(int)man[i][j]<85)
                {
                man_four[i][j]=85;
               }
               if((int)man[i][j]<127&&(int)man[i][j]>85)
               {
                   man_four[i][j]=85;
               }
              if((int)man[i][j]>127&&(int)man[i][j]<170)
               {
                man_four[i][j]=170;
               }
               if((int)man[i][j]>170&&(int)man[i][j]<212)
               {
                man_four[i][j]=170;
               }
               if((int)man[i][j]>212&&(int)man[i][j]<255)
               {
                man_four[i][j]=225;
               }
        }
    }
   //Writing all output images into the respect files


    if (!(file2=fopen("man_new.raw","wb"))) {
		cout << "Cannot open file: " << "man_new.raw" << endl;
		exit(1);
	}
	fwrite(man_new, sizeof(unsigned char),   512*512, file2);
	printf("File written\n");
	fclose(file2);
	 if (!(file2=fopen("man_new_8.raw","wb"))) {
		cout << "Cannot open file: " << "man_new_8.raw" << endl;
		exit(1);
	}
	fwrite(man_new1, sizeof(unsigned char),   512*512, file2);
	printf("File written\n");
	fclose(file2);

	 if (!(file2=fopen("man_new_4.raw","wb"))) {
		cout << "Cannot open file: " << "man_new_4.raw" << endl;
		exit(1);
	}
	fwrite(man_new2, sizeof(unsigned char),   512*512, file2);
	printf("File written\n");
	fclose(file2);
	 if (!(file2=fopen("man_new_a.raw","wb"))) {
		cout << "Cannot open file: " << "man_new_a.raw" << endl;
		exit(1);
	}
	fwrite(man_new_a, sizeof(unsigned char),   512*512, file2);
	printf("File written\n");
	fclose(file2);
	if (!(file2=fopen("man_four.raw","wb"))) {
		cout << "Cannot open file: " << "man_four.raw" << endl;
		exit(1);
	}
	fwrite(man_four, sizeof(unsigned char),   512*512, file2);
	printf("File written\n");
	fclose(file2);
    return 0;
}
