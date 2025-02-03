#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    void *sh_mem;
    int shid;

    // Get existing shared memory
    shid = shmget((key_t)1234, 1024, 0666);
    if (shid == -1) {
        perror("shmget failed");
        exit(EXIT_FAILURE);
    }

    // Attach shared memory
    sh_mem = shmat(shid, NULL, 0);
    if (sh_mem == (void *)-1) {
        perror("shmat failed");
        exit(EXIT_FAILURE);
    }

    // Read and print data
    printf("Data in shared memory: %s", (char *)sh_mem);

    // Detach shared memory
    if (shmdt(sh_mem) == -1) {
        perror("shmdt failed");
        exit(EXIT_FAILURE);
    }

    // Remove shared memory
    if (shmctl(shid, IPC_RMID, NULL) == -1) {
        perror("shmctl (removal) failed");
        exit(EXIT_FAILURE);
    }

    printf("\nShared memory deleted successfully.\n");

    return 0;
}
