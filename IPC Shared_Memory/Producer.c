#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    void *sh_mem;
    int shid;
    char buff[100];

    // Create shared memory segment
    shid = shmget((key_t)1234, 1024, 0666 | IPC_CREAT);
    if (shid == -1) {
        perror("shmget failed");
        exit(EXIT_FAILURE);
    }

    printf("ID of shared memory: %d\n", shid);

    // Attach shared memory
    sh_mem = shmat(shid, NULL, 0);
    if (sh_mem == (void *)-1) {
        perror("shmat failed");
        exit(EXIT_FAILURE);
    }

    printf("Process attached at %p\n", sh_mem);

    // Get user input
    printf("Enter some data: ");
    read(0, buff, 100);

    // Copy input to shared memory
    strcpy(sh_mem, buff);
    printf("You wrote: %s\n", (char *)sh_mem);

    // Detach shared memory
    if (shmdt(sh_mem) == -1) {
        perror("shmdt failed");
        exit(EXIT_FAILURE);
    }

    return 0;
}
