#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUMTHREADS 3
#define MAXVAL 40 //make user input later
pthread_mutex_t mutex1;
pthread_mutex_t mutex2;
pthread_mutex_t mutex3;

typedef struct {
    int startVal;
    int maxVal;
} CountStruct;

void *runner(void *param){
    CountStruct *data;
    data = (CountStruct *) param;
    
    while(data->startVal < data->maxVal){
        pthread_mutex_lock(&mutex1);
        printf("%d\n", data->startVal);
        data->startVal = data->startVal + 3; 
        pthread_mutex_unlock(&mutex1);
    }
    pthread_exit(0);
}

int main() {
    CountStruct counts[NUMTHREADS];
    pthread_t threads[NUMTHREADS];
    pthread_mutex_init(&mutex1, NULL);

    for(int i = 0; i < NUMTHREADS; i++){
        counts[i].startVal = i;
        counts[i].maxVal = 40;

        pthread_create(&threads[i], NULL, runner, &counts[i]);
    }
    for(int i = 0; i < NUMTHREADS; i++){
        pthread_join(threads[i], NULL);
    }
    return 0;
}
