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



int main(int argc, char** argv) {
    int sock;
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
    }

    return (EXIT_SUCCESS);
}