#include<stdio.h>
#include<omp.h>

const int N = 200000;
 
void medianFilter(int height,int width,unsigned char* __restrict__ src,unsigned char* __restrict__ dst){
	for(int i=1;i<height-1;i++){
		for(int j=1;j<width-1;j++){
			unsigned char a[9];
			a[0] = src[i*width+j];
			a[1] = src[i*width+j+1];
			a[2] = src[i*width+j-1];
			a[3] = src[(i+1)*width+j];
			a[4] = src[(i+1)*width+j+1];
			a[5] = src[(i+1)*width+j-1];
			a[6] = src[(i-1)*width+j];
			a[7] = src[(i-1)*width+j+1];
			a[8] = src[(i-1)*width+j-1];
			for(int ji=0;ji<5;ji++){
				for(int jj=ji+1;jj<9;jj++){
					if(a[ji] > a[jj]){
						unsigned char tmp = a[ji];
						a[ji] = a[jj];
						a[jj] = tmp;
					}
				}
			}
			dst[i*width+j] = a[4];
		}
	}
	for(int i=0;i<width;i++){
		dst[i] = src[i]; // first now
		dst[(height-1)*width+i] = src[(height-1)*width+i];
	}
	for(int i=0;i<height;i++){
		dst[i*width] = src[i*width];
		dst[i*width+width-1] = src[i*width+width-1];
	}
}


int main(){
    int height,width;
    unsigned char src[N];
    unsigned char dst[N];
    
// 数据读入
    FILE * f1;		
    f1 = fopen("input.txt","r");
    for(int i=1;i<N;i++){
    	fscanf(f1,"%d",&src[i]);
    }
    fclose(f1);
	
//计时区
    double t0,t1;
    t0 = omp_get_wtime();
    medianFilter(400,400,src,dst);             // mian
    t1 = omp_get_wtime();
    printf("运行耗时: %f ms\n", (t1-t0)*1000);

// 数据输出	
    FILE * out;		
    out = fopen("output.txt","w");
    for(int i=1;i<N;i++){
    	fprintf(out,"%d\n",dst[i]);
    }
    fclose(out);
}
