# IPC全解析

进程间通信（IPC，InterProcess Communication）是指在不同进程之间传播或交换信息。

IPC的方式通常有管道（包括无名管道和命名管道）、消息队列、信号量、共享存储、Socket、Streams等。其中 Socket和Streams支持不同主机上的两个进程IPC。

以Linux中的C语言编程为例。

## 一、管道

管道，通常指无名管道，是 UNIX 系统IPC最古老的形式。

### 1、特点：

1. 它是半双工的（即数据只能在一个方向上流动），具有固定的读端和写端。
2. 它只能用于具有亲缘关系的进程之间的通信（父子进程或者兄弟进程之间）。

3. 它可以看成是一种特殊的文件，对于它的读写也可以使用普通的read、write 等函数。但是它不是普通的文件，并不属于其他任何文件系统，并且只存在于内存中。


### 2、原型：

```
#include <unistd.h>
int pipe(int fd[2]);    // 返回值：若成功返回0，失败返回-1
// 当一个管道建立时，它会创建两个文件描述符：fd[0]为读而打开，fd[1]为写而打开。如下图：
// 要关闭管道只需将这两个文件描述符关闭即可。
```

### 3、例子

单个进程中的管道几乎没有任何用处。所以，通常调用 pipe 的进程接着调用 fork，这样就创建了父进程与子进程之间的 IPC 通道。

若要数据流从父进程流向子进程，则关闭父进程的读端（fd[0]）与子进程的写端（fd[1]）；反之，则可以使数据流从子进程流向父进程。

```c
#include<stdio.h>
#include<unistd.h>

int main()
{
    int fd[2];  // 两个文件描述符
    pid_t pid;
    char buff[20];

if(pipe(fd) < 0)  // 创建管道
    printf("Create Pipe Error!\n");

if((pid = fork()) < 0)  // 创建子进程
    printf("Fork Error!\n");
else if(pid > 0)  // 父进程
{
    close(fd[0]); // 关闭读端
    write(fd[1], "hello world\n", 12);
}
else
{
    close(fd[1]); // 关闭写端
    read(fd[0], buff, 20);
    printf("%s", buff);
}

return 0;

}
```

## 二、FIFO

FIFO，也称为命名管道，它是一种文件类型。

### 1、特点

1. FIFO可以在无关的进程之间交换数据，与无名管道不同。
2. FIFO有路径名与之相关联，它以一种特殊设备文件形式存在于文件系统中。


### 2、原型

```c
#include <sys/stat.h>
// 返回值：成功返回0，出错返回-1
int mkfifo(const char *pathname, mode_t mode);
// 其中的 mode 参数与open函数中的 mode 相同。一旦创建了一个 FIFO，就可以用一般的文件I/O函数操作它。

// 当 open 一个FIFO时，是否设置非阻塞标志（O_NONBLOCK）的区别：
```

- 若没有指定O_NONBLOCK（默认），只读 open 要阻塞到某个其他进程为写而打开此 FIFO。类似的，只写 open 要阻塞到某个其他进程为读而打开它。

- 若指定了O_NONBLOCK，则只读 open 立即返回。而只写 open 将出错返回 -1 如果没有进程已经为读而打开该 FIFO，其errno置ENXIO。


### 3、例子

FIFO的通信方式类似于在进程中使用文件来传输数据，只不过FIFO类型文件同时具有管道的特性。在数据读出时，FIFO管道中同时清除数据，并且“先进先出”。下面的例子演示了使用 FIFO 进行 IPC 的过程：

