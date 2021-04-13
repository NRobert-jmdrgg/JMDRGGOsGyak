#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <signal.h>

void main() {
    signal(SIGALRM, handleSigalarm);
    pause();
    printf("kibillent");
    exit(0);
}

void handleSigalarm() {
    printf("jmdrgg");
    exit(1);
}
