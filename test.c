#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
char* pointers[1024*1024];
int total_mem = 0;
int main() {
	clock_t start,end;
	start = clock();
	end = start;
    int max = 1024*1024;
    int i;
    for (i = 0; i < max; i ++) {
		pointers[i] = (char*)malloc(5);
		int j;
		for (j = 0; j < 5; j ++) {
			pointers[i][j] = 'a';
		}
    }printf(" begin i=%d\n",i);
    for (i = 0; i < max; i ++) {
        if (i%2==0) {
            free(pointers[i]);
        }
    }
    int size;
	for (size = 10; size < 1024; size += 5) {
		printf("%d.	size %d begin\n",size,size);
		int i;
        
		for (i = 0; i < max; i ++) {
			if ((i+size)%2==0) {
				pointers[i] = (char*)malloc(size);
				int j;
				for (j = 0; j < size; j ++) {
					pointers[i][j] = 'a';	
				}
			}
		}
		printf("	alloc %d bytes\n",size*max);
		if (size == 1020) sleep(45);// just to see memory usage in monitor
		for (i = 0; i < max; i ++) {
			if ((i+size)%2==1) {
				free(pointers[i]);
			}
		}
		clock_t temp = clock();
		printf("	size %d end, use %lus\n",size,(temp-end)/CLOCKS_PER_SEC);
		end = temp;
	}
	end = clock();
	int total_time = (end-start)/CLOCKS_PER_SEC;
	printf("total time is %ds\n",total_time);
	return 0;
}