```c
写FIFO示例程序:

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>   // exit
#include<fcntl.h>    // O_WRONLY
#include<sys/stat.h>
#include<sys/types.h>
#include<time.h>     // time

int main()
{
    int fd;
    int n, i;
    char buf[1024];
    time_t tp;
    printf("I am %d process.\n", getpid()); // 说明进程ID
    if((fd = open("fifo1", O_WRONLY)) < 0) // 以写打开一个FIFO
    {
        perror("Open FIFO Failed");
        exit(1);
    }

for(i=0; i<10; ++i)
{
    time(&tp);  // 取系统当前时间
    n=sprintf(buf,"Process %d's time is %s",getpid(),ctime(&tp));
    printf("Send message: %s", buf); // 打印
    if(write(fd, buf, n+1) < 0)  // 写入到FIFO中
    {
        perror("Write FIFO Failed");
        close(fd);
        exit(1);
    }
    sleep(1);  // 休眠1秒
}
close(fd);  // 关闭FIFO文件
return 0;

}
        读FIFO示例程序：

#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>

int main()
{
    int fd;
    int len;
    char buf[1024];

if(mkfifo("fifo1", 0666) < 0 && errno!=EEXIST) // 创建FIFO管道
    perror("Create FIFO Failed");

if((fd = open("fifo1", O_RDONLY)) < 0)  // 以读打开FIFO
{
    perror("Open FIFO Failed");
    exit(1);
}

while((len = read(fd, buf, 1024)) > 0) // 读取FIFO管道
    printf("Read message: %s", buf);
close(fd);  // 关闭FIFO文件
return 0;

}
```

在两个终端里用 gcc 分别编译运行上面两个文件，可以看到输出结果如下：

```
(写终端)

I am 69684 process.
Send message: Process 69684's time is Sun Jul  5 21:22:04 2020
Send message: Process 69684's time is Sun Jul  5 21:22:05 2020
Send message: Process 69684's time is Sun Jul  5 21:22:06 2020
Send message: Process 69684's time is Sun Jul  5 21:22:07 2020
Send message: Process 69684's time is Sun Jul  5 21:22:08 2020
Send message: Process 69684's time is Sun Jul  5 21:22:09 2020
Send message: Process 69684's time is Sun Jul  5 21:22:10 2020
Send message: Process 69684's time is Sun Jul  5 21:22:11 2020
Send message: Process 69684's time is Sun Jul  5 21:22:12 2020
Send message: Process 69684's time is Sun Jul  5 21:22:13 2020
        读终端：

Read message: Process 69684's time is Sun Jul  5 21:22:04 2020
Read message: Process 69684's time is Sun Jul  5 21:22:05 2020
Read message: Process 69684's time is Sun Jul  5 21:22:06 2020
Read message: Process 69684's time is Sun Jul  5 21:22:07 2020
Read message: Process 69684's time is Sun Jul  5 21:22:08 2020
Read message: Process 69684's time is Sun Jul  5 21:22:09 2020
Read message: Process 69684's time is Sun Jul  5 21:22:10 2020
Read message: Process 69684's time is Sun Jul  5 21:22:11 2020
Read message: Process 69684's time is Sun Jul  5 21:22:12 2020
Read message: Process 69684's time is Sun Jul  5 21:22:13 2020
```

上述例子可以扩展成 客户进程—服务器进程 通信的实例，write_fifo的作用类似于客户端，可以打开多个客户端向一个服务器发送请求信息，read_fifo类似于服务器，它适时监控着FIFO的读端，当有数据时，读出并进行处理，但是有一个关键的问题是，每一个客户端必须预先知道服务器提供的FIFO接口，下图显示了这种安排：



## 三、消息队列

消息队列，是消息的链接表，存放在内核中。一个消息队列由一个标识符（即队列ID）来标识。

### 1、特点

1. 消息队列是面向记录的，其中的消息具有特定的格式以及特定的优先级。
2. 消息队列独立于发送与接收进程。进程终止时，消息队列及其内容并不会被删除。

3. 消息队列可以实现消息的随机查询,消息不一定要以先进先出的次序读取,也可以按消息的类型读取。


### 2、原型

```c
#include <sys/msg.h>
// 创建或打开消息队列：成功返回队列ID，失败返回-1
int msgget(key_t key, int flag);
// 添加消息：成功返回0，失败返回-1
int msgsnd(int msqid, const void *ptr, size_t size, int flag);
// 读取消息：成功返回消息数据的长度，失败返回-1
int msgrcv(int msqid, void *ptr, size_t size, long type,int flag);
// 控制消息队列：成功返回0，失败返回-1
int msgctl(int msqid, int cmd, struct msqid_ds *buf);
        在以下两种情况下，msgget将创建一个新的消息队列：

如果没有与键值key相对应的消息队列，并且flag中包含了IPC_CREAT标志位。
key参数为IPC_PRIVATE。
        函数msgrcv在读取消息队列时，type参数有下面几种情况：

type == 0，返回队列中的第一个消息；
type > 0，返回队列中消息类型为 type 的第一个消息；
type < 0，返回队列中消息类型值小于或等于 type 绝对值的消息，如果有多个，则取类型值最小的消息。
```

