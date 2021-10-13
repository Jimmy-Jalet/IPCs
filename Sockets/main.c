
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>

int main(int argc, char** argv) {
    /*UDP
     * int valEnvoyee, valRecu;
    int sock;
    int retour;
    struct sockaddr_in infosServeur;
     struct sockaddr_in infosReception;
     socklen_t taille;
    //creation socket
    sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock == -1) {
        printf("pb socket : %s\n", strerror(errno));
        exit(errno);
    }
    // init serveur
    infosServeur.sin_family = AF_INET;
    infosServeur.sin_port = htons(4444); // port dans l'ordre reseau
    infosServeur.sin_addr.s_addr = inet_addr("172.18.58.101");

    //client : envoie un entier
    valEnvoyee = 666;
    retour = sendto(sock, &valEnvoyee, sizeof (valEnvoyee), 0, (struct sockaddr *)&infosServeur, sizeof (infosServeur));

    if (retour == -1) {
        printf("pb sendto : %s\n", strerror(errno));
        exit(errno);
    }
    //serveur : affiche l'entier reçu
    
    retour = recvfrom(sock, &valRecu, sizeof (valRecu), 0, (struct sockaddr *)&infosReception,&taille);

    if (retour == -1) {
        printf("pb recvfrom : %s\n", strerror(errno));
        exit(errno);
    }
    printf("Reponse du serveur : %d\n",valRecu);
    //serveur : envoie l'inverse de l'entier
    //client : affiche ce que le serveur a envoyé*/


    //TCP
    int valEnvoyee, valRecu;
    int sock;
    int retour;
    struct sockaddr_in infosServeur;
    struct sockaddr_in infosReception;
    socklen_t taille;
    //creation socket
    sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == -1) {
        printf("pb socket : %s\n", strerror(errno));
        exit(errno);
    }
    // init serveur
    infosServeur.sin_family = AF_INET;
    infosServeur.sin_port = htons(5555); // port dans l'ordre reseau
    infosServeur.sin_addr.s_addr = inet_addr("172.18.58.150");

    //client : envoie un entier
    
    retour = connect(sock, (struct sockaddr *) &infosServeur, sizeof (infosServeur));

    if (retour == -1) {
        printf("pb connect : %s\n", strerror(errno));
        exit(errno);
    }
    //serveur : affiche l'entier reçu

    valEnvoyee = 123;
    taille = sizeof (valEnvoyee);
    
    retour =  write( sock, &valEnvoyee, taille);
    if (retour == -1) {
        printf("pb write : %s\n", strerror(errno));
        exit(errno);
    }
    printf("Reponse du serveur : %d\n", valRecu);
    //serveur : envoie l'inverse de l'entier
    
    retour =  read( sock, &valRecu, taille);
    if (retour == -1) {
        printf("pb read : %s\n", strerror(errno));
        exit(errno);
    }
    printf("Reponse du serveur : %d\n", valRecu);
    //client : affiche ce que le serveur a envoyé

    return (EXIT_SUCCESS);
}


