#include <stdio.h>
#include <stdlib.h>
//include pour socket
#include <sys/types.h>
#include <sys/socket.h>
//include pour stockaddr_in
#include <netinet/in.h>
#include <arpa/inet.h>
//include gestion erreurs
#include <string.h>
#include <errno.h>
#include <unistd.h>

typedef struct {
        unsigned char jour;
        unsigned char mois;
        unsigned short int annee;
        char jourDeLaSemaine[10]; // le jour en toute lettre
    } datePerso;
    
int main(int argc, char** argv) {
    /* int sock;
     int valEnvoyee, valRecu;
     int retour;
     struct sockaddr_in adresseServeur;
     struct sockaddr_in infosReception;
     socklen_t taille;

     //creation de la socket
     sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
     if (sock == -1) {
         printf("pb socket : %s\n", strerror(errno));
         exit(errno);
     }
     //init de la structure pour communiquer avec le serveur

     adresseServeur.sin_family = AF_INET;
     adresseServeur.sin_port = htons(2222);
     adresseServeur.sin_addr.s_addr = htonl(INADDR_ANY);

     // Associer l'adresse IP et le nro de port
     retour = bind(sock, (struct sockaddr *) &adresseServeur, sizeof (adresseServeur));
     if (retour == -1) {
         printf("pb bind : %s\n", strerror(errno));
         exit(errno);
     }
     while (1) {
         //recevoir l'entier en provenance du client
         retour = recvfrom(sock, &valRecu, sizeof (valRecu), 0, (struct sockaddr *) &adresseServeur, &taille);
         if (retour == -1) {
             printf("pb recvfrom : %s\n", strerror(errno));
             exit(errno);
         }



         //renvoyer un entier au client
         valEnvoyee = -valRecu;
         retour = sendto(sock, &valEnvoyee, sizeof (valEnvoyee), 0, (struct sockaddr *) &adresseServeur, sizeof (adresseServeur));
         if (retour == -1) {
             printf("pb sendto : %s\n", strerror(errno));
             exit(errno);
         }
         //affiche l'entier
         printf("Message reçu du client : %d\n", valRecu);
     }*/
    
   // ------------------------------------------TCP-INT & FLOAT------------------------------------------------------
    /*int socketFileAttente;
    int socketCommunicationClient;
    float valEnvoyee, valRecu;
    float retour;
    struct sockaddr_in adresseServeur;
    struct sockaddr_in infosReception;
    socklen_t taille;

    //creation de la socket
    socketFileAttente = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socketCommunicationClient == -1) {
        printf("pb socket : %s\n", strerror(errno));
        exit(errno);
    }
    //init de la structure pour communiquer avec le serveur

    adresseServeur.sin_family = AF_INET;
    adresseServeur.sin_port = htons(2222);
    adresseServeur.sin_addr.s_addr = htonl(INADDR_ANY);

    // Associer l'adresse IP et le nro de port
    retour = bind(socketFileAttente, (struct sockaddr *) &adresseServeur, sizeof (adresseServeur));
    if (retour == -1) {
        printf("pb bind : %s\n", strerror(errno));
        exit(errno);
    }
    retour = listen(socketFileAttente, 20);
    if (retour == -1) {
        printf("pb listen : %s\n", strerror(errno));
        exit(errno);
    }
    taille = sizeof (infosReception);
    while (1 == 1) {
        socketCommunicationClient = accept(socketFileAttente, (struct sockaddr *) &infosReception, &taille);
        if (retour == -1) {
            printf("pb accept : %s\n", strerror(errno));
            exit(errno);
        }
        //recevoir l'entier en provenance du client
        retour = read(socketCommunicationClient, &valRecu, sizeof (valRecu));
        if (retour == -1) {
            printf("pb read : %s\n", strerror(errno));
            exit(errno);
        }
        //affiche l'entier
        printf("Message reçu du client : %f\n", valRecu);


        //renvoyer un entier au client
        valEnvoyee = -valRecu;
        printf("Message envoyer : %f\n", valEnvoyee);
        retour = write(socketCommunicationClient, &valEnvoyee, sizeof (valEnvoyee));
        if (retour == -1) {
            printf("pb write : %s\n", strerror(errno));
            exit(errno);
        }

    }*/
    int socketFileAttente;
    int socketCommunicationClient;
    float retour;
    struct sockaddr_in adresseServeur;
    struct sockaddr_in infosReception;
    socklen_t taille;
    datePerso date;

    //creation de la socket
    socketFileAttente = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socketCommunicationClient == -1) {
        printf("pb socket : %s\n", strerror(errno));
        exit(errno);
    }
    //init de la structure pour communiquer avec le serveur

    adresseServeur.sin_family = AF_INET;
    adresseServeur.sin_port = htons(2222);
    adresseServeur.sin_addr.s_addr = htonl(INADDR_ANY);

    // Associer l'adresse IP et le nro de port
    retour = bind(socketFileAttente, (struct sockaddr *) &adresseServeur, sizeof (adresseServeur));
    if (retour == -1) {
        printf("pb bind : %s\n", strerror(errno));
        exit(errno);
    }
    retour = listen(socketFileAttente, 20);
    if (retour == -1) {
        printf("pb listen : %s\n", strerror(errno));
        exit(errno);
    }
    taille = sizeof (infosReception);
    while (1 == 1) {
        socketCommunicationClient = accept(socketFileAttente, (struct sockaddr *) &infosReception, &taille);
        if (retour == -1) {
            printf("pb accept : %s\n", strerror(errno));
            exit(errno);
        }
        //recevoir l'entier en provenance du client
        retour = read(socketCommunicationClient, &date, sizeof (date));
        if (retour == -1) {
            printf("pb read : %s\n", strerror(errno));
            exit(errno);
        }
        //affiche l'entier
        printf("Message reçu du client : %s/%d/%d/%d\n", date.jourDeLaSemaine,date.jour,date.mois,date.annee);


    }

    return (EXIT_SUCCESS);
}