可以看出，type值非 0 时用于以非先进先出次序读消息。也可以把 type 看做优先级的权值。（其他的参数解释，请自行Google之）

### 3、例子

下面写了一个简单的使用消息队列进行IPC的例子，服务端程序一直在等待特定类型的消息，当收到该类型的消息以后，发送另一种特定类型的消息作为反馈，客户端读取该反馈并打印出来。

```c
服务端示例：

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/msg.h>

// 用于创建一个唯一的key
#define MSG_FILE "/etc/passwd"

// 消息结构
struct msg_form {
    long mtype;
    char mtext[256];
};

int main()
{
    int msqid;
    key_t key;
    struct msg_form msg;

// 获取key值
if((key = ftok(MSG_FILE,'z')) < 0)
{
    perror("ftok error");
    exit(1);
}

// 打印key值
printf("Message Queue - Server key is: %d.\n", key);

// 创建消息队列
if ((msqid = msgget(key, IPC_CREAT|0777)) == -1)
{
    perror("msgget error");
    exit(1);
}

// 打印消息队列ID及进程ID
printf("My msqid is: %d.\n", msqid);
printf("My pid is: %d.\n", getpid());

// 循环读取消息
for(;;)
{
    msgrcv(msqid, &msg, 256, 888, 0);// 返回类型为888的第一个消息
    printf("Server: receive msg.mtext is: %s.\n", msg.mtext);
    printf("Server: receive msg.mtype is: %ld.\n", msg.mtype);

​    msg.mtype = 999; // 客户端接收的消息类型
​    sprintf(msg.mtext, "hello, I'm server %d", getpid());
​    msgsnd(msqid, &msg, sizeof(msg.mtext), 0);

}
return 0;

}
        客户端示例：

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/msg.h>

// 用于创建一个唯一的key
#define MSG_FILE "/etc/passwd"

// 消息结构
struct msg_form {
    long mtype;
    char mtext[256];
};

int main()
{
    int msqid;
    key_t key;
    struct msg_form msg;

// 获取key值
if ((key = ftok(MSG_FILE, 'z')) < 0)
{
    perror("ftok error");
    exit(1);
}

// 打印key值
printf("Message Queue - Client key is: %d.\n", key);

// 打开消息队列
if ((msqid = msgget(key, IPC_CREAT|0777)) == -1)
{
    perror("msgget error");
    exit(1);
}

// 打印消息队列ID及进程ID
printf("My msqid is: %d.\n", msqid);
printf("My pid is: %d.\n", getpid());

// 添加消息，类型为888
msg.mtype = 888;
sprintf(msg.mtext, "hello, I'm client %d", getpid());
msgsnd(msqid, &msg, sizeof(msg.mtext), 0);

// 读取类型为999的消息
msgrcv(msqid, &msg, 256, 999, 0);
printf("Client: receive msg.mtext is: %s.\n", msg.mtext);
printf("Client: receive msg.mtype is: %ld.\n", msg.mtype);
return 0;

}
```

## 四、信号量

信号量（semaphore）与已经介绍过的 IPC 结构不同，它是一个计数器。信号量用于实现进程间的互斥与同步，而不是用于存储进程间通信数据。

### 0、简介

#### 1.信号本质

- 信号是在软件层次上对中断机制的一种模拟，在原理上，一个进程收到一个信号与处理器收到一个中断请求可以说是一样的。信号是异步的，一个进程不必通过任何操作来等待信号的到达，事实上，进程也不知道信号到底什么时候到达。

- 信号是进程间通信机制中唯一的异步通信机制，可以看作是异步通知，通知接收信号的进程有哪些事情发生了。信号机制经过POSIX实时扩展后，功能更加强大，除了基本通知功能外，还可以传递附加信息。


#### 2.信号来源

信号事件的发生有两个来源：硬件来源(比如我们按下了键盘或者其它硬件故障)；软件来源，最常用发送信号的系统函数是kill, raise, alarm和setitimer以及sigqueue函数，软件来源还包括一些非法运算等操作。

#### 3.信号的种类

可以从两个不同的分类角度对信号进行分类：

1. 可靠性方面：可靠信号与不可靠信号；
2. 与时间的关系上：实时信号与非实时信号。

