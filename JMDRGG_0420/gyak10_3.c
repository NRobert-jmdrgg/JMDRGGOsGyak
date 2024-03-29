#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>

#define KEY 777777

void main() {
    
    pid_t process1; //foglalja le az osztott memoriat
    pid_t process2;
    pid_t process3;

    process1 = fork();
    if (process1 == 0) {
        
        int sharedMemoryId = shmget(KEY, 256, IPC_CREAT | 0666);
        if (sharedMemoryId == -1) {
            perror("Nem sikerult lefoglalni a memoriat\n");
            exit(-1);
        }
        printf("Processz 1 lefoglalta a memoriat!\n");
    } else {
        process2 = fork();
        if (process2 == 0) {
            printf("Process 2 olvas\n");
            int sharedMemoryId = shmget(KEY, 0, 0);
            char *s = shmat(sharedMemoryId, NULL, SHM_RND);
            strlen(s) > 0 ? printf("osztott memoriaban szereplo szoveg : %s\n", s) : printf("Nincs benne szoveg\n");
            //beleirunk
            strcpy(s, "Ez egy uj szoveg");
            printf("process2 kuldte az uzenetet\n");
        } else {
            process3 = fork();
            if (process3 == 0) {
                printf("process3: \n");
                int sharedMemoryId = shmget(KEY, 0, 0);
                struct shmid_ds buffer;
                if (shmctl(sharedMemoryId, IPC_STAT, &buffer) == -1) {
                    perror("Nem sikerult lekerdezni\n");
                    exit(-1);
                }
                printf("Szegmens merete : %ld\n", buffer.shm_segsz);
                printf("utolso operaciot kiado processz pidje : %d\n", buffer.shm_lpid);
                

            }
        }
    }
    
       

    
}