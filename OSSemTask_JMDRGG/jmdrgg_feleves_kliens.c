#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

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

int getRandom(void);
void kliensIr(int fd);
void kliensOlvas(int fd);

void main() {
    srand(time(0));
    
    int fd = open(CSONEV, O_RDWR);
    if (fd == -1) {
        perror("Szerver : nem sikerult megnyitni \n");
        exit(-1);
    }
    
    printf("kliens indul...\n");
    kliensIr(fd);
    kliensOlvas(fd);
    close(fd);   
    unlink(CSONEV);
    
}

void kliensIr(int fd) {
    int n = getRandom();
    if (write(fd, &n, sizeof(int)) == -1) {
        perror("kliens : Nem sikerult irni\n");
        exit(-1);
    } 
    printf("kliens : irva\n");
    
}

void kliensOlvas(int fd) {    
    int val;
    printf("kliens olvas...\n");
    if (read(fd, &val, sizeof(val)) < 0) {
        perror("kliens : Nem sikerult olvasni\n");
        exit(-1);
    }
    printf("\nkliens kapott ertek : %d\n", val);
}

int getRandom() {
    return (rand() % 10) + 1;
}

