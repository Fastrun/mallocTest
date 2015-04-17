#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
char* pointers[1024*1024];
int max = 1024*1024;
clock_t start,end;
int total_mem;
void small_work_load_loop() {
    int size;
    
    for (size = 10; size < 4096; size += 41) {
        printf("%d.	size %d begin\n",size,size);
        int i;
        total_mem = 0;
        for (i = 0; i < max; i ++) {
            if ( (i + size)%2 == 0) {//the last time is odd
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
                if (size == 4069 && i < 5) printf("i=%d",i);
            }
        }
        clock_t temp = clock();
        printf("	size %d end, use %lus\n",size,(temp-end)/CLOCKS_PER_SEC);
        end = temp;
    }
    
}
void small_work_load() {
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
    small_work_load_loop();
}

void large_work_load() {
    int i;
    int mb = 1024*1024;
	for (i = 0; i < max; i += 2) {
		if ( i%1024 == 0 ) {
			pointers[i] = (char*)malloc(mb);
			total_mem += mb;
			int j;
			for (j = 0; j < mb; j ++) pointers[i][j] = 'a';
		}
	}
    

}
void free_large_work_load() {
    int i;
    for (i = 0; i < max; i += 2) {
        if ( i%1024 == 0 ) {
            free(pointers[i]);
        }
    }
}
int main() {
	
	start = clock();
	end = start;
    
    small_work_load();
	//total_mem /= 2;// because half of the memory has been freed.
	//test5 starts here
    large_work_load();
	printf("final alloc %d Mbytes\n",total_mem/(1024*1024));
	sleep(50);
    free_large_work_load();
    small_work_load_loop();
    large_work_load();
    printf("final alloc %d Mbytes\n",total_mem/(1024*1024));
    sleep(150);
	end = clock();
	int total_time = (end-start)/CLOCKS_PER_SEC;
	printf("total time is %ds\n",total_time);
	return 0;
}
