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
    /* UDP
     * float valEnvoyee, valRecu;
    float sock;
    float retour;
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
    infosServeur.sin_port = htons(3333); // port dans l'ordre reseau
    infosServeur.sin_addr.s_addr = inet_addr("172.18.58.104");

    //client : envoie un reel
    valEnvoyee = 6.8;
    retour = sendto(sock, &valEnvoyee, sizeof (valEnvoyee), 0, (struct sockaddr *)&infosServeur, sizeof (infosServeur));

    if (retour == -1) {
        printf("pb sendto : %s\n", strerror(errno));
        exit(errno);
    }
    //serveur : affiche le reel reçu
    
    retour = recvfrom(sock, &valRecu, sizeof (valRecu), 0, (struct sockaddr *)&infosReception,&taille);

    if (retour == -1) {
        printf("pb recvfrom : %s\n", strerror(errno));
        exit(errno);
    }
    printf("Reponse du serveur : %f\n",valRecu);
    //serveur : envoie l'inverse du reel
    //client : affiche ce que le serveur a envoyé*/
    
    //TCP
    int sock;
    float valEnvoyee, valRecu;
    float retour;
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
    infosServeur.sin_port = htons(2222); // port dans l'ordre reseau
    infosServeur.sin_addr.s_addr = inet_addr("172.18.58.90");

    //client : envoie un reel
    
    retour = connect(sock, (struct sockaddr *)&infosServeur, sizeof (infosServeur));

    if (retour == -1) {
        printf("pb connect : %s\n", strerror(errno));
        exit(errno);
    }
    //serveur : affiche le reel reçu
    taille = sizeof(valEnvoyee);
    valEnvoyee = 6.8;
    retour = write(sock,(void *)&valEnvoyee,taille);

    if (retour == -1) {
        printf("pb write : %s\n", strerror(errno));
        exit(errno);
    }
   
    //serveur : envoie l'inverse du reel
    retour = read(sock, &valRecu,taille);

    if (retour == -1) {
        printf("pb read : %s\n", strerror(errno));
        exit(errno);
    }
    
    //client : affiche ce que le serveur a envoyé
     printf("Reponse du serveur : %f\n",valRecu);
    return (EXIT_SUCCESS);
}


