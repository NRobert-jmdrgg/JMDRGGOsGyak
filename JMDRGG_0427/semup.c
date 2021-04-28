	
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
#define KEY 123456L

void main() {
    int semID = semget(KEY, 0, 0);
    if (semID == -1) {
        perror("Nem sikerult szemaforokat lekerdezni\n");
        exit(-1);
    }

    struct sembuf buffer;
    struct sembuf *op;

    int n = 5;

    int numberOfOperations = 1;
    buffer.sem_flg = 0666;
    buffer.sem_num = 0;
    buffer.sem_op = 1;

    op = &buffer;

    if (semop(semID, op, numberOfOperations) != 0) {
        perror("Sikertelen\n");
        exit(-1);
    }
}