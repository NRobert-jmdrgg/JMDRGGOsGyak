#include <unistd.h>
#include <signal.h>
#include <stdio.h>

int main(int argc, char const *argv[]) {
    //gyerek
    pid_t pid;
    pid = fork();

    while (1) {
        
        sleep(10);
    }

    if (fork() == 0) {

    }

    return 0;
}
