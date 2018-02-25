#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#include<math.h>
#include<algorithm>
unsigned char text1[128][128];
unsigned char text2[128][128];
unsigned char text3[128][128];
unsigned char text4[128][128];
unsigned char text5[128][128];
unsigned char text6[128][128];
unsigned char text7[128][128];
unsigned char text8[128][128];
unsigned char text9[128][128];
unsigned char text10[128][128];
unsigned char text11[128][128];
unsigned char text12[128][128];
unsigned char textA[128][128];
unsigned char textB[128][128];
unsigned char textC[128][128];
unsigned char textD[128][128];
unsigned char textE[128][128];
unsigned char textF[128][128];
using namespace std;
//----------------------25 filter bank generation-----------------//
int** multiply(int arr[1][5] , int arr1[5][1])
{

   int** final_mat=0;
   final_mat=new int*[5];
    for(int i=0;i<5;i++)
    {
        final_mat[i]=new int[5];
        for( int j=0;j<5;j++)
        {
          final_mat[i][j]=arr[0][i]*arr1[j][0]; //computing the 5x5 matrix combinations
        }
    }
    return final_mat;

}
//----------------------Global Mean subtraction from each pixel----------------//
void mean(unsigned char image[128][128])
{
    int sum=0;
    for(int i=0;i<128;i++)
    {
        for(int j=0;j<128;j++)
        {
           sum=sum+image[i][j];
        }
    }
    double mean=sum/(128.0*128.0);

    for(int i=0;i<128;i++)
    {
        for(int j=0;j<128;j++)
        {
            image[i][j]=image[i][j]-mean; //subtracting the global mean from each of the pixel intensities

        }
    }

}
//--------------Boundary Extension for each image---------------------------//
unsigned char** boundary_extend(unsigned char arr[128][128])
{
int ext=5;
int extend=(ext-1)/2;
//---dynamically allocating memory to the newly extended image
unsigned char** pepper_extend;
    pepper_extend=new unsigned char*[132];
    for(int i=0;i<132;i++)
    {
        pepper_extend[i]=new unsigned char[132];
        for(int j=0;j<132;j++)
        {
            pepper_extend[i][j]=0;
        }
    }
    for(int m=0;m<128;m++)
    {

        for(int n=0;n<128;n++)
        {
                pepper_extend[m+extend][n+extend]=arr[m][n];
        }
    }

    for(int i=extend;i>0;i--)
    {

         for(int j=extend;j<(128+extend-1);j++)
         {
                pepper_extend[i-1][j]=pepper_extend[i][j];
    }
    }
    for(int i_bottom=(128+extend-1);i_bottom<(128+(2*extend)-1);i_bottom++)
    {

    for(int j_bottom=extend;j_bottom<(128+extend-1);j_bottom++)
    {

                pepper_extend[i_bottom+1][j_bottom]=pepper_extend[i_bottom][j_bottom];
    }
    }

    for(int row_left=0;row_left<(128+(2*extend)-1);row_left++)
    {

        for(int col_left=extend;col_left>0;col_left--)
        {
                pepper_extend[row_left][col_left-1]=pepper_extend[row_left][col_left];
        }
    }
    for(int col_right=0;col_right<(128+(2*extend)-1);col_right++)
    {

    for(int row_right=(128+extend-1);row_right<(128+(2*extend)-1);row_right++)
    {
                pepper_extend[col_right][row_right+1]=pepper_extend[col_right][row_right];

    }
    }

    return pepper_extend;
    }
    //--------------Energy feature calculation from the 132x132 extended image--------//
