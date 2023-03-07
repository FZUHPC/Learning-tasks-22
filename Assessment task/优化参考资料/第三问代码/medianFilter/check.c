#include <stdio.h>
#include<math.h>
int main()
{
    printf("CHECK:\n");
    
    FILE * f1;
    FILE * f2;
    f1 = fopen("output.txt","r");
    f2 = fopen("answer.txt","r");
    
    int lop = 0;
    int x1;
    int x2;
    
    fscanf(f1,"%d",&x1);
    fscanf(f2,"%d",&x2);
    
    while(!feof(f1) && !feof(f2)){       
        if(x1!=x2){		
            lop = 1;
            break;
        }
        fscanf(f1,"%d",&x1);
        fscanf(f2,"%d",&x2);
    }
    
    if(lop==0) printf("-RIGHT-\n");
    else printf("-WRONG-\n");
    fclose(f1);
    fclose(f2);
}
