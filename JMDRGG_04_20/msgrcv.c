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

    messageBuffer recieveBuffer;
    messageBuffer *messagePointer;
    messagePointer = &recieveBuffer;


    int messageFlag = 0666 | IPC_CREAT | MSG_NOERROR;

    int messageID = msgget(key, messageFlag);
    if (messageID == -1) {
        perror("Nem sikerult letrehozni\n");
        exit(-1);
    }
    printf("Letrejott uzenet %d\n", messageID);

    struct msqid_ds descriptor, *buffer;

    buffer = &descriptor;
    int messageLen = 20;
    int messageType = 0; //minden tipus lehet
    int messageReturn = msgctl(messageID, IPC_STAT, buffer);
    if (messageReturn == -1) {
        perror("Nem sikerult megkapni az uzenetet\n");
        exit(-1);
    }

    printf("A megkapott üzenetek szama: %ld", buffer->msg_qnum);

    while (buffer->msg_qnum) {
        messageReturn = msgrcv(messageID, messagePointer, messageLen, messageType, messageFlag);
        if (messageReturn == -1) {
            perror("Nem sikerult megkapni az uzenetet\n");
            exit(-1);
        }

        printf("Megkapott uzenet : %s", messagePointer->mtext);
    }   
}
