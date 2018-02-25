#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#include<math.h>
#include<algorithm>
#include<vector>
#include<string.h>
unsigned char board[480][480];
unsigned char board_new[480][480];
unsigned char square[480][480];
unsigned char square_shrink[480][480];
unsigned char square_new[480][480];
unsigned char temp_mat[480][480];
unsigned char output_image[480][480];
unsigned char output_image_final[480][480];
int square_norm[480][480];
int temp_mat_norm[480][480];
unsigned char temp_mat_new[480][480];
unsigned char temp_mat_new1[480][480];
unsigned char temp_mat_new2[480][480];
unsigned char square_inter[480][480];
unsigned char square_fill[480][480];
unsigned char square_inter1[480][480];
unsigned char square_shrink1[480][480];
using namespace std;

int main()
{
   FILE *file1, *file2, *file3,*file4,*file5,*file6,*file;
    int BytesPerPixel=3;
    int i,j;
    if (!(file1=fopen("board.raw","rb"))) {
		cout << "Cannot open file: " << "board.raw" <<endl;
		exit(1);
	}
	fread(board,sizeof(unsigned char), 480*480, file1);
    fclose(file1);
    //-----Complementing the original image----//
    for(int i=0;i<480;i++)
    {
        for(int j=0;j<480;j++)
        {
            board_new[i][j]=255-board[i][j];
        }
    }
     if (!(file=fopen("board_comp1.raw","wb"))) {
		cout << "Cannot open file: " << "board_comp1.raw" << endl;
		exit(1);
	}

	fwrite(board_new, sizeof(unsigned char),   480*480, file);
	printf("File written\n");
	fclose(file);

    if (!(file1=fopen("board_comp1.raw","rb"))) {
		cout << "Cannot open file: " << "board_comp1.raw" <<endl;
		exit(1);
	}
	fread(board_new,sizeof(unsigned char), 480*480, file1);
    fclose(file1);
    //----------Normalise the complemented image------------------//
    int temp_count=0;
    for(int i=0;i<480;i++)
    {
        for(int j=0;j<480;j++)
        {
            square_norm[i][j]=(int)board_new[i][j]/255;
        }
    }

for(int i=0;i<480;i++)
{
    for(int j= 0;j<480;j++)
    {
        temp_mat[i][j]=(int)square_norm[i][j];

    }
}
//--------Shrinking the complemented image 15 times----//

  string string_table[58]={"001010000","100010000","000010100","000010001","000011000","010010000","000110000","000010010","001011000","011010000","110010000",
  "100110000","000110100","000010110","000010011","000011001","001011001","111010000","100110100","000010111","110011000","010011001","011110000",
  "001011010","011011000","110110000","000110110","000011011","110011001","011110100","111011000","011011001","111110000",
  "110110100","100110110","000110111","000011111","001011011","111011001","111110100","100110111","001011111","011011011",
  "111111000","110110110","000111111","111011011","011011111","111111100","111111001","111110110","110110111","100111111",
  "001111111","111011111","111111101","111110111","101111111"};

string uncon[364]={"001010000","100010000","000010010","000011000","001011000","011010000","110010000","100110000","000110100",
"000010110","000010011","000011001","011110000","110011000","010011001","001011010","001011100","011010100","011011100",
"110010001","100110001","110110001","001010110","001110100","001110110","100011001","100010011","100011011",
"110110000","110110001","110111000","110111001","111110000","111110001","111111000",
"111111001","110110010","110110011","110111010","110111011","111110010","111110011",
"111111010","111111011","110110100","110110101","110111100","110111101","111110100","111110101",
"111111100","111111101","110110110","110110111","110111110","110111111","111110110","111110111","111111110","111111111",
"010110010","011110010","110110010","111110010","010110010","010110011","010110110","010110111",
"010011010","010011011","010011110","010011111","010011010","011011010","110011010","111011010",
"010111000","010111100","110111000","110111100","010111000","010111001","011111000","011111001",
"000111010","000111011","001111010","001111011","000111010","000111110","100111010","100111110",
"100010101","100011100","100011101","101010100","101010101","101011100",
"101011101","100010111","100011110","100011111","101010110","101010111",
"101011110","101011111","110010101","110011100","110011101","111010100",
"111010101","111011100","111011101","110010111","110011110","110011111",
"111010110","111010111","111011110","111011111","100110101","100111100",
"100111101","101110100","101110101","101111100","101111101","100110111",
"100111110","100111111","101110110","101110111","101111110","101111111",
"110110101","110111100","110111101","111110100","111110101","111111100",
"111111101","110110111","110111110","110111111","111110110","111110111",
"111111110","111111111",
"101010100","101010010","101010110","101010001","101010101","101010011",
"101010111","101011100","101011010","101011110","101011001","101011101",
"101011011","101011111","111010100","111010010","111010110","111010001",
"111010101","111010011","111010111","111011100","111011010","111011110",
"111011001","111011101","111011011","111011111","101110100","101110010",
"101110110","101110001","101110101","101110011","101110111","101111100",
"101111010","101111110","101111001","101111101","101111011","101111111",
"111110100","111110010","111110110","111110001","111110101","111110011",
"111110111","111111100","111111010","111111110","111111001","111111101",
"111111011","111111111",
"001010101","001110001","001110101","101010001","101010101","101110001",
"101110101","001011101","001111001","001111101","101011001","101011101",
"101111001","101111101","001010111","001110011","001110111","101010011",
"101010111","101110011","101110111","001011111","001111011","001111111",
"101011011","101011111","101111011","101111111","011010101","011110001",
"011110101","111010001","111010101","111110001","111110101","011011101",
"011111001","011111101","111011001","111011101","111111001","111111101",
"011010111","011110011","011110111","111010011","111010111","111110011",
"111110111","011011111","011111011","011111111","111011011","111011111",
"111111011","111111111",
"001010101","010010101","011010101","100010101","101010101","110010101",
"111010101","001011101","010011101","011011101","100011101","101011101",
"110011101","111011101","001010111","010010111","011010111","100010111",
"101010111","110010111","111010111","001011111","010011111","011011111",
"100011111","101011111","110011111","111011111","001110101","010110101",
"011110101","100110101","101110101","110110101","111110101","001111101",
"010111101","011111101","100111101","101111101","110111101","111111101",
"001110111","010110111","011110111","100110111","101110111","110110111",
"111110111","001111111","010111111","011111111","100111111","101111111",
"110111111","111111111",
"001110010","001110011","101110010","101110011",
"010110001","011110001","010110101","011110101","010011100","010011101","110011100","110011101",
"100011010","101011010","100011110","101011110","110110000","110110001","110111000","110111001","111110000","111110001",
"111111000","111111001","110110010","110110011","110111010","110111011",
"111110010","111110011","111111010","111111011","110110100","110110101",
"110111100","110111101","111110100","111110101","111111100","111111101",
"110110110","110110111","110111110","110111111","111110110","111110111",
"111111110","111111111"};


//-----------Actual shrinking operation----------//
string str1="";
string str2="";
int count1=0;
int c1=0;
for(int run=0;run<15;run++)
{
for(int i=0;i<477;i++)
{
for(int j=0;j<477;j++)
{
        for(int m=0;m<3;m++)
        {
            for(int n=0;n<3;n++)
            {
                str1=str1+(char)(temp_mat[m+i][n+j]+48);
            }
        }
        int mid_val=(int)temp_mat[i+1][j+1];
        if(mid_val!=1)
        {
            square_inter[i+1][j+1]=0;
        }
        else
        {
        for(int v=0;v<58;v++) //run through the entire shrinking conditional masks (all 59)
        {
            if(str1==string_table[v]) //if the string of original image is equal to any of the 59, count increment, its a hit
            {
                count1++;
            }
        }
            if(count1!=0) //if it's a hit
            {
                square_inter[i+1][j+1]=1;
            }
             else
            {
            square_inter[i+1][j+1]=0;
            }

        }
        count1=0;
        str1="";
}
}

for(int i=0;i<477;i++)
{
for(int j=0;j<477;j++)
{
        for(int m=0;m<3;m++)
        {
            for(int n=0;n<3;n++)
            {

                    str2=str2+(char)(square_inter[m+i][n+j]+48);
                //cout<<str1<<endl;
            }
            //cout<<endl;
        }
            int new_mid_val=(int)square_inter[i+1][j+1];

            if(new_mid_val==1)
                    {
            //square_shrink[i][j]=255; //shrink that pixel to white
                    for(int val=0;val<364;val++)
                    {
                    if(str2==uncon[val])
                        {
                            c1=c1+1;
                        }
                    }

                    if(c1!=0)
                    {
                        square_shrink[i+1][j+1]=temp_mat[i+1][j+1];

                    }
                    else
                    {
                        square_shrink[i+1][j+1]=0;

                    }

        }
        else
            {
            square_shrink[i+1][j+1]=temp_mat[i+1][j+1];
            }
             c1=0;
        str2="";
        }
}

for(int temp1=0;temp1<480;temp1++)
{
    for(int temp2=0;temp2<480;temp2++)
    {
        temp_mat[temp1][temp2]=square_shrink[temp1][temp2];
        square_inter[temp1][temp2]=0;
    }
}
}
int final1=0;
int h=0;
for(int i=0;i<480;i++)
{
    for(int j=0;j<480;j++)
    {
        if(temp_mat[i][j]==1)
        {
            final1++;
        }
        if(square[i][j]==255)
        {
            h++;
        }
    }
}

for(int i=0;i<480;i++)
{
    for(int j=0;j<480;j++)
    {
    temp_mat[i][j]=255*temp_mat[i][j];
    }
}

for(int i=0;i<480;i++)
{
    for(int j=0;j<480;j++)
    {
        temp_mat_norm[i][j]=(int)temp_mat[i][j]/255;
    }
}
//------------------Checking for the 1 white pixel to count the number of holes-------------------//
string str3="";
int count_hole=0;
for(int i=0;i<477;i++)
{
    for(int j=0;j<477;j++)
    {
         for(int m=0;m<3;m++)
        {
            for(int n=0;n<3;n++)
            {

                    str3=str3+(char)(temp_mat_norm[m+i][n+j]+48);

                //cout<<str1<<endl;
            }
            //cout<<endl;
        }

        if(str3=="000010000") //if there's one white pixel
        {
            cout<<"yes"<<endl;
            count_hole++;
            output_image[i][j]=255; //keep it white
        }
        else
        {
            output_image[i][j]=0; //make the image black
        }
        str3="";
    }
}
//-----------------Counting the number of holes--------------//
cout<<"The number of holes in the board is : "<<count_hole<<endl;
if (!(file=fopen("board_comp1_shrink.raw","wb"))) {
		cout << "Cannot open file: " << "board_comp1_shrink.raw" << endl;
		exit(1);
	}

	fwrite(output_image, sizeof(unsigned char),   480*480, file);
	printf("File written\n");
	fclose(file);
//---------Normalize the output image------------//
for(int i=0;i<480;i++)
{
    for(int j=0;j<480;j++)
    {
        temp_mat_new[i][j]=(int)output_image[i][j]/255;
    }
}
int input[480][480];

//------------------Dilating the image with 9 holes about 15 times-------------//
for(int run=0;run<15;run++)
{
for(int i=0;i<480;i++)
{
    for(int j=0;j<480;j++)
    {

          if((int)temp_mat_new[i][j]==1)
          {
              temp_mat_new1[i][j+1]=1;
              temp_mat_new1[i][j-1]=1;
              temp_mat_new1[i+1][j]=1;
              temp_mat_new1[i-1][j]=1;
              temp_mat_new1[i-1][j-1]=1;
              temp_mat_new1[i-1][j+1]=1;
              temp_mat_new1[i+1][j+1]=1;
              temp_mat_new1[i+1][j-1]=1;
              temp_mat_new1[i][j]=1;
          }

    }

}
 for(int i=0;i<480;i++)
 {
     for(int j=0;j<480;j++)
     {
         temp_mat_new[i][j]=(int)temp_mat_new1[i][j];
     }
 }
}

for(int i=0;i<480;i++)
{
    for(int j=0;j<480;j++)
    {
        temp_mat_new[i][j]=255*temp_mat_new[i][j];
    }
}
//---------------Unioning the output of the dilated image with the input board image to fill the holes-------//
for(int i=0;i<480;i++)
{
    for(int j=0;j<480;j++)
    {
        output_image_final[i][j]=max(temp_mat_new[i][j],board[i][j]); //max gives the union of the two images
    }
}
//--------------Normalizing the output hole filled image---------------//
unsigned int temp_mat_norm1[480][480];
for(int i=0;i<480;i++)
{
    for(int j=0;j<480;j++)
    {
        temp_mat_norm1[i][j]=output_image_final[i][j]/255;
    }
}
//-------------------Assigning the input to a temporary variable input_norm1--------//
unsigned char input_norm1[480][480];
for(int i=0;i<480;i++)
{
    for(int j=0;j<480;j++)
    {
        input_norm1[i][j]=(int)temp_mat_norm1[i][j];
    }
}
//--------------Shrinking the dilated image 90 time-----------//
string str6="";
string str7="";
int count_hole1=0;
int c2=0;
for(int run=0;run<90;run++)
{
for(int i=0;i<477;i++)
{
for(int j=0;j<477;j++)
{
        for(int m=0;m<3;m++)
        {
            for(int n=0;n<3;n++)
            {
                str6=str6+(char)(input_norm1[m+i][n+j]+48);
            }
        }
        int mid_val=(int)input_norm1[i+1][j+1];
        if(mid_val!=1)
        {
            square_inter1[i+1][j+1]=0;
        }
        else
        {
        for(int v=0;v<58;v++) //run through the entire shrinking conditional masks (all 59)
        {
            if(str6==string_table[v]) //if the string of original image is equal to any of the 59, count increment, its a hit
            {
                count_hole1++;
            }
        }
            if(count_hole1!=0) //if it's a hit
            {
                square_inter1[i+1][j+1]=1;
            }
             else
            {
            square_inter1[i+1][j+1]=0;
            }

        }
        count_hole1=0;
        str6="";
}
}

for(int i=0;i<477;i++)
{
for(int j=0;j<477;j++)
{
        for(int m=0;m<3;m++)
        {
            for(int n=0;n<3;n++)
            {

                    str7=str7+(char)(square_inter1[m+i][n+j]+48);
                //cout<<str1<<endl;
            }
            //cout<<endl;
        }
            int new_mid_val=(int)square_inter1[i+1][j+1];

            if(new_mid_val==1)
                    {
            //square_shrink[i][j]=255; //shrink that pixel to white
                    for(int val=0;val<364;val++)
                    {
                    if(str7==uncon[val])
                        {
                            c2=c2+1;
                        }
                    }

                    if(c2!=0)
                    {
                        square_shrink1[i+1][j+1]=input_norm1[i+1][j+1];

                    }
                    else
                    {
                        square_shrink1[i+1][j+1]=0;

                    }

        }
        else
            {
            square_shrink1[i+1][j+1]=input_norm1[i+1][j+1];
            }
             c2=0;
        str7="";
        }
}

for(int temp1=0;temp1<480;temp1++)
{
    for(int temp2=0;temp2<480;temp2++)
    {
        input_norm1[temp1][temp2]=square_shrink1[temp1][temp2];
        square_inter1[temp1][temp2]=0;
    }
}
}
int final2=0;
int h1=0;
for(int i=0;i<480;i++)
{
    for(int j=0;j<480;j++)
    {
        if(input_norm1[i][j]==1)
        {
            final2++;
        }

    }
}
for(int i=0;i<480;i++)
{
    for(int j=0;j<480;j++)
    {
        input_norm1[i][j]=255*input_norm1[i][j];
    }
}

cout<<"The total number of objects in the image is : "<< final2<<endl;
//---------------------------Finding the number of squares in the image--------------//

/*string str5="";
 for(int i=0;i<480;i++)
 {
     for(int j=0;j<480;j++)
     {

     for(int m=0;m<3;m++)
     {
     for(int n=0;n<3;n++)
     {
          str5=str5+(char)(temp_mat_norm1[m+i][n+j]+48);
     }
     }
     if((str5=="000011011")||(str5=="000001011")

 }*/

if (!(file=fopen("board_comp1_shrink1.raw","wb"))) {
		cout << "Cannot open file: " << "board_comp1_shrink1.raw" << endl;
		exit(1);
	}

	fwrite(temp_mat_new, sizeof(unsigned char),   480*480, file);
	printf("File written\n");
	fclose(file);
if (!(file=fopen("board_15objects_shrink.raw","wb"))) {
		cout << "Cannot open file: " << "board_15objects_shrink.raw" << endl;
		exit(1);
	}

	fwrite(input_norm1, sizeof(unsigned char),   480*480, file);
	printf("File written\n");
	fclose(file);

return 0;

}

