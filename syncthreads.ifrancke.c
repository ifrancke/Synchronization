#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUMTHREADS 3
#define MAXVAL 40
pthread_mutex_t mutex1;
pthread_mutex_t mutex2;
pthread_mutex_t mutex3;
int counter = 1;

typedef struct {
    int startVal;
    int maxVal;
} CountStruct;

void *runner1(void *param){
    CountStruct *data;
    data = (CountStruct *) param;
    
    while(data->startVal <= data->maxVal){
        pthread_mutex_lock(&mutex1);
        if(counter%3 == 0) {
            printf("%d\n", data->startVal);
            data->startVal = data->startVal + 3; 
            ++counter;
        }
        pthread_mutex_unlock(&mutex1);
    }
    pthread_exit(0);
}

void *runner2(void *param){
    CountStruct *data;
    data = (CountStruct *) param;
    
    while(data->startVal <= data->maxVal){
        pthread_mutex_lock(&mutex1);
        if(counter%3 == 1) {
            printf("%d\n", data->startVal);
            data->startVal = data->startVal + 3; 
            ++counter;
        }
        pthread_mutex_unlock(&mutex1);
    }
    pthread_exit(0);
}

void *runner3(void *param){
    CountStruct *data;
    data = (CountStruct *) param;
    
    while(data->startVal <= data->maxVal){
        pthread_mutex_lock(&mutex1);
        if(counter%3 == 2){
            printf("%d\n", data->startVal);
            data->startVal = data->startVal + 3; 
            ++counter;
        }
        pthread_mutex_unlock(&mutex1);
        
    }
    pthread_exit(0);
}

int main() {
    CountStruct counts[NUMTHREADS];
    pthread_t threads[NUMTHREADS];
    pthread_mutex_init(&mutex1, NULL);
    pthread_mutex_init(&mutex2, NULL);
    pthread_mutex_init(&mutex3, NULL);

    for(int i = 0; i < NUMTHREADS; i++){
        counts[i].startVal = i;
        counts[i].maxVal = 40;

        
    }
    pthread_create(&threads[0], NULL, runner1, &counts[0]);
    pthread_create(&threads[1], NULL, runner2, &counts[1]);
    pthread_create(&threads[2], NULL, runner3, &counts[2]);

    for(int i = 0; i < NUMTHREADS; i++){
        pthread_join(threads[i], NULL);
    }
    return 0;
}
