#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char const *argv[]) {
    int fileDescriptor = open("jmdrgg.txt", O_RDWR);
    
    if (fileDescriptor == -1) {
        printf("Hibas file name");
        return 1;
    } 

    char text[256];
    int numberOfBytes = read(fileDescriptor, text, sizeof(text));

    text[numberOfBytes] = '\0';

    printf("Beolvasott szoveg: %s\nByteok szama: %d", text, numberOfBytes);

    lseek(fileDescriptor, 0, SEEK_SET);

    char szoveg[] = "szoveg";
    numberOfBytes = write(fileDescriptor, szoveg, sizeof(szoveg));
    printf("\nkiirt szoveg: %s\nByteok szama: %d", szoveg, numberOfBytes);

    return 0;
}
