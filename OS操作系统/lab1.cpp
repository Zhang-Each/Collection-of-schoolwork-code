#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <cstring>
#include <string>
#include <cstdio>

#define MAX_SIZE 100

using namespace std;

// 2020-2021 操作系统lab1_1 同步互斥实验
// author：张溢弛 3180103772


// 代表了车的四种行驶方向,结果后面没用上
enum direction {
    NORTH,
    WEST,
    SOUTH,
    EAST
};

// 表示方向的四个字符串，用于在print的时候方便查询
// 根据题意应该设定北西南东的方向顺序
const string direction_string[4] = {"north", "west", "south", "east"};


// 一个表示车的结构体，包含了车的编号和行驶方向
struct car {
    int car_direction;
    int car_id;
};

typedef struct car *pCar;

// 一些全局的互斥信号量和条件信号量
// 表示此时此刻车能否通行的互斥信号量
pthread_mutex_t can_cross;

// 表示此时此刻是否有死锁存在的互斥信号量
pthread_mutex_t is_dead_lock;

// 表示四个方向是否被车占用的互斥信号量，数组按照北西南东的顺序安排下标
pthread_mutex_t direction_lock[4];

// 一些条件信号量
// 用于给下一个方向的车发送一个可以通过的信号量，按照题意就是左边的车
pthread_cond_t next_direction_cond[4];
// 用于给同一方向的下一辆车发送信号量
pthread_cond_t car_cond[4];
pthread_cond_t solve_dead_lock;

// 一个表示小车的简易队列，图方便没有实现一个有严格意义上enqueue和dequeue数据结构
int queue[4][MAX_SIZE] = {0};
// 表示现在某个方向上排队的小车数量的数组
int now_number[4] = {0};
// 表示已经通过某个方向上小车的数量
int cur_number[4] = {0};
// 表明该方向是否有小车在等待
int is_waiting[4] = {0};
// 表示该方向路口处是否有车到达的数组
int car_arrived[4] = {0};
bool cross_dead = true;

// 几个重要的函数
void pthread_init();
void pthread_destroy();
void *car_thread(void *car);
void *dead_lock_thread(void *);

int main(int argc, char const *arg[]) {
    // 初始化一些信号量和全局数组
    pthread_init();

    // 读取输入的车辆信息，并对初始化一个表示每辆车行驶方向的数组
    string input;
    cin >> input;
    int car_num = strlen(input.c_str());
    char* car_direction = new char[car_num];
    for (int i = 0; i < car_num; i++) {
        car_direction[i] = input[i];
    }
    // 创建一系列的表示车辆的结构体，数量和输入的数量相同
    struct car car_flow[car_num];
    // 为每一辆车都创建一个自线程来运行决策函数
    pthread_t thread[car_num], dead_lock_detection;

    pthread_create(&dead_lock_detection, NULL, dead_lock_thread, NULL);
    for (int i = 0; i < car_num; i++) {
        // 给每一辆车分配一个编号，方便起见从0开始分配
        car_flow[i].car_id = i;
        // 读取车开过来的方向并对方向进行判断
        char direct = car_direction[i];
        // 0 - north
        // 1 - west
        // 2 - south
        // 3 - east
        // 更新每一个方向上的小车总数，也就是将小车放到队列的末尾，并设置结构体中的方向
        if (direct == 'n') {
            car_flow[i].car_direction = 0;
            queue[0][now_number[0]++] = i;
        } else if (direct == 'w') {
            car_flow[i].car_direction = 1;
            queue[1][now_number[1]++] = i;
        } else if (direct == 's') {
            car_flow[i].car_direction = 2;
            queue[2][now_number[2]++] = i;
        } else if (direct == 'e') {
            car_flow[i].car_direction = 3;
            queue[3][now_number[3]++] = i;
        }
        // 为每一辆小车创建一个线程
        pthread_create(&thread[i], NULL, car_thread, (void*)&car_flow[i]);
    }
    // 启动每一个线程，开始小车的调度
    for (int i = 0; i < car_num; i++) {
        pthread_join(thread[i], NULL);
    }

    // 程序运行结束之后销毁所有的信号量
    pthread_destroy();
    return 0;
}


/**
 * 代表一辆车的行动的函数，程序为每一辆车都调用这个函数，并进行多线程的处理
 * @param car_pointer 一个车结构体的地址，用于读取一辆车的信息
 * @return void类型，线程结束没有返回值
 */