在《Linux环境进程间通信（一）：管道及有名管道》的附1中列出了系统所支持的所有信号。

##### 1) 不可靠信号

- Linux信号机制基本上是从Unix系统中继承过来的。早期Unix系统中的信号机制比较简单和原始，后来在实践中暴露出一些问题，因此，把那些建立在早期机制上的信号叫做"不可靠信号"，信号值小于SIGRTMIN(Red hat 7.2中，SIGRTMIN=32，SIGRTMAX=63)的信号都是不可靠信号。这就是"不可靠信号"的来源。它的主要问题是：

- 进程每次处理信号后，就将对信号的响应设置为默认动作。在某些情况下，将导致对信号的错误处理；因此，用户如果不希望这样的操作，那么就要在信号处理函数结尾再一次调用signal()，重新安装该信号。
  信号可能丢失，后面将对此详细阐述。
  因此，早期unix下的不可靠信号主要指的是进程可能对信号做出错误的反应以及信号可能丢失。

##### 2) 可靠信号

- 随着时间的发展，实践证明了有必要对信号的原始机制加以改进和扩充。所以，后来出现的各种Unix版本分别在这方面进行了研究，力图实现"可靠信号"。由于原来定义的信号已有许多应用，不好再做改动，最终只好又新增加了一些信号，并在一开始就把它们定义为可靠信号，这些信号支持排队，不会丢失。同时，信号的发送和安装也出现了新版本：信号发送函数sigqueue()及信号安装函数sigaction()。POSIX.4对可靠信号机制做了标准化。但是，POSIX只对可靠信号机制应具有的功能以及信号机制的对外接口做了标准化，对信号机制的实现没有作具体的规定。

- 信号值位于SIGRTMIN和SIGRTMAX之间的信号都是可靠信号，可靠信号克服了信号可能丢失的问题。Linux在支持新版本的信号安装函数sigation（）以及信号发送函数sigqueue()的同时，仍然支持早期的signal（）信号安装函数，支持信号发送函数kill()。

### 1、特点

1. 信号量用于进程间同步，若要在进程间传递数据需要结合共享内存。
2. 信号量基于操作系统的 PV 操作，程序对信号量的操作都是原子操作。

3. 每次对信号量的 PV 操作不仅限于对信号量值加 1 或减 1，而且可以加减任意正整数。

4. 支持信号量组。


### 2、原型

​        最简单的信号量是只能取 0 和 1 的变量，这也是信号量最常见的一种形式，叫做二值信号量（Binary Semaphore）。而可以取多个正整数的信号量被称为通用信号量。

`Linux 下的信号量函数都是在通用的信号量数组上进行操作，而不是在一个单一的二值信号量上进行操作。`

```c
#include <sys/sem.h>
// 创建或获取一个信号量组：若成功返回信号量集ID，失败返回-1
int semget(key_t key, int num_sems, int sem_flags);
// 对信号量组进行操作，改变信号量的值：成功返回0，失败返回-1
int semop(int semid, struct sembuf semoparray[], size_t numops);
// 控制信号量的相关信息
int semctl(int semid, int sem_num, int cmd, ...);
       当semget创建新的信号量集合时，必须指定集合中信号量的个数（即num_sems），通常为1； 如果是引用一个现有的集合，则将num_sems指定为 0 。
```

在semop函数中，sembuf结构的定义如下：

```
struct sembuf
{
    short sem_num; // 信号量组中对应的序号，0～sem_nums-1
    short sem_op;  // 信号量值在一次操作中的改变量
    short sem_flg; // IPC_NOWAIT, SEM_UNDO
}
```

​       其中 sem_op 是一次操作中的信号量的改变量：

- 若sem_op > 0，表示进程释放相应的资源数，将 sem_op 的值加到信号量的值上。如果有进程正在休眠等待此信号量，则换行它们。

- 若sem_op < 0，请求 sem_op 的绝对值的资源。

