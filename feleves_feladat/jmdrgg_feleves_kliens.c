#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdbool.h>

#define CSONEV "jmdrgg_pipe"

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

int main(int argc, char const *argv[]) {
    srand(time(0));
    //execlp("./jmdrgg_feleves", "jmdrgg_feleves", (char *)NULL);
    int fd = open(CSONEV, O_RDWR);
    printf("kliens indul...\n");

    kliensIr(fd);

    kliensOlvas(fd);

    close(fd);   
    
    unlink(CSONEV);
    
    return 0;
}

void kliensIr(int fd) {
    int n = getRandom();
    if (write(fd, &n, sizeof(int)) == -1) {
        perror("kliens : Nem sikerult irni\n");
    } else {
        printf("kliens : irva\n");
    }
}

void kliensOlvas(int fd) {
    bool olvasott = false;
    int val;
    do {
        printf("kliens olvas...\n");
        if (read(fd, &val, sizeof(val)) > 0) {
            olvasott = true;
        }
    } while (olvasott == false);
    printf("\nkliens kapott ertek : %d\n", val);
}

int getRandom() {
    return rand() % 10 + 1;
}

