#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
char* pointers[1024*1024];

int main() {
	clock_t start,end;
	start = clock();
	end = start;
    int max = 1024*1024;
    int i;
    for (i = 0; i < max; i ++) {
		pointers[i] = (char*)malloc(i%5);
		int j;
        int k = i%5;
		for (j = 0; j < k; j ++) {
			pointers[i][j] = 'a';
		}
    }printf(" begin i=%d\n",i);
    for (i = 0; i < max; i ++) {
        if (i%2==0) {
            free(pointers[i]);
        }
    }
    int size;
	int total_mem;
	for (size = 10; size < 4096; size += 41) {
		printf("%d.	size %d begin\n",size,size);
		int i;
        total_mem = 0;
		for (i = 0; i < max; i ++) {
			if ( (i + size)%2 == 0) {
				pointers[i] = (char*)malloc(i%size);
                total_mem += i%size;
				int j;
                int k = i%size;
				for (j = 0; j < k; j ++) {
					pointers[i][j] = 'a';	
				}
			}
		}
		printf("	alloc %d Mbytes\n",total_mem*2/(1024*1024));
		//if (size == 1020) sleep(45);// just to see memory usage in monitor
		for (i = 0; i < max; i ++) {
			if ( (i + size)%2 == 1) {
				free(pointers[i]);
			}
		}
		clock_t temp = clock();
		printf("	size %d end, use %lus\n",size,(temp-end)/CLOCKS_PER_SEC);
		end = temp;
	}
	total_mem /= 2;// because half of the memory has been freed.
	//test5 starts here
	for (i = 1; i < max; i += 2) {
		if ( (i-1)%1024 == 0 ) {
			pointers[i] = (char*)malloc(1024000);
			total_mem += 1024000;
			int j;
			for (j = 0; j < 1024000; j ++) pointers[i][j] = 'a';
		}
	}
	printf("final alloc %d Mbytes\n",total_mem(1024*1024));
	sleep(50);
	end = clock();
	int total_time = (end-start)/CLOCKS_PER_SEC;
	printf("total time is %ds\n",total_time);
	return 0;
}
