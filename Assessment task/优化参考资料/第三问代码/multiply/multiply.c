#include<stdio.h>
#include<omp.h>
#include<stdlib.h>
#include<math.h>

const int N = 500;

double a[500][500];
double b[500][500];
double c_0[500][500];
double c[500][500];

int main(){

//---------------读取数据---------------------------// 
	FILE* f1;
	FILE* f2;
	FILE* out;
		
	f1 = fopen("data_a.txt", "r");
	f2 = fopen("data_b.txt", "r");
	out = fopen("data_c.txt", "w");
	
	for(int i=1;i<N;i++)
		for(int j=1;j<N;j++){
			fscanf(f1,"%lf",&a[i][j]);
			fscanf(f2,"%lf",&b[i][j]);
		}
//--------------------------------------------------//	

	double t0,t1;
	double T0,T1;
	
	
//--------------初始矩阵乘法运算--------------------// 
	t0 = omp_get_wtime();
	//mul
	for(int i=1;i<N;i++)
		for(int j=1;j<N;j++)
			for(int k=1;k<N;k++)
				c_0[i][j] += a[i][k]*b[k][j];
	
	t1 = omp_get_wtime();
	
	T0 = (t1-t0)*1000;
	printf("初始矩阵乘法运行耗时: %f ms\n", T0);
//---------------------------------------------------//	



	t0 = omp_get_wtime();
	
//-----------优化矩阵乘法运算（需修改部分）-----------// 
//--------------- c = a * b -------------------------//
	
	for(int i=1;i<N;i++)
		for(int j=1;j<N;j++)
			for(int k=1;k<N;k++)
				c[i][j] += a[i][k]*b[k][j];
	
//--------------------------------------------------//	

	t1 = omp_get_wtime();
	
	T1 = (t1-t0)*1000;
	printf("优化后矩阵乘法运行耗时: %f ms\n", T1);	

	printf("加速比为：%f\n",T0/T1);

//----------------数据输出---------------------------// 
	for(int i=1;i<N;i++)
		for(int j=1;j<N;j++)
			fprintf(out,"%lf\n",c[i][j]);
//---------------------------------------------------//			
			
	fclose(f1);
	fclose(f2);
	fclose(out);			
}
