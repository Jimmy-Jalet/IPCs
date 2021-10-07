

#include <sys/types.h> 
#include <sys/shm.h> 
#include <sys/ipc.h> 
#include <errno.h> 
#include <time.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h>
#include "Shared_Mem.h"

int main(int argc, char** argv) {
    key_t clef;
    int id;
    // creation de la memoire partagée
    clef = ftok("/tmp/1234", 'a'); // generation d'une clef
    //6 --> 110
    //      RWX
    id = shmget(clef,sizeof(zone),IPC_CREATE |0600);// autorisation en R/W
    if(id==-1)
    {
        // le segment n'existe pas
        if(errno!=EEXIST)
        {
            printf("pb shmget : %s\n",strerror(errno));
            exit (errno);
        }
    }
    // attribution adresse virtuelle du segment
    
    return (EXIT_SUCCESS);
}

