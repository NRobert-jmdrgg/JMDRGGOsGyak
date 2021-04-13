
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main(void) {
    int f = mkfifo("szerverfifo", S_IFIFO|0666);
    if (f == -1) {
        perror("Nem jott letre a nevesitett pipe");
    }
    return(0);
}