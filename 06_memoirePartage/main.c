

#include <sys/types.h> 
#include <sys/shm.h> 
#include <sys/ipc.h> 
#include <errno.h> 
#include <time.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h>
#include "Shared_Mem.h"
#include <sys/shm.h>

int main(int argc, char** argv) {
    key_t clef;
    int id;
    zone *partage;
    // creation de la memoire partagée
    clef = ftok("/tmp/1234", 'a'); // generation d'une clef
    //6 --> 110
    //      RWX
    id = shmget(clef,sizeof(zone),IPC_CREAT |0600);// autorisation en R/W
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
    shmat(zone *)shmat(id,NULL,SHM_W);
    if(partage ==(void *)-1){
        printf("pb shmget : %s\n",strerror(errno));
            exit (errno);
    }
            
    //lMise a jour temprature et pression de la zone partagee
    while(1){
        partage->pres=randomI();
        sleep(1);
        partage->temp=randomF();
        sleep(2);
        printf("temp: %.2f press : %d\n",partage->temp,partage->pres);
    }
    return (EXIT_SUCCESS);
}

