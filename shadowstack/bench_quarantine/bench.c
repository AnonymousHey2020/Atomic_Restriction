#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

#define M 100

void foo(int k)
{
    int i, j;
    for (i = 0; i < k; i++)
    {
        for (j = 0; j < k; j++)
        {
            /* code */
        }
    }
}

int main(int argc, char* argv[])
{
    int k = (int)(argv[1][0] - 48);
    float f = (float)(k/10);
    struct timeval start;
    struct timeval end;
    unsigned long diff;
    for (int n = 0; n < 10; n++)
    {
        for (int i = 0; i < M; i++)
        {
            for (int j = 1; j < 100; j++)
            {
                if (i < M * f)
                    foo(j);
                else
                    foo1(j);
            }
        }
    }
    for (int n = 0; n < 10; n++)
    {
        gettimeofday(&start, NULL);
        for (int i = 0; i < M; i++)
        {
            for (int j = 1; j < 100; j++)
            {
                if (i < M * f)
                    foo(j);
                else
                    foo1(j);
            }
        }
        gettimeofday(&end, NULL);
        diff = (1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec);
        printf("%ld\n", diff);
    }

    return 0;
}