- 如果相应的资源数可以满足请求，则将该信号量的值减去sem_op的绝对值，函数成功返回。
  当相应的资源数不能满足请求时，这个操作与sem_flg有关。
  sem_flg 指定IPC_NOWAIT，则semop函数出错返回EAGAIN。
  sem_flg 没有指定IPC_NOWAIT，则将该信号量的semncnt值加1，然后进程挂起直到下述情况发生：
  当相应的资源数可以满足请求，此信号量的semncnt值减1，该信号量的值减去sem_op的绝对值。成功返回；
  此信号量被删除，函数smeop出错返回EIDRM；
  进程捕捉到信号，并从信号处理函数返回，此情况下将此信号量的semncnt值减1，函数semop出错返回EINTR
  若sem_op == 0，进程阻塞直到信号量的相应值为0：
- 当信号量已经为0，函数立即返回。
  如果信号量的值不为0，则依据sem_flg决定函数动作：
  sem_flg指定IPC_NOWAIT，则出错返回EAGAIN。
  sem_flg没有指定IPC_NOWAIT，则将该信号量的semncnt值加1，然后进程挂起直到下述情况发生：
  信号量值为0，将信号量的semzcnt的值减1，函数semop成功返回；
  此信号量被删除，函数smeop出错返回EIDRM；
  进程捕捉到信号，并从信号处理函数返回，在此情况将此信号量的semncnt值减1，函数semop出错返回EINTR

在semctl函数中的命令有多种，这里就说两个常用的：

- SETVAL：用于初始化信号量为一个已知的值。所需要的值作为联合semun的val成员来传递。在信号量第一次使用之前需要设置信号量。
- IPC_RMID：删除一个信号量集合。如果不删除信号量，它将继续在系统中存在，即使程序已经退出，它可能在你下次运行此程序时引发问题，而且信号量是一种有限的资源。

### 3、例子

```c
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/sem.h>

// 初始化信号量
int init_sem(int sem_id, int value)
{
    union semun tmp;
    tmp.val = value;
    if(semctl(sem_id, 0, SETVAL, tmp) == -1)
    {
        perror("Init Semaphore Error");
        return -1;
    }
    return 0;
}

// P操作:
// 若信号量值为1，获取资源并将信号量值-1
// 若信号量值为0，进程挂起等待
int sem_p(int sem_id)
{
    struct sembuf sbuf;
    sbuf.sem_num = 0;
    sbuf.sem_op = -1;
    sbuf.sem_flg = SEM_UNDO;
    if(semop(sem_id,&sbuf, 1) == -1) {
       perror("P operation Error");
       return -1;
    }
    return 0;
}

// V操作：
//    释放资源并将信号量值+1
//    如果有进程正在挂起等待，则唤醒它们
int sem_v(int sem_id)
{
    struct sembuf sbuf;
    sbuf.sem_num = 0;
    sbuf.sem_op = 1;

sbuf.sem_flg = SEM_UNDO;
if(semop(sem_id, &sbuf, 1) == -1) {
     perror("V operation Error");
     return -1;
}
return 0;

}

// 删除信号量集
int del_sem(int sem_id)
{
    union semun tmp;
    if(semctl(sem_id, 0, IPC_RMID, tmp) == -1) {
        perror("Delete Semaphore Error");
        return -1;
    }
    return 0;
}

int main()
{
    int sem_id; // 信号量集ID
    key_t key;
    pid_t pid;

// 获取key值
if((key = ftok(".",'z')) < 0) {
     perror("ftok error");
     exit(1);
}

//创建信号量集，其中只有一个信号量
if((sem_id = semget(key,1, IPC_CREAT|0666)) == -1) {
     perror("semget error");
     exit(1);
}

// 初始化：初值设为0资源被占用
init_sem(sem_id,0);
if((pid = fork()) == -1)
    perror("Fork Error");
else if(pid == 0) {
    sleep(2);
    printf("Process child: pid=%d\n",getpid());
    sem_v(sem_id);
} else {
   sem_p(sem_id);
   printf("Process father: pid=%d\n", getpid());
   sem_v(sem_id);
   del_sem(sem_id);
}

return 0;

}
```

上面的例子如果不加信号量，则父进程会先执行完毕。这里加了信号量让父进程等待子进程执行完以后再执行。

## 五、共享内存

共享内存（Shared Memory），指两个或多个进程共享一个给定的存储区。

### 1、特点

1. 共享内存是最快的一种 IPC，因为进程是直接对内存进行存取。
2. 因为多个进程可以同时操作，所以需要进行同步。

3. 信号量+共享内存通常结合在一起使用，信号量用来同步对共享内存的访问。


### 2、原型

