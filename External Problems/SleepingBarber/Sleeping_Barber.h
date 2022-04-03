//
// Created by Zza on 2022/4/3.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_SLEEPING_BARBER_H
#define DATASTRUCTUREIMPLEMENTINGC_SLEEPING_BARBER_H

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#define CUSTOMER_NUMBER 20
void *customer(void *param);

_Noreturn void *barber(void *param);

int seat_num = 5;

int cus_process_alive = CUSTOMER_NUMBER;
int interval[CUSTOMER_NUMBER] = {100, 100, 200, 100, 250, 400, 200,
                                 100, 200, 700, 100, 200, 600, 100,
                                 250, 400, 200, 100, 200, 700};

sem_t customer_ready;
sem_t barber_ready;
sem_t arrived;
sem_t mutex;

int main_barber_problem(int argc, char *argv[]) {
    pthread_t barber_id;
    pthread_t client_ids[CUSTOMER_NUMBER];
    sem_init(&mutex,0,1);
    sem_init(&barber_ready,0,0);
    sem_init(&customer_ready,0,0);
    sem_init(&arrived,0,0);
    pthread_create(&barber_id, NULL, barber, NULL);
    for (int i = 0; i < CUSTOMER_NUMBER; i++){
        usleep(interval[i]*1000);
        printf("%d: One customer comes, see %d seats left now\n",
               time(NULL), seat_num);
        pthread_create(&client_ids[i], NULL, customer, NULL);
    }
    while(cus_process_alive);
    return 0;
}

int iter=0;
_Noreturn void *barber(void *param) {
    int worktime = 500;
    time_t t;
    while(1) {
        sem_wait(&customer_ready);
        sem_post(&barber_ready);

        sem_wait(&arrived);
        iter++;
        t = time(NULL);
        printf("%d: Barber start cut the %d hair\n",t,iter);
        usleep(worktime*1000);
        t = time(NULL);
        printf("%d: Barber end cut the %d hair\n",t,iter);

    }
}

void *customer(void *param) {
    sem_wait(&mutex);
    if(seat_num > 0){
        seat_num --;
        printf("%d: One customer ready, make %d seats left now\n",
               time(NULL), seat_num);
//        坐下后就一次性喊
        sem_post(&customer_ready);
        sem_post(&mutex);

        sem_wait(&barber_ready);
//        听到消息后自己离开位置
        sem_wait(&mutex);
        seat_num++;
        printf("%d: One customer is to cut, make %d seats left now\n",
               time(NULL), seat_num);
        sem_post(&mutex);
        sem_post(&arrived);

    } else {
        printf("%d: One customer leaves with no haircut\n", time(NULL));
        sem_post(&mutex);
    }
    cus_process_alive--;
}

#endif //DATASTRUCTUREIMPLEMENTINGC_SLEEPING_BARBER_H
