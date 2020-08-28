#include <stdio.h>
int main (void){
int i=0,a=0,b=0;
int V[15];
for (i=0;i<15;i++)
    {
    scanf("%d",&V[i]);
    }

for (i=0;i<15;i++)
{
    if(V[i]%2 == 0)
    {
     printf("par[%d] = %d\n",a,V[i]);
     a++;
        if (a==5)
        {
            a = 0;
            break;
        }
    }
}


for (i=0;i<15;i++)
{
    if(V[i]%2 != 0)
    {
     printf("impar[%d] = %d\n",b,V[i]);
     b++;
        if (b==5)
            {
             b = 0;
             break;
            }
    }
}
























return 0;
}
