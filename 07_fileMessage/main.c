#include <sys/types.h> 
#include <sys/shm.h> 
#include <sys/ipc.h> 
#include <errno.h> 
#include <time.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <string.h>

#include "zone.h"

int main(int argc, char** argv) {
    struct donnees maFile;
    int idFile;
    key_t clef;
    // creation de la file
    clef = ftok("/tmp/5678", 'a'); // generation d'une clef
    idFile = msgget(clef, IPC_CREAT | IPC_EXCL);
    if (idFile == -1) {
        if (errno != EEXIST) {
            printf("pb msgget : %s\n", strerror(errno));
            exit(errno);
        }
    }
    while (1) 
    {
        // envoyer temperature dans la file
        //type 2 selon le sujet
        sprintf(maFile.texte,"%.2f",randomF());
        maFile.type=2;
        msgsnd(idFile,(void *)&maFile,sizeof(maFile),IPC_NOWAIT);
        sleep(1);
        // envoyer prsesion dans la file
        //type 4 selon le sujet
        sprintf(maFile.texte,"%d",randomI());
        maFile.type=4;
        msgsnd(idFile,(void *)&maFile,sizeof(maFile),IPC_NOWAIT);
        sleep(2);
    }


    return (EXIT_SUCCESS);
}
