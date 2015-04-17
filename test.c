#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
char* pointers[1024*1024];
int main() {
	int size;
	clock_t start,end;
	start = clock();
	end = start;
	for (size = 0; size < 1024; size += 5) {
		printf("%d.	size %d begin\n",size,size);
		int i;
		int max = 1024*1024;
		for (int i = 0; i < max; i ++) {
			pointers[i] = (char*)malloc(size);
			int j;
			for (j = 0; j < size; j ++) {
				pointers[i][j] = 'a';	
			}
		}
		printf("	alloc %d bytes\n",max*size);
		if (size == 1020) sleep(45);// just to see memory usage in monitor
		for (int i = 0; i < max; i ++) {
			free(pointers[i]);
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
