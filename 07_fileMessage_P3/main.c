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
    int ret;
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
        ret=msgrcv(idFile,(void*)&maFile,sizeof(maFile),2,IPC_NOWAIT);
        if(ret!=-1) // pas d'erreur de lecture
        {
            printf("temp : %s\n",maFile.texte);
        }
        ret=msgrcv(idFile,(void*)&maFile,sizeof(maFile),4,IPC_NOWAIT);
        if(ret!=-1) // pas d'erreur de lecture
        {
            printf("pression : %s\n",maFile.texte);
        }
        ret=msgrcv(idFile,(void*)&maFile,sizeof(maFile),3,IPC_NOWAIT);
        if(ret!=-1) // pas d'erreur de lecture -> afficher le message
        {
            printf("ordre : %s\n",maFile.texte);
        }
        sleep(1);
    }


    return (EXIT_SUCCESS);
}