```
#include <sys/shm.h>
// 创建或获取一个共享内存：成功返回共享内存ID，失败返回-1
int shmget(key_t key, size_t size, int flag);
// 连接共享内存到当前进程的地址空间：成功返回指向共享内存的指针，失败返回-1
void *shmat(int shm_id, const void *addr, int flag);
// 断开与共享内存的连接：成功返回0，失败返回-1
int shmdt(void *addr); 
// 控制共享内存的相关信息：成功返回0，失败返回-1
int shmctl(int shm_id, int cmd, struct shmid_ds *buf);
```

- 当用shmget函数创建一段共享内存时，必须指定其 size；而如果引用一个已存在的共享内存，则将 size 指定为0 。

- 当一段共享内存被创建以后，它并不能被任何进程访问。必须使用shmat函数连接该共享内存到当前进程的地址空间，连接成功后把共享内存区对象映射到调用进程的地址空间，随后可像本地空间一样访问。

- shmdt函数是用来断开shmat建立的连接的。注意，这并不是从系统中删除该共享内存，只是当前进程不能再访问该共享内存而已。

- shmctl函数可以对共享内存执行多种操作，根据参数 cmd 执行相应的操作。常用的是IPC_RMID（从系统中删除该共享内存）。

### 3、例子

​        下面这个例子，使用了【共享内存+信号量+消息队列】的组合来实现服务器进程与客户进程间的通信。

1. 共享内存用来传递数据；

2. 信号量用来同步；
3. 消息队列用来 在客户端修改了共享内存后 通知服务器读取。

