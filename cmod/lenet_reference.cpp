#include<opencv2/opencv.hpp> 
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<math.h>

using namespace cv;
using namespace std;
void softmax(double *connect2,int input_len);


int main()
{
	Mat df;
	int i,j,k,l,n,m,o;
	double ip2[10][500];
	double conv2[50][20][5][5];
	double conv1[20][5][5];
	double ip1[500][800];
	
	double ip2_bias[10];
	double conv2_bias[50];
	double conv1_bias[20];
	double ip1_bias[500];
	
	char trash[100];
	char trash1;

	int  trash2;
	double ***p;
	double ***p1;
	double ***p2;
	double ***p3;
	double ***p4;
	double max1;
	double max2;
	
	

	
	

	
	df=imread("/home/socmgr/caffe/11.jpg",IMREAD_COLOR); //이미지 파일 불러오
	if(df.empty())
	{
		cout<<"could not open or find the image"<<endl;
		return -1;
	}

	Mat image;
	cvtColor(df,image, COLOR_BGR2GRAY);



	//bias 불러오기

	FILE *fp2=fopen("/home/socmgr/opencv-3.4.2/lenet_bias.txt","r");
	if(fp2==NULL)
	{
		printf("err -end \n");
		return -1;
	}
	fscanf(fp2,"%s",trash);
	fscanf(fp2,"%s",trash);
	
	fscanf(fp2,"%c",&trash1);
	fscanf(fp2,"%c",&trash1);
	fscanf(fp2,"%d",&trash2);
	fscanf(fp2,"%c",&trash1);
	fscanf(fp2,"%d",&trash2);
	fscanf(fp2,"%c",&trash1);
	fscanf(fp2,"%s",trash);
	fscanf(fp2,"%c",&trash1);
	fscanf(fp2,"%c",&trash1);
	
	
	for(i=0;i<10;i++)
	{
		fscanf(fp2,"%lf",&ip2_bias[i]);
		fscanf(fp2,"%c",&trash1);
	}
	
	fscanf(fp2,"%s",trash);
	fscanf(fp2,"%s",trash);
	
	fscanf(fp2,"%c",&trash1);
	fscanf(fp2,"%c",&trash1);
	fscanf(fp2,"%d",&trash2);
	fscanf(fp2,"%c",&trash1);
	fscanf(fp2,"%d",&trash2);
	fscanf(fp2,"%c",&trash1);
	fscanf(fp2,"%s",trash);
	fscanf(fp2,"%s",trash);
	fscanf(fp2,"%s",trash);
	fscanf(fp2,"%c",&trash1);
	fscanf(fp2,"%c",&trash1);
	

	
	for(i=0;i<50;i++)
	{
		fscanf(fp2,"%lf",&conv2_bias[i]);
		fscanf(fp2,"%c",&trash1);
		
	}



	fscanf(fp2,"%s",trash);
	fscanf(fp2,"%s",trash);
	
	fscanf(fp2,"%c",&trash1);
	fscanf(fp2,"%c",&trash1);
	fscanf(fp2,"%d",&trash2);
	fscanf(fp2,"%c",&trash1);
	fscanf(fp2,"%d",&trash2);
	fscanf(fp2,"%c",&trash1);
	fscanf(fp2,"%s",trash);
	fscanf(fp2,"%s",trash);
	fscanf(fp2,"%s",trash);
	fscanf(fp2,"%c",&trash1);
	fscanf(fp2,"%c",&trash1);
	
	for(i=0;i<20;i++)
	{
		fscanf(fp2,"%lf",&conv1_bias[i]);
		fscanf(fp2,"%c",&trash1);
		
	}
	

	fscanf(fp2,"%s",trash);
	fscanf(fp2,"%s",trash);
	
	fscanf(fp2,"%c",&trash1);
	fscanf(fp2,"%c",&trash1);
	fscanf(fp2,"%d",&trash2);
	fscanf(fp2,"%c",&trash1);
	fscanf(fp2,"%d",&trash2);
	fscanf(fp2,"%c",&trash1);
	fscanf(fp2,"%s",trash);
	fscanf(fp2,"%s",trash);
	fscanf(fp2,"%s",trash);
	fscanf(fp2,"%c",&trash1);
	fscanf(fp2,"%c",&trash1);
	
	for(i=0;i<500;i++)
	{
		fscanf(fp2,"%lf",&ip1_bias[i]);
		fscanf(fp2,"%c",&trash1);
		
	}
	







	//weight 불러오기 


	FILE *fp5=fopen("/home/socmgr/opencv-3.4.2/lenet_conv1_weight.txt","r");
	if(fp5==NULL)
	{
		printf("1err -end \n");
		return -1;
	}
	for(i=0;i<20;i++)
	{
			for(k=0;k<5;k++)
			{
				for(l=0;l<5;l++)
				{
				fscanf(fp5,"%lf",&conv1[i][k][l]);
				}
			}
	}
	fclose(fp5);


	FILE *fp6=fopen("/home/socmgr/opencv-3.4.2/lenet_conv2_weight.txt","r");
	if(fp6==NULL)
	{
		printf("2err -end \n");
		return -1;
	}
	for(i=0;i<50;i++)
	{
		for(j=0;j<20;j++)
		{
			for(k=0;k<5;k++)
			{
				for(l=0;l<5;l++)
				{
				fscanf(fp6,"%lf",&conv2[i][j][k][l]);
				}
			}
		}
	}
	fclose(fp6);

	FILE *fp7=fopen("/home/socmgr/opencv-3.4.2/lenet_ip1_weight.txt","r");
	if(fp7==NULL)
	{
		printf("3err -end \n");
		return -1;
	}
	
			for(i=0;i<500;i++)
			{
				for(j=0;j<800;j++)
				{
				fscanf(fp7,"%lf",&ip1[i][j]);
				}
			}

	fclose(fp7);

	
	FILE *fp8=fopen("/home/socmgr/opencv-3.4.2/lenet_ip2_weight.txt","r");
	if(fp8==NULL)
	{
		printf("4err -end \n");
		return -1;
	}
	
			for(i=0;i<10;i++)
			{
				for(j=0;j<500;j++)
				{
				fscanf(fp8,"%lf",&ip2[i][j]);
				}
			}
	

	fclose(fp8);

	int f_size=5;
	int filter_num=20;
	int channel=1;
	int stride=1;
	
	//input image
	
	
	
	p=(double***)malloc(filter_num*sizeof(double**));//3차원 배열 동적할당

	for(i=0;i<filter_num;i++)	
	{
		*(p+i)=(double**)malloc(image.rows*sizeof(double*));
			for(j=0;j<image.rows;j++)
			{
				*(*(p+i)+j)=(double*)malloc(image.cols*sizeof(double));
			}
	}

	



      
	for(i=0;i<filter_num;i++)
	{
		for(j=0;j<image.rows;j++)
		{
			for(k=0;k<image.cols;k++)
			{	
					p[i][j][k]=255-image.at<uchar>(j,k);	
						
			}
			
		}
	     	
	}
	
	int orsize=((image.rows-f_size)/stride)+1;
	int ocsize=((image.cols-f_size)/stride)+1;


	p1=(double***)malloc(filter_num*sizeof(double**));//3차원 배열 동적할당
	for(i=0;i<filter_num;i++)	
	{
		*(p1+i)=(double**)malloc(orsize*sizeof(double*));
			for(j=0;j<orsize;j++)
			{
				*(*(p1+i)+j)=(double*)malloc(ocsize*sizeof(double));
			}
	}
	

	

	

	 for(n=0;n<filter_num;n++)
	{
				for(i=0;i<orsize;i++)
				{
					for(j=0;j<ocsize;j++)
					{
						
					p1[n][i][j]=0;
							 
					}
					
				}  
				
	}
	//convolution 1

	 for(m=0;m<filter_num;m++)
	{	
	
			for(i=0;i<orsize;i++)
			{
				for(j=0;j<ocsize;j++)
				{
					for(k=0;k<f_size;k++)
					{
						for(l=0;l<f_size;l++)
						{
							p1[m][i][j]+=(p[m][(i*stride)+k][(j*stride)+l])*conv1[m][k][l];
				
						}
							
					}			
                                       p1[m][i][j]=p1[m][i][j]+conv1_bias[m];
				}
				
				
			}
		
	}
	
	//max_pooling1

	int stride_pooling1=2;
	int f_size_pooling1=2;



	int p_rsize=(orsize-f_size_pooling1)/stride_pooling1+1;
	int p_csize=(ocsize-f_size_pooling1)/stride_pooling1+1;


	p2=(double***)malloc(filter_num*sizeof(double**));

	for(i=0;i<filter_num;i++)
	{
		*(p2+i)=(double**)malloc(p_rsize*sizeof(double*));
		for(j=0;j<p_rsize;j++)
		{
			*(*(p2+i)+j)=(double*)malloc(p_csize*sizeof(double));
		}	
	}

	

	 for(m=0;m<filter_num;m++)
	{	
	
			for(i=0;i<p_rsize;i++)
			{
				for(j=0;j<p_csize;j++)
				{
					max1 = INT_MIN;
					for(k=0;k<f_size_pooling1;k++)
					{
						for(l=0;l<f_size_pooling1;l++)
						{
							if(max1<p1[m][(i*stride_pooling1)+k][(j*stride_pooling1)+l])
							{
							max1=(p1[m][(i*stride_pooling1)+k][(j*stride_pooling1)+l]);
							p2[m][i][j]=max1;
							
							}
						}
							
					}			
                                         
				}
					
				 
			}
		
	}
	
	//convolution2
	
	filter_num=50;
	stride=1;
	f_size=5;
	int channel2=20;
	

	int orsize2=((p_rsize-f_size)/stride)+1;
	int ocsize2=((p_csize-f_size)/stride)+1;

	
	filter_num=50;
	p3=(double***)malloc(filter_num*sizeof(double**));//3차원 배열 동적할당
	for(i=0;i<filter_num;i++)	
	{
		*(p3+i)=(double**)malloc(orsize2*sizeof(double*));
			for(j=0;j<orsize2;j++)
			{
				*(*(p3+i)+j)=(double*)malloc(ocsize2*sizeof(double));
			}
	}
	
	
	 for(n=0;n<filter_num;n++)
	{
	
				for(i=0;i<orsize2;i++)
				{
					for(j=0;j<ocsize2;j++)
					{
							p3[n][i][j]=0;
							 
					}
					
				}	  
				
	}
	
	
	 for(n=0;n<filter_num;n++)
	{

	 	for(m=0;m<channel2;m++)
		{	
	
				for(i=0;i<orsize2;i++)
				{
					for(j=0;j<ocsize2;j++)
					{
						for(k=0;k<f_size;k++)
						{
							for(l=0;l<f_size;l++)
							{
							p3[n][i][j]+=(p2[m][(i*stride)+k][(j*stride)+l])*conv2[n][m][k][l];
							}
								
						}
					p3[n][i][j]=p3[n][i][j]+conv2_bias[n];		 
					}
					
					
				}	  
				
		}
	}
	
	//max pooling2

	

	int stride_pooling2=2;
	int f_size_pooling2=2;
	
	int p_rsize2=(orsize2-f_size_pooling2)/stride_pooling2+1;
	int p_csize2=(ocsize2-f_size_pooling2)/stride_pooling2+1;


	p4=(double***)malloc(filter_num*sizeof(double**));

	for(i=0;i<filter_num;i++)
	{
		*(p4+i)=(double**)malloc(p_rsize2*sizeof(double*));
		for(j=0;j<p_rsize2;j++)
		{
			*(*(p4+i)+j)=(double*)malloc(p_csize2*sizeof(double));
		}	
	}

	


	 for(m=0;m<filter_num;m++)
	{	
	
			for(i=0;i<p_rsize2;i++)
			{
				for(j=0;j<p_csize2;j++)
				{
					max2 = INT_MIN;
					for(k=0;k<f_size_pooling2;k++)
					{
						for(l=0;l<f_size_pooling2;l++)
						{
							if(max1<p3[m][(i*stride_pooling2)+k][(j*stride_pooling2)+l])
							{
							max2=(p3[m][(i*stride_pooling2)+k][(j*stride_pooling2)+l]);
							p4[m][i][j]=max2;
							
							}
						}
							
					}			
                                         
				}
					
				 
			}
		
	}
	//connect

	double move_connect1[800];
	double connect1[500];
	int count=0;

	double connect2[10];

	for(i=0;i<filter_num;i++)
	{
		
			for(k=0;k<p_rsize2;k++)
			{
				for(l=0;l<p_csize2;l++)
				{
					move_connect1[count]=p4[i][k][l];
					count++;
				}
				
			}
	}
	
	
	
	for(i=0;i<500;i++)
	{
		for(j=0;j<800;j++)
		{
			connect1[i]+=ip1[i][j]*move_connect1[j];
		}
		connect1[i]=connect1[i]+ip1_bias[i];
	}


	
	for(i=0;i<500;i++)
	{
		if(connect1[i]<0)
		connect1[i]=0;
	}
	

	for(i=0;i<10;i++)
	{
		for(j=0;j<500;j++)
		{
		connect2[i]+=connect1[j]*ip2[i][j];
		}
		connect2[i]=connect2[i]+ip2_bias[i];
	}

	for(i=0;i<10;i++)
	{
		printf("\n%lf\n",connect2[i]);
	}
	
	
	int number=10;
	softmax(connect2,number);


	for(i=0;i<20;i++)//할당해제
	{
		for(j=0;j<image.rows;j++)
		{
			
			free(*(*(p+i)+j));
		}
		free(*(p+i));
	}
	free(p);


	for(i=0;i<20;i++)//할당해제
	{
		for(j=0;j<orsize;j++)
		{
			
			free(*(*(p1+i)+j));
		}
		free(*(p1+i));
	}
	free(p1);

	for(i=0;i<20;i++)//할당해제
	{
		for(j=0;j<p_rsize;j++)
		{
			
			free(*(*(p2+i)+j));
		}
		free(*(p2+i));
	}
	free(p2);

	for(i=0;i<50;i++)//할당해제
	{
		for(j=0;j<orsize2;j++)
		{
			
			free(*(*(p3+i)+j));
		}
		free(*(p3+i));
	}
	free(p3);


	for(i=0;i<50;i++)//할당해제
	{
		for(j=0;j<p_rsize2;j++)
		{
			
			free(*(*(p4+i)+j));
		}
		free(*(p4+i));
	}
	free(p4);
}
void softmax(double *connect2,int input_len)
{
	double sum_exp_input;

	double q=-INFINITY;
	for(size_t i=0;i<input_len;i++)
	{
		if(connect2[i]>q)
		q=connect2[i];
	}

	double exp_input[input_len]={};
	
	for(int i=0;i<input_len;i++)
	{
		exp_input[i]=exp(connect2[i]-q);
	}
	for(int i=0;i<input_len;i++)
	{
		sum_exp_input+=exp_input[i];
	}
	double y[10];
	
	for(int i=0;i<input_len;i++)
	{
		y[i]=(exp_input[i])/sum_exp_input;
	}
	
	for(int i=0;i<10;i++)
	{
		printf("\n\n%d 결과: %lf \n",i,y[i]);
	}
}
	

	

	


	


