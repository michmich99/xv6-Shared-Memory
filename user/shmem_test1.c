#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(void)
{
    int cpid;
    int ppid;
    uint64 dst_va; 

    ppid = getpid();   

    cpid = fork();

    //TODO: check if the fork is OK

    //printf("PID = %d\n", pid);
    char *hello = malloc(12);
    memcpy(hello, "Hello child", 12);

    if (cpid != 0)
    {
        //parent
        // char *hello = (char *)sbrk(12);

        // char* p = (char *)0x13ff0;
        // printf("from father: %s\n", p);

        // memcpy(hello, "Hello child", 12);
        // strcpy(hello, "Hello child");

	
	    // printf("from father: %s\n", hello);

        // dst_va = map_shared_pages(ppid, cpid, hello, 12); 

        // printf(" Dst VA %d\n", dst_va);
        // printf("father: %s\n", (char *)dst_va);

        //printf(" %s\n", (char *)dst_va);

        wait(0);
    }
    else
    {
        //child
        
        // sleep(10);
        dst_va = map_shared_pages(ppid, getpid(), hello, 12);
        printf(" Dst VA %d\n", dst_va);

        // uint64 address = (uint64)"Hello, World!"; // Use the address of a string
        // char *str = (char *)address;
        // printf("%s\n", str);
        // char *str = (char *)((uint64))address);

        // uint64 temp = 16396;
        // char* p = (char *)temp;
        // printf("here: %s\n", p);

        char* p = (char *)dst_va;
        printf("here: %s\n", p);

        exit(0);
    }

    return 0;
}


