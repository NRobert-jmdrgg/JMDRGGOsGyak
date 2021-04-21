#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define KEY 777

typedef struct msgbuf {
    long mtype;
    char mtext[128];
} messageBuffer;

void main() {
    pid_t childPid;
    key_t key = KEY;

    childPid = fork();
    if (childPid == 0) {
        messageBuffer message;
        messageBuffer *messagePointer;
        
        messagePointer = &message;
        messagePointer->mtype = 1; // csak irunk
        
        int messageID = msgget(key, IPC_CREAT | 0666);
        if (messageID == -1) {
            perror("Nem sikerult letrehozni\n");
            exit(-1);
        }

        int messageReturn;
        int messageLen;
        char *messages[] = {"elso uzenet", "masodik uzenet", "harmadik uzenet"};

        for (int i = 0; i < 3; i++) {
            strcpy(messagePointer->mtext, messages[i]);
            messageLen = strlen(messagePointer->mtext) + 1;

            messageReturn = msgsnd(messageID, messagePointer, messageLen, IPC_CREAT | 0666);
            if (messageReturn == -1) {
                perror("Nem sikerult kuldeni\n");
                exit(-1);
            }

            printf("Gyerek kuldte : %s\n", messagePointer->mtext);
        }
        
        exit(0);
    } else {
        struct msqid_ds desciptor;
        struct msqid_ds *buffer;
        messageBuffer recieveMessage;
        messageBuffer *messagePointer;
        messagePointer = &recieveMessage;
        buffer = &desciptor;

        int messageFlag = 0666 | IPC_CREAT | MSG_NOERROR;
        int messageLen = 20;
        int messageType = 0;
        int messageReturn;
        int messageID = msgget(key, IPC_CREAT | 0666);

        if (messageID == -1) {
            perror("Nem sikerult letrehozni\n");
            exit(-1);
        }

        messageReturn = msgctl(messageID, IPC_STAT, buffer);
        if (messageReturn == -1) {
            perror("Nem sikerult megkapni az uzenetet\n");
            exit(-1);
        }

        while (buffer->msg_qnum) {
            messageReturn = msgrcv(messageID, messagePointer, messageLen, messageType, messageFlag);
            if (messageReturn == -1) {
                perror("\nNem sikerult olvasni\n");
                exit(-1);
            }

            printf("Olvasott uzenet : %s", messagePointer->mtext);
        }
    }

    int messageID = msgget(key, IPC_CREAT | 0666);
    int messageReturn = msgctl(messageID, IPC_RMID, NULL);
    if (messageID == -1) {
        perror("Nem sikerult kitorolni \n");
        exit(-1);
    }
    
}
