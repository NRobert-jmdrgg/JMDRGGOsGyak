#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define CSONEV "FIFO"

/*
    6. Irjon C nyelvu programokat, ami
    letrehoz egy nevesitett csovezeteket (bejegyzes az fs-en)
    megnyitja
    olvasni probal belole
    kozben egy masik program ir bele egy random szamot
    az elso program kiirja a kapott szamot es visszakuldi ennek a duplajat
    a masik program kiolvassa es kiirja a kepernyore
    a processzek megszunnek es a masodik program eltunteti a nevesitett csovezeteket"

    Hatarido : maj 11.
*/

void olvasMajdVisszair(int);

void main() {
    int pipe;
    //megnezi, hogy nincs fifo, ennek normalis mukodeskor teljesulnie kell. Ha mar van akkor nem hoz letre ujjat.
    if (access(CSONEV, F_OK)) {
        pipe = mkfifo(CSONEV, S_IFIFO | 0666);
    }    
    
    int fd = open(CSONEV, O_RDWR);
    if (fd == -1) {
        perror("Szerver : nem sikerult megnyitni \n");
        exit(-1);
    }
    
    olvasMajdVisszair(fd);
    close(fd);
    printf("\nbefejezve\n");
    
    unlink(CSONEV);
    
}

void olvasMajdVisszair(int fd) {
    int val = 0;

    printf("szerver olvas..\n");
    if (read(fd, &val, sizeof(val)) > 0) {
        printf("szerver megkapta : %d \n", val);
    } else {
        perror("Szerver : nem sikerult olvasni\n");
        exit(-1);
    }
    val *= 2;
    if (write(fd, &val, sizeof(val)) < 0) {    
        perror("Szerver(2) : nem sikerult irni\n");
        exit(-1);
    }    
}
