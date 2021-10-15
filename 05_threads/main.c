#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/syscall.h>

char message[255]; // Zone commune

typedef struct {
    int v1;
    int v2;
    int v3;
} laStruct;

//Zone de partage
laStruct partage;
//mutex
pthread_mutex_t verrou;

void *thread1(void *arg) {
    int *ptr = (int *) arg;
    printf("dans le thread 1 mon pid est %ld\n", syscall(SYS_gettid));
    printf("mise à jour de v1 avec la valeur %d\n", *ptr);
    partage.v1 = *ptr;

    pthread_exit(NULL);
}

void *thread2(void *arg) {
    int *ptr = (int *) arg;
    printf("dans le thread 2 mon pid est %ld\n", syscall(SYS_gettid));
    printf("mise à jour de v1 avec la valeur %d\n", *ptr);
    partage.v2 = *ptr;
    pthread_exit(NULL);
}

void *thread3(void *arg) {
    int *ptr = (int *) arg;
    printf("dans le thread 3 mon pid est %ld\n", syscall(SYS_gettid));
    printf("mise à jour de v1 avec la valeur %d\n", *ptr);
    partage.v3 = ptr;
    pthread_exit(NULL);
}

void *threadMulti(void *arg) {
    laStruct *ptr = (laStruct *) arg;
    printf("dans le threadMulti mon pid est %ld\n", syscall(SYS_gettid));
    printf("mise à jour de v1,v2,v3 avec les valeurs %d,%d,%d\n", ptr->v1, ptr->v2, ptr->v3);
    //Section Critique
    pthread_mutex_lock(&verrou);
    partage.v1 = ptr->v1;
    sleep(3 - ptr->v1);
    partage.v2 = ptr->v2;
    partage.v3 = ptr->v3;
    pthread_mutex_unlock(&verrou);
    //Fin section critique
    pthread_exit(NULL);
}

void affichePartage() {
    pthread_mutexlock(&verrou);
    printf("__\n");
    printf("v1 = %d\n", partage.v1);
    printf("v2 = %d\n", partage.v2);
    printf("v3 = %d\n", partage.v3);
    pthread_mutex_unlock(&verrou);
}
pthread_t t1, t2, t3;
    int ret;
    void *thread_result;
    laStruct param1, param2, param3;
    param1.v1 = 1;
    param1.v2 = 1;
    param1.v3 = 1;
    //Initialisation du mutex
    ret= pthread_mutex_init(&verrou, NULL);
    if(ret!=0)
    {
        perror("Pb Mutex Initialisation");
        exit(EXIT_FAILURE);
    }
    affichePartage();
    //creation du thread 1

    ret = pthread_create(&t1, NULL, threadMulti, (void *) &param1);
    if (ret != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
    affichePartage();
    //creation du thread 2
    param2.v1 = 2;
    param2.v2 = 2;
    param2.v3 = 2;
    ret = pthread_create(&t2, NULL, threadMulti, (void *) &param2);
    if (ret != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
    affichePartage();
    //creation du thread 3
    param3.v1 = 3;
    param3.v2 = 3;
    param3.v3 = 3;
    ret = pthread_create(&t3, NULL, threadMulti, (void *) &param3);
    if (ret != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
    affichePartage();

    //attendre fin du thread 1
    ret = pthread_join(t1, &thread_result);
    if (ret != 0) {
        perror("Thread join a foir... echoué");
        exit(EXIT_FAILURE);
    }
    //attendre fin du thread 2
    ret = pthread_join(t2, &thread_result);
    if (ret != 0) {
        perror("Thread join a foir... echoué");
        exit(EXIT_FAILURE);
    }
    //attendre fin du thread 3
    ret = pthread_join(t3, &thread_result);
    if (ret != 0) {
        perror("Thread join a foir... echoué");
        exit(EXIT_FAILURE);
    }
    affichePartage();
    return (EXIT_SUCCESS);
}