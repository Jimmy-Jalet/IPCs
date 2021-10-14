#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define TAILLE_MAX 4096

int main(int argc, char *argv[]) {
    int socketFileAttente, socketCommunicationClient;

    struct sockaddr_in adresseServeur;
    struct sockaddr_in adresseClient;

    int retour;
    int tailleClient;
    int taille;
    char msgRecu[TAILLE_MAX];
    char msgEnvoyer[TAILLE_MAX];

    printf("serveur Web TCP sur port 6789 \n");


    adresseServeur.sin_family = AF_INET;

    adresseServeur.sin_port = htons(6789); //numero de port du serveur dans l'ordre des octets du r�seau
    adresseServeur.sin_addr.s_addr = htonl(INADDR_ANY); // adresse IP du serveur dans l'ordre des octets du reseau
    //stresseur de serveur
    socketFileAttente = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (socketFileAttente == -1) {
        printf("pb socket : %s\n", strerror(errno));
        exit(0);
    }
    retour = bind(socketFileAttente, (struct sockaddr*) &adresseServeur, sizeof ( adresseServeur)); //attachement ip-port

    if (retour == -1) {
        printf("pb bind : %s\n", strerror(errno));
        exit(0);
    }

    retour = listen(socketFileAttente, 10); //je peux gerer 10 clients en file d'attente
    if (retour == -1) {
        printf("pb listen : %s\n", strerror(errno));
        exit(0);
    }

    tailleClient = sizeof ( adresseClient);
    socketCommunicationClient = accept(socketFileAttente, (struct sockaddr *) &adresseClient, &tailleClient); // acceptation de la connexion client et creation de la socket de communication

    if (socketCommunicationClient == -1) {
        printf("pb accept : %s\n", strerror(errno));
        exit(0);
    }
    printf("Connection du client ²s\n",inet_ntoa(adresseClient.sin_addr));

   

    do{
        memset(msgRecu, '\0' , TAILLE_MAX);
        retour = read(socketCommunicationClient, msgRecu, TAILLE_MAX);
        if (retour == -1) {
            printf("pb connect : %s\n", strerror(errno));
            exit(0);
        }
        printf("message du client %s/%d: \n", inet_ntoa(adresseClient.sin_addr), adresseClient.sin_port);
        printf("%s\n", msgRecu);
        gets(msgEnvoyer);

        retour = write(socketCommunicationClient, msgEnvoyer, strlen(msgEnvoyer));
        if (retour == -1) {
            printf("pb connect : %s\n", strerror(errno));
            exit(0);
        }

    }while (strcmp("a+",msgRecu) !=0); 

        close(socketCommunicationClient);
    close(socketFileAttente);
        /*memset(buffer, '\0', 255);
        read(fdSocket,buffer,255);
        printf("reposne: %s\n",buffer);*/
    
    return EXIT_SUCCESS;
}