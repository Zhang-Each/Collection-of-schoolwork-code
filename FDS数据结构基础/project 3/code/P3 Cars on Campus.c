#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MaxRecord 10000 /*The max number of the records been recorded.*/
#define MaxQuery 80000  /*The max number of the queries being recorded.*/
#define MaxTime 86400   /*The number of seconds per day.*/

/*An array to save every record.*/
struct Node {
    char plate_number[8];/*The plate number of the car in this record.*/
	int t;				 /*The time when the record is recorded.*/
	int status;			 /*The status of the car when the record is recorded.*/
}Record[MaxRecord];

/*An array to save current number of cars on campus of every second in a day.*/
int EverySecond[MaxTime];
/*An array to save the points of time needed to calculate the number of cars on campus.*/
int check[MaxQuery];

/*The function used to compare the two data structures when we call the function "qsort" included in stdlib.h.*/
int compare(const void *a, const void *b);
/*The function to avoid the successive "in" status.*/
int In(int *i, int j);
/*The function to avoid the successive "out" status.*/
int Out(int *i, int j);

int main()
{
	int N, K, i, j, maxtime = -1, top = 0;
	char status[4], plate_number[MaxRecord][8];
	scanf("%d%d", &N, &K);
	for(i = 0; i < N; ++i) {
	    int hour, minute, second;
		/*Input the information of each record.*/
		scanf("%s %d:%d:%d %s", Record[i].plate_number, &hour, &minute, &second, status);
		/*To save the times of comparation, transfer the clock into seconds.*/
		Record[i].t = hour * 3600 + minute * 60 + second;
		/*If the status is "in", the status of the record equals to 1, if not, the status equals to 0.*/
		if(status[0] == 'i') Record[i].status = 1;
		else Record[i].status = 0;
	}
	/*Sort the records in alphabetic order and time order, respectively.*/
	qsort(Record, N, sizeof(struct Node), compare);
	i = 0;/*Initial the template variable.*/
	while(i < N) {
		int m = i, currenttime = 0;
		char temp_number[8];
		/*To find the index of the last record of this car.*/
		while((m < N) && (strcmp(Record[i].plate_number, Record[m].plate_number) == 0)) m++;
		/*To save the plate number of the current car temporarily.*/
		strcpy(temp_number, Record[i].plate_number);
		/*To calculate the total time the car has been parked on campus.*/
		while(1) {
			int *tmp = &i;
			/*If we cannot find the next "in" status, get out from current loop.*/
			if(In(tmp, m) == 0) break;
			int j = i;
			/*If we cannot find the next "out" status, get out from current loop.*/
			if(Out(tmp, m) == 0) break;
			/*Now, the j-th record records a car has come in the campus while the i-th record records a car has get
			  out the campus. So increase EverySecond[Record[j].t] by 1, and decrease EverySecond[Record[i].t] by 1.*/
			EverySecond[Record[j].t]++;
			EverySecond[Record[i].t]--;
			/*Add the parking time to currenttime.*/
			currenttime += Record[i].t - Record[j].t;
		}
		/*To compare current time with the max time, if the current time is smaller than the max time, jump to the next record, if the result is equation, push the current plate number to the stack named "plate_number", if the result is bigger, clear all the records in the stack and push the current plate number to the bottom of the stack.*/
		if(currenttime > maxtime) {
			maxtime = currenttime;
			top = 0;
			strcpy(plate_number[top++], temp_number);
        }
		else if(currenttime == maxtime) {
			strcpy(plate_number[top++], temp_number);
        }
	}
	/*Now, the elements in the array named "EverySecond" save the change of the number of the cars on campus, so to flatter our aim, we need to add the number of cars of the last second to the next second.*/
	for(i = 1; i < MaxTime; ++i) EverySecond[i] += EverySecond[i - 1];   
	for(i = 0; i < K; i++) {
		int hour, minute, second;
		scanf("%d:%d:%d", &hour, &minute, &second);
		check[i] = hour * 3600 + minute * 60 + second;
	}
	for(i = 0; i < K; i++) printf("%d\n", EverySecond[check[i]]);
	for(i = 0; i < top; i++) printf("%s ",plate_number[i]);
	/*Tranfer the max time from the form of seconds into the form of clock.*/
	printf("%02d:%02d:%02d\n", maxtime / 3600, maxtime % 3600 / 60, maxtime % 60);
	system("pause");
	return 0;
}

/*If the plate number of record "a" is larger than the number of record "b" in alphabetic order, return 1, if smaller, return -1 and when it comes to an equation, compare the time order of the two records.*/
int compare(const void *a, const void *b)
{
	struct Node *c = (struct Node *)a;  
	struct Node *d = (struct Node *)b; 
	int p = strcmp(c->plate_number, d->plate_number);    
	if(p < 0) return -1; 
	if(p > 0) return 1;
	return c->t - d->t;
}

/*To ignore the successive "in" statuses and stop at the last one. If we cannot find such a record, return back 0, otherwise, return 1.*/
int In(int *i, int j)
{
	while((*i < j) && (!Record[*i].status)) (*i)++;   
	if(*i >= j) return 0;
	while((*i < j) && (Record[*i].status)) (*i)++;   
	(*i)--;
    return 1;
}

/*To find the next fisrt "out" status. If we don't get to the end of the records of the current car, return 1, otherwise, return 0.*/
int Out(int *i, int j)
{
	while((*i < j) && (Record[*i].status)) (*i)++;
    return *i < j;
}