```c
// 服务端的示例代码：

#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>  // shared memory
#include<sys/sem.h>  // semaphore
#include<sys/msg.h>  // message queue
#include<string.h>   // memcpy

// 消息队列结构
struct msg_form {
    long mtype;
    char mtext;
};

// 初始化信号量
int init_sem(int sem_id, int value)
{
    union semun tmp;
    tmp.val = value;
    if(semctl(sem_id, 0,SETVAL, tmp) == -1)
    {
        perror("Init Semaphore Error");
        return -1;
    }
    return 0;
}

// P操作:
// 若信号量值为1，获取资源并将信号量值-1
// 若信号量值为0，进程挂起等待
int sem_p(int sem_id)
{
    struct sembuf sbuf;
    sbuf.sem_num = 0;
    sbuf.sem_op = -1;
    sbuf.sem_flg = SEM_UNDO;
    if(semop(sem_id, &sbuf, 1) == -1)
    {
        perror("P operation Error");
        return -1;
    }
    return 0;
}

// V操作：
//  释放资源并将信号量值+1
//  如果有进程正在挂起等待，则唤醒它们
int sem_v(int sem_id)
{
    struct sembuf sbuf;
    sbuf.sem_num = 0;
    sbuf.sem_op = 1;

sbuf.sem_flg = SEM_UNDO;
if(semop(sem_id, &sbuf, 1) == -1)
{
     perror("V operation Error");
     return -1;
}
return 0;

}

// 删除信号量集
int del_sem(int sem_id)
{
    union semun tmp;
    if(semctl(sem_id, 0, IPC_RMID, tmp) == -1)
    {
         perror("Delete Semaphore Error");
         return -1;
    }
    return 0;
}

// 创建一个信号量集
int creat_sem(key_t key)
{
    int sem_id;
    if((sem_id = semget(key, 1, IPC_CREAT|0666)) == -1) {
        perror("semget error");
        exit(-1);
    }
    init_sem(sem_id, 1);
    return sem_id;
}

int main()
{
    key_t key;
    int shmid, semid, msqid;
    char *shm;
    char data[] = "this isserver";
    struct shmid_ds buf1;
    struct msqid_ds buf2;
    struct msg_form msg;

// 获取key值
if((key = ftok(".",'z')) < 0) {
    perror("ftok error");
    exit(1);
}

// 创建共享内存
if((shmid = shmget(key, 1024, IPC_CREAT|0666)) == -1) {
    perror("Create Shared Memory Error");
     exit(1);
}

// 连接共享内存
shm = (char*)shmat(shmid, 0, 0);
if(*(int*)shm == -1) {
    perror("Attach Shared Memory Error");
    exit(1);
}

// 创建消息队列
if ((msqid = msgget(key, IPC_CREAT|0777)) == -1) {
     perror("msgget error");
     exit(1);
}

// 创建信号量
semid = creat_sem(key);

// 读数据
while(1)
{
    msgrcv(msqid, &msg, 1, 888, 0);
    if(msg.mtext == 'q')
        break;
    if(msg.mtext == 'r') {
   	    sem_p(semid);
        printf("%s\n",shm);
        sem_v(semid);
    }
}
// 断开连接
shmdt(shm);

shmctl(shmid, IPC_RMID, &buf1);
msgctl(msqid, IPC_RMID, &buf2);
del_sem(semid);
return 0;

}
        客户端的示例代码：

#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>  // shared memory
#include<sys/sem.h>  // semaphore
#include<sys/msg.h>  // message queue
#include<string.h>   // memcpy

// 消息队列结构
struct msg_form {
    long mtype;
    char mtext;
};

// P操作:
// 若信号量值为1，获取资源并将信号量值-1
// 若信号量值为0，进程挂起等待
int sem_p(int sem_id)
{
    struct sembuf sbuf;
    sbuf.sem_num = 0;
    sbuf.sem_op = -1;
    sbuf.sem_flg = SEM_UNDO;
    if(semop(sem_id, &sbuf, 1) == -1)
    {
         perror("P operation Error");
         return -1;
    }
    return 0;
}

// V操作：
//  释放资源并将信号量值+1
//  如果有进程正在挂起等待，则唤醒它们
int sem_v(int sem_id)
{
    struct sembuf sbuf;
    sbuf.sem_num = 0;
    sbuf.sem_op = 1;

sbuf.sem_flg = SEM_UNDO;
if(semop(sem_id,&sbuf, 1) == -1)
{
    perror("V operation Error");
    return -1;
}
return 0;

}

int main()
{
    key_t key;
    int shmid, semid, msqid;
    char *shm;
    struct msg_form msg;
    int flag = 1;

// 获取key值
if((key = ftok(".", 'z')) < 0) {
    perror("ftok error");
    exit(1);
}

// 获取共享内存
if((shmid = shmget(key, 1024, 0)) == -1) {
    perror("shmget error");
    exit(1);
}

// 连接共享内存
shm = (char*)shmat(shmid, 0, 0);
if(*(int*)shm == -1) {
     perror("Attach Shared Memory Error");
     exit(1);
}

// 创建消息队列
if ((msqid = msgget(key,0)) == -1) {
     perror("msgget error");
     exit(1);
}

// 获取信号量
if((semid = semget(key,0, 0)) == -1) {
     perror("semget error");
     exit(1);
}

// 写数据
   printf("***************************************\n");
   printf("*                 IPC                   *\n");
   printf("*Input r to send data toserver.  *\n");
   printf("*   Input q to quit.      *\n");
   printf("***************************************\n");

   while(flag) {
        char c;
        printf("Please input command: ");
        scanf("%c", &c);
        switch(c)
        {
            case 'r':
                printf("Data to send:");
                sem_p(semid);
                scanf("%s", shm);
                sem_v(semid);

​                while((c=getchar())!='\n'&& c!=EOF);
​                msg.mtype = 888;
​                msg.mtext = 'r';
​                msgsnd(msqid, &msg, sizeof(msg.mtext), 0);
​                break;
​           case 'q':
​                msg.mtype = 888;
​                msg.mtext = 'q';
​                msgsnd(msqid, &msg,sizeof(msg.mtext), 0);
​                flag = 0;
​                break;
​           default:
​                printf("Wrong input!\n");
​                while((c=getchar())!='\n'&& c!=EOF);
​    }

}
// 断开连接
shmdt(shm);
return 0;

}
```

​        注意：当scanf()输入字符或字符串时，缓冲区中遗留下了\n，所以每次输入操作后都需要清空标准输入的缓冲区。但是由于 gcc 编译器不支持fflush(stdin)（它只是标准C的扩展），所以我们使用了替代方案：

```c
while((c=getchar())!='\n' && c!=EOF);
```

## 六、IPC mapped memory

mapped memory and shared memory 有不同。

| name          | 名称     | different                                           |
| ------------- | -------- | --------------------------------------------------- |
| shared memory | 内存映射 | 除了IPC以外的应用。mapped memory 映射的是一个文件。 |
| mapped memory | 共享内存 | 是共享一段内存空间                                  |

