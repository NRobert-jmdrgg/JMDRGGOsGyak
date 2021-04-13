/*
1. Készítsen C nyelvű programot, ahol egy szülő processz létrehoz egy csővezetéket, a gyerek
processz beleír egy szöveget a csővezetékbe (A kiírt szöveg: XY neptunkod), a szülő processz
ezt kiolvassa, és kiírja a standard kimenetre.
*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main(void) {
    int nbytes;
    pid_t   childpid;
    char    string[] = "XY jmdrgg\n";
    char    readbuffer[80];
    int     fd[2];
    
    if((childpid = fork()) == -1) {
            perror("fork");
            exit(1);
    }

    if(childpid == 0) {
        close(fd[0]);
        write(fd[1], string, (strlen(string)+1));
        exit(0);
    } else {      
        pipe(fd);
        close(fd[1]);
        nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
        printf("Received string: %s", readbuffer);
    }
    
    return(0);
}