# Sleeping barber problem

## description:

The sleeping_barber Problem:

- A barbershop consists of a waiting room with n chairs and the barber room containing the barber chair.
- if there are no customers to be served, the barber goes to sleep.
- if a customer enters the barbershop and all chairs are occupied, then the customer leaves the shop.
- if the barber is busy but chairs are available,then the customer sits in a free chair.
- if the barber is asleep,the customer wakes up the barber.

## Solution Method:

### Semaphore:

| Semaphore name      | Init numbers | Target                             |
| ------------------- | ------------ | ---------------------------------- |
| mutex               | 1            | 用于互斥地维护seat变量的数值       |
| barber_ready        | 0            | 用于保证barber与customer的前后关系 |
| customer_ready      | 0            | 用于保证barber与customer的前后关系 |
| seat(not semaphore) | n            | 店内剩余的椅子数量                 |
| arrive              | 0            | 判断客户是否走到了理发师处         |

### Relation:

因为如果店内没有椅子的时候，顾客便不再等待，所以我们就不设置椅子为信号量。

但是椅子也是一种资源，需要有互斥的分配，所以我们使用了mutex来实现椅子的互斥的访问。

#### Customer process:

- 对于顾客进程，我们基本上是使用试探和问询的逻辑。
- 进入店内后，先试探地去访问是否还有剩余地椅子，如果有就进入店内坐下，如果没有那么就离开。
- 坐在椅子上以后，就对理发师发出customer_ready的信号，表明自己一直在等待。
- 等待理发师发出ready的信号，接收到信号以后离开自己的位置去到理发位，修改位置信息。

### Barber process:

- 对于理发师进程，我们基本使用获得-回答的逻辑。
- 理发师一直在等待顾客发出ready的信号，如果听到了ready的信号且这个时候没有事情，就响应barber_ready信号。也就是听到有一个人说自己好了，就叫一个人过来。

### Update:

但是这里有个问题，就是如果理发师剪得非常非常快，当剪的过程已经结束，如果这个时候进程还在处理seat的操作，它就会让下一个进程直接过来，这就发生了问题。

所以引入了arrive变量，只有在顾客到达位置以后，才会开始剪。

## Source Code:

```c
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
```