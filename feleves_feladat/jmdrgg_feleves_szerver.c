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

void olvasMajdVisszair(int);

int val = 0;

int main(int argc, char const *argv[]) {
    int pipe = mkfifo(CSONEV, S_IFIFO | 0666);
    int fd = open(CSONEV, O_RDWR);
    
    olvasMajdVisszair(fd);
    
    printf("\nbefejezve\n");

    unlink(CSONEV);
    return 0;
}

void olvasMajdVisszair(int fd) {
    bool irva = false;
    do {
        printf("szerver olvas..\n");
        read(fd, &val, sizeof(val));
        printf("szerver megkapta : %d \n", val);
        val *= 2;
        if (write(fd, &val, sizeof(val)) != 0) {
            irva = true;
        }
    } while (irva == false);
    close(fd);
}
