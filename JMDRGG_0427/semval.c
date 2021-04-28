	
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

    printf("Szemaforok tartalma: \n");

    for (int i = 0; i < 5; i++) {
        printf("%d ", semctl(semID, i, GETVAL));
    }   
}