void *car_thread(void *car_pointer) {
    // 先用结构体的地址把结构体从内存中读回来，并获取id和方向等信息
    pCar p_car = (pCar)car_pointer;
    int id, direct;
    id = p_car->car_id + 1;
    direct = p_car->car_direction;

    // 给当前方向的互斥信号量进行signal操作
    pthread_mutex_lock(&direction_lock[direct]);

    // cout << car_arrived[direct] << "car-id::" << id << endl;
    // 如果前面有车在等待通行或者队列中该方向的前面还有车就先等待其释放代表前面有车在等待的信号量
    while (car_arrived[direct] != 0 || queue[direct][cur_number[direct]] != p_car->car_id) {
        pthread_cond_wait(&car_cond[direct], &direction_lock[direct]);
    }
    // 此时表明车正式进入十字路口的待行区，对两个数组进行标记
    is_waiting[direct] = 1;
    car_arrived[direct] = 1;

    // 打印进入十字路口待行区的车辆信息
    // string arrive_info = "Car " + to_string(id) + " is arriving at the cross in " + direction_string[direct] + '\n';
    // cout << arrive_info;
    printf("car %d arrive the %s\n", id, direction_string[direct].c_str());
    pthread_mutex_lock(&can_cross); // 此时车准备通行，对代表能否通行的互斥信号量上锁

    // 获取当前方向的左右两个方向
    int left, right;
    left = (direct + 3) % 4;
    right = (direct + 1) % 4;


    bool dead = true;
    //sleep(1);
    pthread_mutex_lock(&is_dead_lock);
    //遍历四个方向，如果都有小车在等待通行就表明存在死锁
    for (int i : is_waiting) {
        if (!i) {
            dead = false; //判断条件是假如四个方向上都有车在等待就是死锁
        }
    }
    pthread_mutex_unlock(&is_dead_lock);

    // 如果存在死锁就打印死锁的相关信息
    if (dead) {
        sleep(1);
        string dead_lock_info = "There is a dead lock in the crossing road! Now give a signal to north!";
                 //+ direction_string[direct];
        // cout << dead_lock_info;
        printf("Dead lock detected!!!! %s\n", dead_lock_info.c_str());
    }

    // 如果没有死锁并且右边方向上存在等待通行的车，就要先等待其释放信号量
    while (!dead && is_waiting[right]) {
        pthread_cond_wait(&next_direction_cond[direct], &can_cross);
    }
    
    // 小车通过路口并释放信号量
    is_waiting[direct] = 0;
    pthread_mutex_unlock(&direction_lock[direct]);

    //string leave_info = "Car " + to_string(id) + " passed the cross in direction "
            //+ direction_string[direct] + '\n';
    //cout << leave_info;
    // 打印通过的信息并释放信号量
    sleep(1);
    printf("car %d pass the %s\n", id, direction_string[direct].c_str());
    pthread_mutex_unlock(&can_cross);

    // 如果左边有车就给他发送一个信号量让其通行
    if (is_waiting[left] == 1) {
        pthread_cond_signal(&next_direction_cond[left]);
    }

    // 等待1s防止处理过快，并修改是否有车等待的状态
    sleep(1);
    car_arrived[direct] = 0;
    // 通过路口的车数量增加
    cur_number[direct]++;
    // 给同一个方向中的下一辆车发送信号让其通信
    pthread_cond_broadcast(&car_cond[direct]);
    pthread_exit(NULL);
}


/**
 * 用于在程序开始的时候创建所有的互斥信号量和条件信号量
*/
void pthread_init() {
    pthread_mutex_init(&is_dead_lock, nullptr);
    pthread_mutex_init(&can_cross, nullptr);

    for (auto & i : direction_lock) {
        pthread_mutex_init(&i, nullptr);
    }
    for (int i = 0; i < 4; i++) {
        pthread_cond_init(&next_direction_cond[i], nullptr);
        pthread_cond_init(&car_cond[i], nullptr);
    }
    pthread_cond_init(&solve_dead_lock, nullptr);
}


/**
 * 用于在程序结束的时候销毁所有的互斥信号量和条件信号量
 */
void pthread_destroy() {
    pthread_mutex_destroy(&is_dead_lock);
    pthread_mutex_destroy(&can_cross);

    for (int i = 0; i < 4; i++) {
        pthread_mutex_destroy(&direction_lock[i]);
        pthread_cond_destroy(&next_direction_cond[i]);
        pthread_cond_destroy(&car_cond[i]);
    }
    pthread_cond_destroy(&solve_dead_lock);
}

void *dead_lock_thread(void *) {
    while (sleep(1)) { //每隔一段时间检测一次是否存在死锁
        for (int i : is_waiting) {
            if (!i) {
                cross_dead = false; //判断条件是假如四个方向上都有车在等待就是死锁
                pthread_cond_signal(&solve_dead_lock);
            }
        }
    }
    pthread_exit(nullptr);
}
