#include <stdio.h>
#include <time.h>
#include <stdint.h>

int main()
{
    clock_t start1, start2, elapsed;
    uint8_t flag = 3;
    uint32_t i = 0;
    while(i++ < 100)
    {
        if(flag)
        {
            start1 = clock();
            if(flag != 3)
            {
                elapsed = start1 - start2;
                printf("elapsed = %d\n", elapsed);
            }
        }
        if(!flag)
        {
            start2 = clock();
            elapsed = start2 - start1;
            printf("elapsed = %d\n", elapsed);
        }

        flag = flag ? 0 : 1;

        usleep(10000);
    }

    return 0;
}
