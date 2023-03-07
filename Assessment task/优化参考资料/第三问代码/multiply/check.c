#include <stdio.h>
#include<math.h>
int main()
{
    printf("CHECK:\n");
    
    FILE * f1;
    FILE * f2;
    f1 = fopen("data_result.txt","r");
    f2 = fopen("data_c.txt","r");
    
    int lop = 0;
    double x1;
    double x2;
    
    fscanf(f1,"%lf",&x1);
    fscanf(f2,"%lf",&x2);
    
    while(!feof(f1) && !feof(f2)){       
        if(fabs(x1-x2) > 0.01){		
            lop = 1;
            break;
        }
        fscanf(f1,"%lf",&x1);
        fscanf(f2,"%lf",&x2);
    }
    
    if(lop==0) printf("-RIGHT-\n");
    else printf("-WRONG-\n");
    fclose(f1);
    fclose(f2);
}
