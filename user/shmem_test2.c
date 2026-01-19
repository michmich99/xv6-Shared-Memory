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

    char *hello = malloc(12);


    //TODO: check if the fork is OK

    if (cpid != 0)
    {
        //parent
        
	    // printf(" %s\n", hello);

        // printf(" Dst VA %d\n", dst_va);

        //printf(" %s\n", (char *)dst_va);
        sleep(2);

        printf("test2: %s\n", hello);

        wait(0);
    }
    else
    {
        //child
        // uint64 temp = 16396;
        printf("%d/n", sbrk(0));
        dst_va = map_shared_pages(ppid, getpid(), hello, 12); 
        memcpy((char *)dst_va, "Hello daddy", 12);

        sleep(2);

        unmap_shared_pages(getpid(), (char *)dst_va, 12);

        char *mallocCheck = malloc(1000);
        exit(0);
    }

    return 0;








}