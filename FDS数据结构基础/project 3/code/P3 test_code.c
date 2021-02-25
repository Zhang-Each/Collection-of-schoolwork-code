#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MaxRecord 10000
#define MaxQuery 80000

void insert(int element, int *destination, int position);

int main()
{
    int N, K, n, randomcar, randomhour, randomminute, randomsecond, randomstatus, i, j, check[MaxQuery];
    scanf("%d%d", &N, &K);/*Input the number of the records and queries.*/
    srand((unsigned)time(NULL));
    char plate_number[MaxRecord][8];
    n = rand() % N;/*Generate a random number which is smaller than N to ensure repetitive cases to happen.*/
    /*Generating n plates randomly. We use numbers larger than 9 but smaller than 36 to represent 'A' to 'Z'.*/
    for(i = 0; i < n; i++) {
        for(j = 0; j < 7; j++) {
            int temp1 = rand() % 36;
            if(temp1 < 10) plate_number[i][j] = temp1 + '0';
            else plate_number[i][j] = temp1 - 10 + 'A';
        }
        plate_number[i][7] = '\0';
    }
    for(i = 0; i < N; i++) {
        randomcar = rand() % n;
        randomhour = rand() % 24;
        randomminute = rand() % 60;
        randomsecond = rand() % 60;
        randomstatus = rand() % 2;
        printf("%s ", plate_number[randomcar]);
        printf("%02d:%02d:%02d ", randomhour, randomminute, randomsecond);
        if(randomstatus == 0) printf("out\n");
        else printf("in\n");
    }
    for(i = 0; i < K; i++) {
        randomhour = rand() % 24;
        randomminute = rand() % 60;
        randomsecond = rand() % 60;
        int time  = randomhour * 3600 + randomminute * 60 + randomsecond;
        insert(time, check, i);
    }
    for(i = 0; i < K; i++) printf("%02d:%02d:%02d\n", check[i] / 3600, check[i] % 3600 / 60, check[i] % 60);
    system("pause");
    return 0;
}

void insert(int element, int *destination, int position)
{
    if(position == 0) {
        destination[position] = element;
        return;
    }
    int temp1, temp2;
    for(temp1 = 0; temp1 < position; temp1++) {
        if(destination[temp1] > element) break;
    }
    for(temp2 = position; temp2 > temp1; temp2--) {
        destination[temp2] = destination[temp2 - 1];
    }
    destination[temp1] = element;
}
