#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]) 
{
    int x = system("ls");
    
    if(WIFEXITED(x)) 
    {
        printf("Kilepett\n");
        printf("Visszateresi ertek: %d\n", WEXITSTATUS(x));
    } 

    int y = system("lp"); // nem létező parancs
    
    if(WIFEXITED(y)) 
    {
        printf("Kilepett\n");
        printf("Visszateresi ertek: %d\n", WEXITSTATUS(y));
    }

    return 0;
}
