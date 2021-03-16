#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]) 
{
    pid_t pid = fork();
    int status;
    if(pid < 0) 
    {
        perror("fork hiba"); 
    } 
    else if(pid == 0) 
    {
         exit(0);
    }
    
    if(wait(&status) != pid) 
    {
        perror("wait hiba"); 
    }

    pid = fork();

    if(WIFEXITED(status)) 
    {
        printf("Normális befejeződés, visszaadott érték = %d\n", WEXITSTATUS(status));
    }

    if(pid < 0) 
    {
        perror("fork hiba");
    } 
    else if (pid == 0) 
    {
        abort(); 
    }

    if(wait(&status) != pid) 
    {
        perror("wait hiba"); 
    }
    
    if(WIFSIGNALED(status)) 
    {
        printf("Abnormális befejeződés, a szignál sorszmáma = %d\n", WTERMSIG(status));
        return 0;
    }    
}
