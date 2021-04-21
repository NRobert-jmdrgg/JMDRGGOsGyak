#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <errno.h>

#define KEY 123456L

typedef struct msgbuf {
    long mtype;      //message type
    char mtext[256]; //uzenet hossza legyen 256 byte
} messageBuffer;



void main() {
    key_t key = KEY;
    int messageId = msgget(key, IPC_CREAT | 0666);
    if (messageId == -1) {
        perror("\n Nem jott letre message queue!!\n");
        exit(-1);
    }
    printf("\nA letrehozott uzenetros idje : %d\n", messageId);
    
    messageBuffer message;
    messageBuffer *messagePointer = &message;

    messagePointer->mtype = 1;    //a kérés típusa 1
    strcpy(messagePointer->mtext, "Ez az elso uzenet");
    int messageLen = strlen(messagePointer->mtext) + 1;

    int messageReturn = msgsnd(messageId, messagePointer, messageLen, 0666 | IPC_CREAT);
    if (messageReturn == -1) {
        perror("\nNem sikerult kuldeni!!\n");
        exit(-1);
    }

    printf("Elkuldott uzenet: %s hossza : %d\n", messagePointer->mtext, messageLen);

    strcpy(messagePointer->mtext, "Ez a masodik uzenet");
    messageLen = strlen(messagePointer->mtext) + 1;

    messageReturn = msgsnd(messageId, messagePointer, messageLen, 0666 | IPC_CREAT);
    if (messageReturn == -1) {
        perror("\nNem sikerult kuldeni!!\n");
        exit(-1);
    }

    printf("Elkuldott uzenet: %s hossza : %d\n", messagePointer->mtext, messageLen);

    printf("Sikeres üzenetküldések !!\n");
}   