### 1 内存存储映射I/O (Memory-mapped I/O)

- 1）内存存储映射I/O简写为mmap，也是比较常用的进程间通信方式。
- 2）mmap使一个磁盘文件与存储空间中的一个缓冲区相映射。于是当从缓冲区中取数据，就相当于读文件中的相应字节。于此类似，将数据存入缓冲区，则相应的字节就自动写入磁盘文件。这样，就可在不适用read和write函数的情况下，使用地址（指针）完成I/O操作。这个文件中个缓冲区也叫映射区。
- 3）使用这种方法，首先应通知内核，将一个指定文件映射到存储区域中。这个映射工作可以通过mmap函数来实现。
- 4）映射的情况类似下图，将一个文件中的空间映射到内存，这个空间可以是文件的所有空间或者部分空间，可以自行设置，通过映射后，内存地址空间也叫映射区。

### 2 详细过程

- 当CPU读取数据时，是由内存管理单元（MMU）管理的。MMU位于CPU与物理内存之间，它包含从虚地址向物理内存地址转化的映射信息。当CPU引用一个内存位置时，MMU决定哪些页需要驻留（通常通过移位或屏蔽地址的某些位）以及转化虚拟页号到物理页号。
- 当某个进程读取磁盘上的数据时，进程要求其缓冲通过read（）系统调用填满，这个系统调用导致内核想磁盘控制硬件发出一条命令要从磁盘获取数据。磁盘控制器通过DMA直接将数据写入内核的内存缓冲区，不需要CPU协助。当请求read（）操作时，一旦磁盘控制器完成了缓存的填写，内核从内核空间的临时缓存拷贝数据到进程指定的缓存中。
- 用户空间是常规进程所在的区域，该区域执行的代码不能直接访问硬件设备。内核空间是操作系统所在的区域，该区域可以与设备控制器通讯，控制用户区域进程的运行状态。
- 内存映射文件技术是操作系统提供的一种新的文件数据存取机制，利用内存映射文件技术，系统可以在内存空间中为文件保留一部分空间，并将文件映射到这块保留空间，一旦文件被映射后，操作系统将管理页映射缓冲以及高速缓冲等任务，而不需要调用分配、释放内存块和文件输入/输出的API函数，也不需要自己提供任何缓冲算法。
- 使用内存映射文件处理存储于磁盘上的文件时，将不必再对文件执行I/O 操作，这意味着在对文件进行处理时将不必再为文件申请并分配缓存，所有的文件缓存操作均由系统直接管理，由于取消了将文件数据加载到内存、数据从内存到文件的回写以及释放内存块等步骤，使得内存映射文件在处理大数据量的文件时能起到相当重要的作用。

### 3 ADT

```c
void *mmap(void *adrr, size_t length, int prot, int flags, int fd, off_t offset); 
/*
	功能：	将文件的所有空间或者部分空间映射到缓冲区，这个缓冲区也叫映射区。
	返回：	成功：返回创建的映射区首地址；失败：MAP_FAILED宏。
	参数：	
	addr: 	建立映射区的首地址，由Linux内核指定。使用时，直接传递NULL。
	length：欲创建映射区的大小。
	prot：	映射区权限，主要使用到PROT_READ、PROT_WRITE、PROT_READ|PROT_WRITE，其余自行man查看。
	flags：	标志位参数(常用于设定更新物理区域、设置共享、创建匿名映射区)。
		  	MAP_SHARED:  会将映射区所做的操作反映到物理设备（磁盘）上。
		  	MAP_PRIVATE: 映射区所做的修改不会反映到物理设备。
	fd： 	用来建立映射区的文件的文件描述符。
	offset：映射文件的偏移位置(必须是4k的整数倍)，默认偏移位置为0，表示映射整个文件大小。
*/
```

- mmap将一个文件或者其它对象映射进内存。文件被映射到多个页上，如果文件的大小不是所有页的大小之和，最后一个页不被使用的空间将会清零。 munmap执行相反的操作，删除特定地址区域的对象映射。

```c
int munmap(void *addr, size_t length);	
/*
	功能：将mmap映射的区域释放，类似malloc，free。
	成功：0； 失败：-1.
	参1：mmap返回的首地址。
	参2：mmap时创建的映射区长度。
*/
```