double* energy_feature(unsigned char** arr2)
{
  double energy_final[25]={0.0};
  //---calling function to get the LAWS filters--//
  int L5[1][5]={1,4,6,4,1};
int L5T[5][1]={1,4,6,4,1};
int E5[1][5]={-1,-2,0,2,1};
int E5T[5][1]={-1,-2,0,2,1};
int S5[1][5]={-1,0,2,0,-1};
int S5T[5][1]={-1,0,2,0,-1};
int W5[1][5]={-1,2,0,-2,1};
int W5T[5][1]={-1,2,0,-2,1};
 int R5[1][5]={1,-4,6,-4,1};
 int R5T[5][1]={1,-4,6,-4,1};
  int** LL_matrix=multiply(L5,L5T);
   int** LE_matrix=multiply(L5,E5T);
   int** LS_matrix=multiply(L5,S5T);
   int** LW_matrix=multiply(L5,W5T);
   int** LR_matrix=multiply(L5,R5T);
   int** EE_matrix=multiply(E5,E5T);
   int** EL_matrix=multiply(E5,L5T);
   int** ES_matrix=multiply(E5,S5T);
   int** EW_matrix=multiply(E5,W5T);
   int** ER_matrix=multiply(E5,R5T);
   int** SS_matrix=multiply(S5,S5T);
   int** SL_matrix=multiply(S5,L5T);
   int** SE_matrix=multiply(S5,E5T);
   int** SW_matrix=multiply(S5,W5T);
   int** SR_matrix=multiply(S5,R5T);
   int** WW_matrix=multiply(W5,W5T);
   int** WL_matrix=multiply(W5,L5T);
   int** WE_matrix=multiply(W5,E5T);
   int** WS_matrix=multiply(W5,S5T);
   int** WR_matrix=multiply(W5,R5T);
   int** RR_matrix=multiply(R5,R5T);
   int** RL_matrix=multiply(R5,L5T);
   int** RE_matrix=multiply(R5,E5T);
   int** RS_matrix=multiply(R5,S5T);
   int** RW_matrix=multiply(R5,W5T);
    //------for matrix 1------//
   int sum_val=0;
    unsigned int arr_temp[128][128];
    for(int i=0;i<128;i++)
    {
        for(int j=0;j<128;j++)
        {
            for(int m=0;m<5;m++)
            {
                for(int n=0;n<5;n++)
                {
                    sum_val=sum_val+(arr2[i+m][j+n]*LL_matrix[m][n]); //performing convolution
                }
            }
            arr_temp[i][j]=sum_val;
            sum_val=0.0;
        }
    }
    double square_value=0.0;
    double square_final=0.0;
    for(int i=0;i<128;i++)
    {
        for(int j=0;j<128;j++)
        {
            square_value=square_value+(arr_temp[i][j]*arr_temp[i][j]);
        }
    }
    square_final=square_value/(128.0*128.0); //computing final energy for the first matrix
    energy_final[0]=square_final;
    //-------for matrix 2-------//
      unsigned int arr_temp1[128][128];
      int sum_val1=0;
        for(int i=0;i<128;i++)
    {
        for(int j=0;j<128;j++)
        {
            for(int m=0;m<5;m++)
            {
                for(int n=0;n<5;n++)
                {
                    sum_val1=sum_val1+(arr2[i+m][j+n]*LE_matrix[m][n]);
                }
            }
            arr_temp1[i][j]=sum_val1;
           // cout<<arr_temp[i][j]<<endl;
            sum_val1=0.0;
        }
    }
    double square_value1=0.0;
    double square_final1=0.0;
    for(int i=0;i<128;i++)
    {
        for(int j=0;j<128;j++)
        {
            square_value1=square_value1+(arr_temp1[i][j]*arr_temp1[i][j]);
        }
    }
    square_final1=square_value1/(128.0*128.0);
    energy_final[1]=square_final1;
    //-------for matrix 3---------------//
        unsigned int arr_temp2[128][128];
      int sum_val2=0;
        for(int i=0;i<128;i++)
    {
        for(int j=0;j<128;j++)
        {
            for(int m=0;m<5;m++)
            {
                for(int n=0;n<5;n++)
                {
                    sum_val2=sum_val2+(arr2[i+m][j+n]*LW_matrix[m][n]);
                }
            }
            arr_temp2[i][j]=sum_val2;
            sum_val2=0.0;
        }
    }
    double square_value2=0.0;
    double square_final2=0.0;
    for(int i=0;i<128;i++)
    {
        for(int j=0;j<128;j++)
        {
            square_value2=square_value2+(arr_temp2[i][j]*arr_temp2[i][j]);
        }
    }
    square_final2=square_value2/(128.0*128.0);
    energy_final[2]=square_final2;
    //-------for matrix 4-----------//
        unsigned int arr_temp3[128][128];
      int sum_val3=0;
        for(int i=0;i<128;i++)
    {
        for(int j=0;j<128;j++)
        {
            for(int m=0;m<5;m++)
            {
                for(int n=0;n<5;n++)
                {
                    sum_val3=sum_val3+(arr2[i+m][j+n]*LS_matrix[m][n]);
                }
            }
            arr_temp3[i][j]=sum_val3;
            sum_val3=0.0;
        }
    }
    double square_value3=0.0;
    double square_final3=0.0;
    for(int i=0;i<128;i++)
    {
        for(int j=0;j<128;j++)
        {
            square_value3=square_value3+(arr_temp3[i][j]*arr_temp3[i][j]);
        }
    }
    square_final3=square_value3/(128.0*128.0);
    energy_final[3]=square_final3;
    //-----------for matrix 5----------//
              unsigned int arr_temp4[128][128];
      int sum_val4=0;
        for(int i=0;i<128;i++)
    {
        for(int j=0;j<128;j++)
        {
            for(int m=0;m<5;m++)
            {
                for(int n=0;n<5;n++)
                {
                    sum_val4=sum_val4+(arr2[i+m][j+n]*LR_matrix[m][n]);
                }
            }
            arr_temp4[i][j]=sum_val4;
            sum_val4=0.0;
        }
    }
    double square_value4=0.0;
    double square_final4=0.0;
    for(int i=0;i<128;i++)
    {
        for(int j=0;j<128;j++)
        {
            square_value4=square_value4+(arr_temp4[i][j]*arr_temp4[i][j]);
        }
    }
    square_final4=square_value4/(128.0*128.0);
    energy_final[4]=square_final4;
    //--------for matrix 6--------//
        unsigned int arr_temp5[128][128];
      int sum_val5=0;
        for(int i=0;i<128;i++)
    {
        for(int j=0;j<128;j++)
        {
            for(int m=0;m<5;m++)
            {
                for(int n=0;n<5;n++)
                {
                    sum_val5=sum_val5+(arr2[i+m][j+n]*EL_matrix[m][n]);
                }
            }
            arr_temp5[i][j]=sum_val5;
            sum_val5=0.0;
        }
    }
    double square_value5=0.0;
    double square_final5=0.0;
    for(int i=0;i<128;i++)
    {
        for(int j=0;j<128;j++)
        {
            square_value5=square_value5+(arr_temp5[i][j]*arr_temp5[i][j]);
        }
    }
    square_final5=square_value5/(128.0*128.0);
    energy_final[5]=square_final5;
    //------------For matrix 7-----------//
        unsigned int arr_temp6[128][128];
      int sum_val6=0;
        for(int i=0;i<128;i++)
    {
        for(int j=0;j<128;j++)
        {
            for(int m=0;m<5;m++)
            {
                for(int n=0;n<5;n++)
                {
                    sum_val6=sum_val6+(arr2[i+m][j+n]*EE_matrix[m][n]);
                }
            }
            arr_temp6[i][j]=sum_val6;
            sum_val6=0.0;
        }
    }
    double square_value6=0.0;
    double square_final6=0.0;
    for(int i=0;i<128;i++)
    {
        for(int j=0;j<128;j++)
        {
            square_value6=square_value6+(arr_temp6[i][j]*arr_temp6[i][j]);
        }
    }
    square_final6=square_value6/(128.0*128.0);
    energy_final[6]=square_final6;
    //------------for matrix 8------//
        unsigned int arr_temp7[128][128];
      int sum_val7=0;
        for(int i=0;i<128;i++)
    {
        for(int j=0;j<128;j++)
        {
            for(int m=0;m<5;m++)
            {
                for(int n=0;n<5;n++)
                {
                    sum_val7=sum_val7+(arr2[i+m][j+n]*EW_matrix[m][n]);
                }
            }
            arr_temp7[i][j]=sum_val7;
            sum_val7=0.0;
        }
    }
    double square_value7=0.0;
    double square_final7=0.0;
    for(int i=0;i<128;i++)
    {
        for(int j=0;j<128;j++)
        {
            square_value7=square_value7+(arr_temp7[i][j]*arr_temp7[i][j]);
        }
    }
    square_final7=square_value7/(128.0*128.0);
    energy_final[7]=square_final7;
    //-------for matrix 9-----//
        unsigned int arr_temp8[128][128];
      int sum_val8=0;
        for(int i=0;i<128;i++)
    {
        for(int j=0;j<128;j++)
        {
            for(int m=0;m<5;m++)
            {
                for(int n=0;n<5;n++)
                {
                    sum_val8=sum_val8+(arr2[i+m][j+n]*ES_matrix[m][n]);
                }
            }
            arr_temp8[i][j]=sum_val8;
            sum_val8=0.0;
        }
    }
    double square_value8=0.0;
    double square_final8=0.0;
    for(int i=0;i<128;i++)
    {
        for(int j=0;j<128;j++)
        {
            square_value8=square_value8+(arr_temp8[i][j]*arr_temp8[i][j]);
        }
    }
    square_final8=square_value8/(128.0*128.0);
    energy_final[8]=square_final8;
    //-----------for matrix 10------//
       unsigned int arr_temp9[128][128];
      int sum_val9=0;
        for(int i=0;i<128;i++)
    {
        for(int j=0;j<128;j++)
        {
            for(int m=0;m<5;m++)
            {
                for(int n=0;n<5;n++)
                {
                    sum_val9=sum_val9+(arr2[i+m][j+n]*ER_matrix[m][n]);
                }
            }
            arr_temp9[i][j]=sum_val9;
            sum_val9=0.0;
        }
    }
    double square_value9=0.0;
    double square_final9=0.0;
    for(int i=0;i<128;i++)
    {
        for(int j=0;j<128;j++)
        {
            square_value9=square_value9+(arr_temp9[i][j]*arr_temp9[i][j]);
        }
    }
    square_final9=square_value9/(128.0*128.0);
    energy_final[9]=square_final9;
    //---------for matrix 11------//
           unsigned int arr_temp10[128][128];
      int sum_val10=0;
        for(int i=0;i<128;i++)
    {
        for(int j=0;j<128;j++)
        {
            for(int m=0;m<5;m++)
            {
                for(int n=0;n<5;n++)
                {
                    sum_val10=sum_val10+(arr2[i+m][j+n]*SL_matrix[m][n]);
                }
            }
            arr_temp10[i][j]=sum_val10;
            sum_val10=0.0;
        }
    }
    double square_value10=0.0;
    double square_final10=0.0;
    for(int i=0;i<128;i++)
    {
        for(int j=0;j<128;j++)
        {
            square_value10=square_value10+(arr_temp10[i][j]*arr_temp10[i][j]);
        }
    }
    square_final10=square_value10/(128.0*128.0);
    energy_final[10]=square_final10;
    //---------for matrix 12------//
    unsigned int arr_temp11[128][128];
      int sum_val11=0;
        for(int i=0;i<128;i++)
    {
        for(int j=0;j<128;j++)
        {
            for(int m=0;m<5;m++)
            {
                for(int n=0;n<5;n++)
                {
                    sum_val11=sum_val11+(arr2[i+m][j+n]*SE_matrix[m][n]);
                }
            }
            arr_temp11[i][j]=sum_val11;
            sum_val11=0.0;
        }
    }
    double square_value11=0.0;
    double square_final11=0.0;
    for(int i=0;i<128;i++)
    {
        for(int j=0;j<128;j++)
        {
            square_value11=square_value11+(arr_temp11[i][j]*arr_temp11[i][j]);
        }
    }
    square_final11=square_value11/(128.0*128.0);
    energy_final[11]=square_final11;
    //-------------for matrix 13------------//
    unsigned int arr_temp12[128][128];
      int sum_val12=0;
        for(int i=0;i<128;i++)
    {
        for(int j=0;j<128;j++)
        {
            for(int m=0;m<5;m++)
            {
                for(int n=0;n<5;n++)
                {
                    sum_val12=sum_val12+(arr2[i+m][j+n]*SW_matrix[m][n]);
                }
            }
            arr_temp12[i][j]=sum_val12;
            sum_val12=0.0;
        }
    }
    double square_value12=0.0;
    double square_final12=0.0;
    for(int i=0;i<128;i++)
    {
        for(int j=0;j<128;j++)
        {
            square_value12=square_value12+(arr_temp12[i][j]*arr_temp12[i][j]);
        }
    }
    square_final12=square_value12/(128.0*128.0);
    energy_final[12]=square_final12;
    //---------for matrix 14-------//
        unsigned int arr_temp13[128][128];
      int sum_val13=0;
        for(int i=0;i<128;i++)
    {
        for(int j=0;j<128;j++)
        {
            for(int m=0;m<5;m++)
            {
                for(int n=0;n<5;n++)
                {
                    sum_val13=sum_val13+(arr2[i+m][j+n]*SS_matrix[m][n]);
                }
            }
            arr_temp13[i][j]=sum_val13;
            sum_val13=0.0;
        }
    }
    double square_value13=0.0;
    double square_final13=0.0;
    for(int i=0;i<128;i++)
    {
        for(int j=0;j<128;j++)
        {
            square_value13=square_value13+(arr_temp13[i][j]*arr_temp13[i][j]);
        }
    }
    square_final13=square_value13/(128.0*128.0);
    energy_final[13]=square_final13;
//---------for matrix 15-----------//
        unsigned int arr_temp14[128][128];
      int sum_val14=0;
        for(int i=0;i<128;i++)
    {
        for(int j=0;j<128;j++)
        {
            for(int m=0;m<5;m++)
            {
                for(int n=0;n<5;n++)
                {
                    sum_val14=sum_val14+(arr2[i+m][j+n]*SR_matrix[m][n]);
                }
            }
            arr_temp14[i][j]=sum_val14;
            sum_val14=0.0;
        }
    }
    double square_value14=0.0;
    double square_final14=0.0;
    for(int i=0;i<128;i++)
    {
        for(int j=0;j<128;j++)
        {
            square_value14=square_value14+(arr_temp14[i][j]*arr_temp14[i][j]);
        }
    }
    square_final14=square_value14/(128.0*128.0);
    energy_final[14]=square_final14;
    //---------For matrix 16------//
        unsigned int arr_temp15[128][128];
      int sum_val15=0;
        for(int i=0;i<128;i++)
    {
        for(int j=0;j<128;j++)
        {
            for(int m=0;m<5;m++)
            {
                for(int n=0;n<5;n++)
                {
                    sum_val15=sum_val15+(arr2[i+m][j+n]*RL_matrix[m][n]);
                }
            }
            arr_temp15[i][j]=sum_val15;
            sum_val15=0.0;
        }
    }
    double square_value15=0.0;
    double square_final15=0.0;
    for(int i=0;i<128;i++)
    {
        for(int j=0;j<128;j++)
        {
            square_value15=square_value15+(arr_temp15[i][j]*arr_temp15[i][j]);
        }
    }
    square_final15=square_value15/(128.0*128.0);
    energy_final[15]=square_final15;
    //-----for matrix 17----//
     unsigned int arr_temp16[128][128];
      int sum_val16=0;
        for(int i=0;i<128;i++)
    {
        for(int j=0;j<128;j++)
        {
            for(int m=0;m<5;m++)
            {
                for(int n=0;n<5;n++)
                {
                    sum_val16=sum_val16+(arr2[i+m][j+n]*RE_matrix[m][n]);
                }
            }
            arr_temp16[i][j]=sum_val16;
            sum_val16=0.0;
        }
    }
    double square_value16=0.0;
    double square_final16=0.0;
    for(int i=0;i<128;i++)
    {
        for(int j=0;j<128;j++)
        {
            square_value16=square_value16+(arr_temp16[i][j]*arr_temp16[i][j]);
        }
    }
    square_final16=square_value16/(128.0*128.0);
    energy_final[16]=square_final16;
    //-------for matrix 18------//
    unsigned int arr_temp17[128][128];
      int sum_val17=0;
        for(int i=0;i<128;i++)
    {
        for(int j=0;j<128;j++)
        {
            for(int m=0;m<5;m++)
            {
                for(int n=0;n<5;n++)
                {
                    sum_val17=sum_val17+(arr2[i+m][j+n]*RS_matrix[m][n]);
                }
            }
            arr_temp17[i][j]=sum_val17;
            sum_val17=0.0;
        }
    }
    double square_value17=0.0;
    double square_final17=0.0;
    for(int i=0;i<128;i++)
    {
        for(int j=0;j<128;j++)
        {
            square_value17=square_value17+(arr_temp17[i][j]*arr_temp17[i][j]);
        }
    }
    square_final17=square_value17/(128.0*128.0);
    energy_final[17]=square_final17;
    //-------for matrix 19----//
        unsigned int arr_temp18[128][128];
      int sum_val18=0;
        for(int i=0;i<128;i++)
    {
        for(int j=0;j<128;j++)
        {
            for(int m=0;m<5;m++)
            {
                for(int n=0;n<5;n++)
                {
                    sum_val18=sum_val18+(arr2[i+m][j+n]*RW_matrix[m][n]);
                }
            }
            arr_temp18[i][j]=sum_val18;
            sum_val18=0.0;
        }
    }
    double square_value18=0.0;
    double square_final18=0.0;
    for(int i=0;i<128;i++)
    {
        for(int j=0;j<128;j++)
        {
            square_value18=square_value18+(arr_temp18[i][j]*arr_temp18[i][j]);
        }
    }
    square_final18=square_value18/(128.0*128.0);
    energy_final[18]=square_final18;
    //-------for matrix 20-------//
            unsigned int arr_temp19[128][128];
      int sum_val19=0;
        for(int i=0;i<128;i++)
    {
        for(int j=0;j<128;j++)
        {
            for(int m=0;m<5;m++)
            {
                for(int n=0;n<5;n++)
                {
                    sum_val19=sum_val19+(arr2[i+m][j+n]*RR_matrix[m][n]);
                }
            }
            arr_temp19[i][j]=sum_val19;
            sum_val19=0.0;
        }
    }
    double square_value19=0.0;
    double square_final19=0.0;
    for(int i=0;i<128;i++)
    {
        for(int j=0;j<128;j++)
        {
            square_value19=square_value19+(arr_temp19[i][j]*arr_temp19[i][j]);
        }
    }
    square_final19=square_value19/(128.0*128.0);
    energy_final[19]=square_final19;
    //--------for matrix 21---------//
           unsigned int arr_temp20[128][128];
      int sum_val20=0;
        for(int i=0;i<128;i++)
    {
        for(int j=0;j<128;j++)
        {
            for(int m=0;m<5;m++)
            {
                for(int n=0;n<5;n++)
                {
                    sum_val20=sum_val20+(arr2[i+m][j+n]*WL_matrix[m][n]);
                }
            }
            arr_temp20[i][j]=sum_val20;
            sum_val20=0.0;
        }
    }
    double square_value20=0.0;
    double square_final20=0.0;
    for(int i=0;i<128;i++)
    {
        for(int j=0;j<128;j++)
        {
            square_value20=square_value20+(arr_temp20[i][j]*arr_temp20[i][j]);
        }
    }
    square_final20=square_value20/(128.0*128.0);
    energy_final[20]=square_final20;
    //------for matrix 22------//
               unsigned int arr_temp21[128][128];
      int sum_val21=0;
        for(int i=0;i<128;i++)
    {
        for(int j=0;j<128;j++)
        {
            for(int m=0;m<5;m++)
            {
                for(int n=0;n<5;n++)
                {
                    sum_val21=sum_val21+(arr2[i+m][j+n]*WE_matrix[m][n]);
                }
            }
            arr_temp21[i][j]=sum_val21;
            sum_val21=0.0;
        }
    }
    double square_value21=0.0;
    double square_final21=0.0;
    for(int i=0;i<128;i++)
    {
        for(int j=0;j<128;j++)
        {
            square_value21=square_value21+(arr_temp21[i][j]*arr_temp21[i][j]);
        }
    }
    square_final21=square_value21/(128.0*128.0);
    energy_final[21]=square_final21;
    //-------for matrix 23------//
                   unsigned int arr_temp22[128][128];
      int sum_val22=0;
        for(int i=0;i<128;i++)
    {
        for(int j=0;j<128;j++)
        {
            for(int m=0;m<5;m++)
            {
                for(int n=0;n<5;n++)
                {
                    sum_val22=sum_val22+(arr2[i+m][j+n]*WS_matrix[m][n]);
                }
            }
            arr_temp22[i][j]=sum_val22;
            sum_val22=0.0;
        }
    }
    double square_value22=0.0;
    double square_final22=0.0;
    for(int i=0;i<128;i++)
    {
        for(int j=0;j<128;j++)
        {
            square_value22=square_value22+(arr_temp22[i][j]*arr_temp22[i][j]);
        }
    }
    square_final22=square_value22/(128.0*128.0);
    energy_final[22]=square_final22;
    //------for matrix 24-------//
    unsigned int arr_temp23[128][128];
      int sum_val23=0;
        for(int i=0;i<128;i++)
    {
        for(int j=0;j<128;j++)
        {
            for(int m=0;m<5;m++)
            {
                for(int n=0;n<5;n++)
                {
                    sum_val23=sum_val23+(arr2[i+m][j+n]*WW_matrix[m][n]);
                }
            }
            arr_temp23[i][j]=sum_val23;
            sum_val23=0.0;
        }
    }
    double square_value23=0.0;
    double square_final23=0.0;
    for(int i=0;i<128;i++)
    {
        for(int j=0;j<128;j++)
        {
            square_value23=square_value23+(arr_temp23[i][j]*arr_temp23[i][j]);
        }
    }
    square_final23=square_value23/(128.0*128.0);
    energy_final[23]=square_final23;
    //-------for matrix 25-----//
        unsigned int arr_temp24[128][128];
      int sum_val24=0;
        for(int i=0;i<128;i++)
    {
        for(int j=0;j<128;j++)
        {
            for(int m=0;m<5;m++)
            {
                for(int n=0;n<5;n++)
                {
                    sum_val24=sum_val24+(arr2[i+m][j+n]*WR_matrix[m][n]);
                }
            }
            arr_temp24[i][j]=sum_val24;
            sum_val24=0.0;
        }
    }
    double square_value24=0.0;
    double square_final24=0.0;
    for(int i=0;i<128;i++)
    {
        for(int j=0;j<128;j++)
        {
            square_value24=square_value24+(arr_temp24[i][j]*arr_temp24[i][j]);
        }
    }
    square_final24=square_value24/(128.0*128.0);
    energy_final[24]=square_final24;
    return energy_final;
}
int main()
{
    FILE *file,*file2,*file1,*file3,*file4,*file5,*file6;

	if (!(file=fopen("Texture1.raw","rb"))) {
		cout << "Cannot open file: " << "Texture1.raw" <<endl;
		exit(1);
	}
	fread(text1 ,sizeof(unsigned char),128*128, file);
	fclose(file);
	if (!(file=fopen("Texture2.raw","rb"))) {
		cout << "Cannot open file: " << "Texture2.raw" <<endl;
		exit(1);
	}
	fread(text2, sizeof(unsigned char), 128*128, file);
	fclose(file);
	if (!(file=fopen("Texture3.raw","rb"))) {
		cout << "Cannot open file: " << "Texture3.raw" <<endl;
		exit(1);
	}
	fread(text3, sizeof(unsigned char), 128*128, file);
	if (!(file=fopen("Texture4.raw","rb"))) {
		cout << "Cannot open file: " << "Texture4.raw" <<endl;
		exit(1);
	}
	fread(text4, sizeof(unsigned char), 128*128, file);
	if (!(file=fopen("Texture5.raw","rb"))) {
		cout << "Cannot open file: " << "Texture5.raw" <<endl;
		exit(1);
	}
	fread(text5, sizeof(unsigned char), 128*128, file);
	fclose(file);
	if (!(file=fopen("Texture6.raw","rb"))) {
		cout << "Cannot open file: " << "Texture6.raw" <<endl;
		exit(1);
	}
	fread(text6, sizeof(unsigned char), 128*128, file);
	fclose(file);
	if (!(file=fopen("Texture7.raw","rb"))) {
		cout << "Cannot open file: " << "Texture7.raw" <<endl;
		exit(1);
	}
	fread(text7, sizeof(unsigned char), 128*128, file);
	fclose(file);
	if (!(file=fopen("Texture8.raw","rb"))) {
		cout << "Cannot open file: " << "Texture8.raw" <<endl;
		exit(1);
	}
	fread(text8, sizeof(unsigned char), 128*128, file);
	fclose(file);
	if (!(file=fopen("Texture9.raw","rb"))) {
		cout << "Cannot open file: " << "Texture9.raw" <<endl;
		exit(1);
	}
	fread(text9, sizeof(unsigned char), 128*128, file);
	fclose(file);
	if (!(file=fopen("Texture10.raw","rb"))) {
		cout << "Cannot open file: " << "Texture10.raw" <<endl;
		exit(1);
	}
	fread(text10, sizeof(unsigned char), 128*128, file);
	fclose(file);
	if (!(file=fopen("Texture11.raw","rb"))) {
		cout << "Cannot open file: " << "Texture11.raw" <<endl;
		exit(1);
	}
	fread(text11, sizeof(unsigned char), 128*128, file);
	fclose(file);
	if (!(file=fopen("Texture12.raw","rb"))) {
		cout << "Cannot open file: " << "Texture12.raw" <<endl;
		exit(1);
	}
	fread(text12, sizeof(unsigned char), 128*128, file);
	fclose(file);
	if (!(file=fopen("TextureA.raw","rb"))) {
		cout << "Cannot open file: " << "TextureA.raw" <<endl;
		exit(1);
	}
	fread(textA, sizeof(unsigned char), 128*128, file);
	fclose(file);
	if (!(file=fopen("TextureB.raw","rb"))) {
		cout << "Cannot open file: " << "TextureB.raw" <<endl;
		exit(1);
	}
	fread(textB, sizeof(unsigned char), 128*128, file);
	fclose(file);
	if (!(file=fopen("TextureC.raw","rb"))) {
		cout << "Cannot open file: " << "TextureC.raw" <<endl;
		exit(1);
	}
	fread(textC, sizeof(unsigned char), 128*128, file);
	fclose(file);
	if (!(file=fopen("TextureD.raw","rb"))) {
		cout << "Cannot open file: " << "TextureD.raw" <<endl;
		exit(1);
	}
	fread(textD, sizeof(unsigned char), 128*128, file);
	fclose(file);
	if (!(file=fopen("TextureE.raw","rb"))) {
		cout << "Cannot open file: " << "TextureE.raw" <<endl;
		exit(1);
	}
	fread(textE, sizeof(unsigned char), 128*128, file);
	fclose(file);
	if (!(file=fopen("TextureF.raw","rb"))) {
		cout << "Cannot open file: " << "TextureF.raw" <<endl;
		exit(1);
	}
	fread(textF, sizeof(unsigned char), 128*128, file);
	fclose(file);
mean(text1);
mean(text2);
mean(text3);
mean(text4);
mean(text5);
mean(text6);
mean(text7);
mean(text8);
mean(text9);
mean(text10);
mean(text11);
mean(text12);
mean(textA);
mean(textB);
mean(textC);
mean(textD);
mean(textE);
mean(textF);
unsigned char** text1_extend=boundary_extend(text1);
unsigned char** text2_extend=boundary_extend(text2);
unsigned char** text3_extend=boundary_extend(text3);
unsigned char** text4_extend=boundary_extend(text4);
unsigned char** text5_extend=boundary_extend(text5);
unsigned char** text6_extend=boundary_extend(text6);
unsigned char** text7_extend=boundary_extend(text7);
unsigned char** text8_extend=boundary_extend(text8);
unsigned char** text9_extend=boundary_extend(text9);
unsigned char** text10_extend=boundary_extend(text10);
unsigned char** text11_extend=boundary_extend(text11);
unsigned char** text12_extend=boundary_extend(text12);
unsigned char** textA_extend=boundary_extend(textA);
unsigned char** textB_extend=boundary_extend(textB);
unsigned char** textC_extend=boundary_extend(textC);
unsigned char** textD_extend=boundary_extend(textD);
unsigned char** textE_extend=boundary_extend(textE);
unsigned char** textF_extend=boundary_extend(textF);


 ofstream outfile,outfile1;
 outfile.open("E:/MATLAB2016/energy_feature_vector.csv");
 outfile1.open("E:/MATLAB2016/energy_feature_vector_test.csv");
 double feature[12][25];
 double feature_test[6][25];
double* energy_final1= energy_feature(text1_extend);
for(int i=0;i<25;i++)
{
    feature[0][i]=energy_final1[i];
}
double* energy_final2= energy_feature(text2_extend);
for(int i=0;i<25;i++)
{
    feature[1][i]=energy_final2[i];
}
double* energy_final3=  energy_feature(text3_extend);
for(int i=0;i<25;i++)
{
    feature[2][i]=energy_final3[i];
}
double* energy_final4=  energy_feature(text4_extend);
for(int i=0;i<25;i++)
{
    feature[3][i]=energy_final4[i];
}
double* energy_final5=  energy_feature(text5_extend);
for(int i=0;i<25;i++)
{
    feature[4][i]=energy_final5[i];
}
double* energy_final6=  energy_feature(text6_extend);
for(int i=0;i<25;i++)
{
    feature[5][i]=energy_final6[i];
}
double* energy_final7=  energy_feature(text7_extend);
for(int i=0;i<25;i++)
{
    feature[6][i]=energy_final7[i];
}
double* energy_final8=  energy_feature(text8_extend);
for(int i=0;i<25;i++)
{
    feature[7][i]=energy_final8[i];
}
double* energy_final9=  energy_feature(text9_extend);
for(int i=0;i<25;i++)
{
    feature[8][i]=energy_final9[i];
}
double* energy_final10= energy_feature(text10_extend);
for(int i=0;i<25;i++)
{
    feature[9][i]=energy_final10[i];
}
double* energy_final11= energy_feature(text11_extend);
for(int i=0;i<25;i++)
{
    feature[10][i]=energy_final11[i];
}
double* energy_final12= energy_feature(text12_extend);
for(int i=0;i<25;i++)
{
    feature[11][i]=energy_final12[i];
}

//-----------compute relative mean of test and train-------//
//double mean_test[25];
double mean_1[25];
double sum=0.0;
//double sum_test=0.0;
for(int i=0;i<25;i++)
{
    for(int j=0;j<12;j++)
    {
        sum=sum+feature[j][i];
    }
   /* for(int k=0;k<6;k++)
    {
        sum_test=sum_test+feature_test[k][i];
    }*/
    mean_1[i]=sum/12.0;
    //mean_test[i]=sum_test/6.0;
    sum=0.0;
    //sum_test=0.0;
}

//--------computing standard deviation----//
double var_table[25];
double sum_1=0.0;
//double sum_2=0.0;
//double var1_table[25];
for(int i=0;i<25;i++)
{
    for(int j=0;j<12;j++)
    {
        sum_1=sum_1+((feature[j][i]-mean_1[i])*(feature[j][i]-mean_1[i]));
    }
  /*  for(int k=0;k<6;k++)
    {
        sum_2=sum_2+((feature_test[k][i]-mean_test[i])*(feature_test[k][i]-mean_test[i]));
    }*/

    var_table[i]=sqrt(sum_1);
    //cout<<var_table[i]<<endl;
    sum_1=0.0;
    //var1_table[i]=sqrt(sum_2);
    //cout<<var_table[i]<<endl;
    //sum_2=0.0;
}
//------------Normalizing------------//
double feature_new[12][25];
for(int i=0;i<25;i++)
{
    for(int j=0;j<12;j++)
    {
        feature_new[j][i]=(feature[j][i]-mean_1[i])/var_table[i];

    }
}
//-------Writing into file---------//
for(int i=0;i<12;i++)
{
    for(int j=0;j<25;j++)
    {
        outfile<<feature_new[i][j]<<",";
        }
        outfile<<endl;
}
outfile.close();
//--------------K-Means Clustering--------//

double centroid1[25];
double centroid2[25];
double centroid3[25];
double centroid4[25];
//---randomly assigning 4 centroid values initially
for(int j=0;j<25;j++)
{
    centroid1[j]=feature_new[0][j];
    centroid2[j]=feature_new[3][j];
    centroid3[j]=feature_new[6][j];
    centroid4[j]=feature_new[9][j];
}

double centroid_new1[25];
double centroid_new2[25];
double centroid_new3[25];
double centroid_new4[25];
double min_dist[12];
double euclid1[12];
double euclid2[12];
double euclid3[12];
double euclid4[12];
int final_flag=0;
int n_vector[12];

double sum_c1[25],sum_c2[25],sum_c3[25],sum_c4[25];
int flag1=0;
int flag2=0;
int flag3=0;
int flag4=0;
double sum1=0.0;
double sum2=0.0;
double sum3=0.0;
double sum4=0.0;
int count_d1,count_d2,count_d3,count_d4;
int dummy=0;
while(final_flag!=1)
{

for(int i=0;i<12;i++)
{
    for(int j=0;j<25;j++)
    {
        //---computing euclidian distance with respect to the 4 centroids
        sum1=sum1+((feature_new[i][j]-centroid1[j])*(feature_new[i][j]-centroid1[j]));
        sum2=sum2+((feature_new[i][j]-centroid2[j])*(feature_new[i][j]-centroid2[j]));
        sum3=sum3+((feature_new[i][j]-centroid3[j])*(feature_new[i][j]-centroid3[j]));
        sum4=sum4+((feature_new[i][j]-centroid4[j])*(feature_new[i][j]-centroid4[j]));
    }
    euclid1[i]=sqrt(sum1);
    euclid2[i]=sqrt(sum2);
    euclid3[i]=sqrt(sum3);
    euclid4[i]=sqrt(sum4);
    min_dist[i]=min(euclid1[i],min(euclid2[i],min(euclid3[i],euclid4[i])));
     sum1=0.0;
    sum2=0.0;
    sum3=0.0;
    sum4=0.0;
}
cout<<"---------RESULT OF THE 12 TRAINED IMAGES------------"<<endl;
for(int i=0;i<12;i++)
{
    if(min_dist[i]==euclid1[i])
{
    count_d1++;
    //----updating the new centroids--//
    for(int j=0;j<25;j++)
    {
        sum_c1[j]=sum_c1[j]+feature_new[i][j];
    }
    n_vector[i]=1;
}
if(min_dist[i]==euclid2[i])
{
    count_d2++;
    for(int j=0;j<25;j++)
    {
        sum_c2[j]=sum_c2[j]+feature_new[i][j];
    }
     n_vector[i]=2;
}
if(min_dist[i]==euclid3[i])
{
    count_d3++;
    for(int j=0;j<25;j++)
     {
        sum_c3[j]=sum_c3[j]+feature_new[i][j];
    }
     n_vector[i]=3;

}
if(min_dist[i]==euclid4[i])
{
    count_d4++;
     for(int j=0;j<25;j++)
    {
        sum_c4[j]=sum_c4[j]+feature_new[i][j];
    }
     n_vector[i]=4;
}
}
for(int i=0;i<25;i++)
{
    centroid_new1[i]=sum_c1[i]/count_d1;
    sum_c1[i]=0;
    centroid_new2[i]=sum_c2[i]/count_d2;
    sum_c2[i]=0;
    centroid_new3[i]=sum_c3[i]/count_d3;
    sum_c3[i]=0;
    centroid_new4[i]=sum_c4[i]/count_d4;
    sum_c4[i]=0;
}
count_d1=0;
count_d2=0;
count_d3=0;
count_d4=0;

for(int i=0;i<25;i++)
{
    if(centroid_new1[i]==centroid1[i])
    {
        flag1=flag1+1;


    }
    centroid1[i]=centroid_new1[i];
       if(centroid_new2[i]==centroid2[i])
    {
        flag2=flag2+1;

    }
     centroid2[i]=centroid_new2[i];

    if(centroid_new3[i]==centroid3[i])
    {
        flag3=flag3+1;

    }
    centroid3[i]=centroid_new3[i];

    if(centroid_new4[i]==centroid4[i])
    {
        flag4=flag4+1;

    }
     centroid4[i]=centroid_new4[i];
}
    if(flag1==25&&flag2==25&&flag3==25&&flag4==25)
    {
        final_flag=1;
    }
    flag1=0;
    flag2=0;
    flag3=0;
    flag4=0;
    dummy++;

}
cout<<endl;
for(int i=0;i<12;i++)
{
    cout<<n_vector[i]<<endl;
}



//--------------Test image feature--------//
double* energy_finalA= energy_feature(textA_extend);
for(int i=0;i<25;i++)
{
    feature_test[0][i]=energy_finalA[i];
}
double* energy_finalB= energy_feature(textB_extend);
for(int i=0;i<25;i++)
{
    feature_test[1][i]=energy_finalB[i];
}
double* energy_finalC=  energy_feature(textC_extend);
for(int i=0;i<25;i++)
{
    feature_test[2][i]=energy_finalC[i];
}
double* energy_finalD=  energy_feature(textD_extend);
for(int i=0;i<25;i++)
{
    feature_test[3][i]=energy_finalD[i];
}
double* energy_finalE=  energy_feature(textE_extend);
for(int i=0;i<25;i++)
{
    feature_test[4][i]=energy_finalE[i];
}

double* energy_finalF=  energy_feature(textF_extend);
for(int i=0;i<25;i++)
{
    feature_test[5][i]=energy_finalF[i];
}
//-----------compute relative mean of test and train-------//
double mean_test[25];
double sum_test=0.0;
for(int i=0;i<25;i++)
{
    for(int j=0;j<6;j++)
    {
        sum_test=sum_test+feature_test[j][i];
    }
    mean_test[i]=sum_test/6.0;
    sum_test=0.0;

}

//--------computing standard deviation----//

double sum_2=0.0;
double var1_table[25];
for(int i=0;i<25;i++)
{
    for(int j=0;j<6;j++)
    {
        sum_2=sum_2+((feature_test[j][i]-mean_test[i])*(feature_test[j][i]-mean_test[i]));
    }

    var1_table[i]=sqrt(sum_2);
    sum_2=0.0;
}
//------------Normalizing------------//
//double feature_new[12][25];
double feature_new_test[6][25];
for(int i=0;i<25;i++)
{
    for(int j=0;j<6;j++)
    {
        feature_new_test[j][i]=(feature_test[j][i]-mean_test[i])/var1_table[i];

    }
}
for(int i=0;i<6;i++)
{
    for(int j=0;j<25;j++)
    {
        outfile1<<feature_new_test[i][j]<<",";
        }
        outfile1<<endl;
}
outfile1.close();
//-----Supervised classification-----//
double sum11=0.0;
double sum12=0.0;
double sum13=0.0;
double sum14=0.0;
double feature_first[25];
double feature_second[25];
double feature_third[25];
double feature_fourth[25];
for(int j=0;j<25;j++)
{
for(int i=0;i<3;i++)
    {
        sum11=sum11+feature_new[i][j];
    }
    feature_first[j]=sum11/3.0;
    sum11=0.0;
    for(int i=3;i<6;i++)
    {
        sum12=sum12+feature_new[i][j];
    }
    feature_second[j]=sum12/3.0;
    sum12=0.0;
    for(int i=6;i<9;i++)
    {
        sum13=sum13+feature_new[i][j];
    }
    feature_third[j]=sum13/3.0;
    sum13=0.0;
    for(int i=9;i<12;i++)
    {
        sum14=sum14+feature_new[i][j];
    }
    feature_fourth[j]=sum14/3.0;
    sum14=0.0;
}
//---------Testing the final 6 images both supervised and unsupervised--------------//
double euclid1_test;
double euclid2_test;
double euclid3_test;
double euclid4_test;
double euclid1_sup;
double euclid2_sup;
double euclid3_sup;
double euclid4_sup;
double sum1_test=0.0,sum2_test=0.0,sum3_test=0.0,sum4_test=0.0;
double sum1_sup=0.0,sum2_sup=0.0,sum3_sup=0.0,sum4_sup=0.0;
int n_vector_test[6];
double min_dist_test;
double min_dist_test1;
string n_vector_classify[6]="";
for(int i=0;i<6;i++)
{
    for(int j=0;j<25;j++)
    {
        sum1_test=sum1_test+((feature_new_test[i][j]-centroid_new1[j])*(feature_new_test[i][j]-centroid_new1[j]));
        sum2_test=sum2_test+((feature_new_test[i][j]-centroid_new2[j])*(feature_new_test[i][j]-centroid_new2[j]));
        sum3_test=sum3_test+((feature_new_test[i][j]-centroid_new3[j])*(feature_new_test[i][j]-centroid_new3[j]));
        sum4_test=sum4_test+((feature_new_test[i][j]-centroid_new4[j])*(feature_new_test[i][j]-centroid_new4[j]));
         sum1_sup=sum1_sup+((feature_new_test[i][j]-feature_first[j])*(feature_new_test[i][j]-feature_first[j]));
        sum2_sup=sum2_sup+((feature_new_test[i][j]-feature_second[j])*(feature_new_test[i][j]-feature_second[j]));
        sum3_sup=sum3_sup+((feature_new_test[i][j]-feature_third[j])*(feature_new_test[i][j]-feature_third[j]));
        sum4_sup=sum4_sup+((feature_new_test[i][j]-feature_fourth[j])*(feature_new_test[i][j]-feature_fourth[j]));
    }
    euclid1_test=sqrt(sum1_test);
    euclid2_test=sqrt(sum2_test);
    euclid3_test=sqrt(sum3_test);
    euclid4_test=sqrt(sum4_test);
    euclid1_sup=sqrt(sum1_sup);
    euclid2_sup=sqrt(sum2_sup);
    euclid3_sup=sqrt(sum3_sup);
    euclid4_sup=sqrt(sum4_sup);
    min_dist_test=min(euclid1_test,min(euclid2_test,min(euclid3_test,euclid4_test)));
    min_dist_test1=min(euclid1_sup,min(euclid2_sup,min(euclid3_sup,euclid4_sup)));
    cout<<"-------Result of the 6 test Images--------//"<<endl;
    if(min_dist_test==euclid1_test)
    {
        n_vector_test[i]=1;
       // n_vector_classify[i]="bark";
    }
    if(min_dist_test==euclid2_test)
    {
        n_vector_test[i]=2;
        //n_vector_classify[i]="sand";
    }
    if(min_dist_test==euclid3_test)
    {
        n_vector_test[i]=3;
    //  n_vector_classify[i]="grass";
    }
    if(min_dist_test==euclid4_test)
    {
        n_vector_test[i]=4;
      //   n_vector_classify[i]="straw";
    }    if(min_dist_test1==euclid1_sup)
    {
        n_vector_classify[i]="bark";

    }
    if(min_dist_test1==euclid2_sup)
    {
        n_vector_classify[i]="sand";
        //n_vector_classify[i]="sand";
    }
    if(min_dist_test1==euclid3_sup)
    {
        n_vector_classify[i]="straw";
    //    n_vector_classify[i]="grass";
    }
    if(min_dist_test1==euclid4_sup)
    {
        n_vector_classify[i]="grass";
         //n_vector_classify[i]="straw";
    }

    sum1_test=0.0;
    sum2_test=0.0;
    sum3_test=0.0;
    sum4_test=0.0;
    sum1_sup=0.0;
    sum2_sup=0.0;
    sum3_sup=0.0;
    sum4_sup=0.0;

}
cout<<endl;
for(int i=0;i<6;i++)
{
    cout<<n_vector_test[i]<<endl;
    cout<<n_vector_classify[i]<<endl;

}

	if (!(file5=fopen("pepper_extend_median.raw","wb"))) {
		cout << "Cannot open file: " << "pepper_extend_median.raw" << endl;
		exit(1);
	}
	for(int i=0;i<132;i++)
    fwrite(text1_extend[i], sizeof(unsigned char),   132
           , file5);
	printf("File written\n");
	fclose(file5);
    return 0;
}
