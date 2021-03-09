#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]) {
    
    pid_t pid = fork();
    if(pid == 0) {
        if(execlp("ls", "ls", (char *) NULL) < 0) {
            perror("execl error");
        }
    } 

    if(waitpid(pid, NULL, 0) < 0) {
        perror("wait error");
    }
        

    return 0;
}
