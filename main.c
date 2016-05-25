#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>

#define LEN 10000
#define FUN_NUM 7
extern int errno;

extern void psort(void *, int, int, int (*)(const void *, const void *));
extern void isort(void *, int, int, int (*)(const void *, const void *));
extern void ssort(void *, int, int, int (*)(const void *, const void *));
extern void shell(void *, int, int, int (*)(const void *, const void *));
extern void msort(void *, int, int, int (*)(const void *, const void *));
extern void quick(void *, int, int, int (*)(const void *, const void *));

static int cmp(int *pa, int *pb);
static long diff_tv(struct timeval, struct timeval);

int main(int argc, char *argv[])
{
    int i, arry[LEN];
    srand(time(0));
    for(i = 0; i < LEN; i++)
    {
        arry[i] = rand();
    }

    int *parry[FUN_NUM] = {NULL};
    for(i = 0; i < FUN_NUM; i++)
    {
        parry[i] = (int *)malloc(LEN * sizeof(int));
        if(parry[i] == NULL)
        {
            fprintf(stderr, "%s:%s:%s\n", __FILE__, __LINE__, strerror(errno));
            goto Free;
        }
        memcpy((char *)parry[i], (char *)arry, LEN * sizeof(int));
    }

    struct timeval start_tv, end_tv;
    gettimeofday(&start_tv, NULL);
    psort(parry[0], LEN, sizeof(int), cmp);
    gettimeofday(&end_tv, NULL);
    fprintf(stdout, "psort:%lu\n", diff_tv(start_tv, end_tv));

    gettimeofday(&start_tv, NULL);
    isort(parry[1], LEN, sizeof(int), cmp);
    gettimeofday(&end_tv, NULL);
    fprintf(stdout, "isort:%lu\n", diff_tv(start_tv, end_tv));

    gettimeofday(&start_tv, NULL);
    ssort(parry[2], LEN, sizeof(int), cmp);
    gettimeofday(&end_tv, NULL);
    fprintf(stdout, "ssort:%lu\n", diff_tv(start_tv, end_tv));

    gettimeofday(&start_tv, NULL);
    shell(parry[3], LEN, sizeof(int), cmp);
    gettimeofday(&end_tv, NULL);
    fprintf(stdout, "shell:%lu\n", diff_tv(start_tv, end_tv));

    gettimeofday(&start_tv, NULL);
    msort(parry[4], LEN, sizeof(int), cmp);
    gettimeofday(&end_tv, NULL);
    fprintf(stdout, "msort:%lu\n", diff_tv(start_tv, end_tv));

    gettimeofday(&start_tv, NULL);
    quick(parry[5], LEN, sizeof(int), cmp);
    gettimeofday(&end_tv, NULL);
    fprintf(stdout, "quick:%lu\n", diff_tv(start_tv, end_tv));

    gettimeofday(&start_tv, NULL);
    qsort(parry[6], LEN, sizeof(int), cmp);
    gettimeofday(&end_tv, NULL);
    fprintf(stdout, "qsort:%lu\n", diff_tv(start_tv, end_tv));


    for(i = 0; i < LEN; i++)
    {
        //printf("%d%c", arry[i], (i + 1) % 10 ? ',' : '\n');
    }

Free:
    for(i = 0; i < FUN_NUM; i++)
    {
        free(parry[i]);
    }

    return 0;
}

static int cmp(int *pa, int *pb)
{
    return *pa - *pb;
}

static long diff_tv(struct timeval start_tv, struct timeval end_tv)
{
    return (end_tv.tv_sec - start_tv.tv_sec) * 1000000 + (end_tv.tv_usec - start_tv.tv_usec);
}

