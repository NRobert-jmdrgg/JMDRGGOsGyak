#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]) 
{
    char parancs[50];
    printf("Adj meg egy parancsot: ");
    scanf("%s", parancs);
    
    int x = system(parancs);

    if(WIFEXITED(x)) 
    {
        printf("Kilepett\n");
    } 
    WEXITSTATUS(x) ? printf("Hibas mukodes \n") : printf("Normalis mukodes ");
    
    return 0;
}
