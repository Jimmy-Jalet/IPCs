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
//zone de partage
laStruct partage;

void *thread1(void *arg) {
    printf("dans le thread1 mon tid est :%d\n", syscall(SYS_gettid));
    printf("mise a jour de v1 avec la valeur 10\n");
    partage.v1 = 10;
    pthread_exit(NULL);
}

void *thread2(void *arg) {
    printf("dans le thread1 mon tid est :%d\n", syscall(SYS_gettid));
    printf("mise a jour de v2 avec la valeur 20\n");
    partage.v2 = 20;
    pthread_exit(NULL);
}

void *thread3(void *arg) {

    printf("dans le thread1 mon tid est :%d\n", syscall(SYS_gettid));
    printf("mise a jour de v3 avec la valeur 30\n");
    partage.v3 = 30;
    pthread_exit(NULL);
}

void affichePartage() {
    printf("--------------------\n");
    printf("v1 = %d\n", partage.v1);
    printf("v2 = %d\n", partage.v2);
    printf("v3 = %d\n", partage.v3);
}

int main(int argc, char** argv) {

    pthread_t T1, T2, T3;
    int ret;
    void *thread_result;
    affichePartage();
    ret = pthread_create(&T1, NULL, thread1, NULL);
    if (ret != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
    affichePartage();
    ret = pthread_create(&T2, NULL, thread2, NULL);
    if (ret != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
    affichePartage();
    ret = pthread_create(&T3, NULL, thread3, NULL);
    if (ret != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
    affichePartage();
    ret = pthread_join(T1, &thread_result);
    if (ret != 0) {
        perror("Thread join a foir... echoué");
        exit(EXIT_FAILURE);
    }
    affichePartage();
    ret = pthread_join(T2, &thread_result);
    if (ret != 0) {
        perror("Thread join a foir... echoué");
        exit(EXIT_FAILURE);
    }
    affichePartage();
    ret = pthread_join(T3, &thread_result);
    if (ret != 0) {
        perror("Thread join a foir... echoué");
        exit(EXIT_FAILURE);
    }
    affichePartage();
    return (EXIT_SUCCESS);
}