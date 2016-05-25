#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

extern int errno;

static void quick_fun(void *, int, int, int
    , int (*)(const void *, const void *), void *);
static void swap(void *, int, int, int, void *);

void quick(void *arry, int num, int size
    , int (*cmp)(const void *, const void *))
{
    void *ptmp = malloc(size);
    if(ptmp == NULL)
    {
        fprintf(stderr, "%s:%s:%s\n", __FILE__, __LINE__, strerror(errno));
        return;
    }

    quick_fun(arry, 0, num, size, cmp, ptmp);

    free(ptmp);
    return;
}

static void quick_fun(void *arry, int left, int right, int size
    , int (*cmp)(const void *, const void *), void *ptmp)
{
    if(left >= right)
    {
        return;
    }

    int i, last = left, mid = (left + right) / 2;
    swap(arry, last, mid, size, ptmp);
    char *pleft, *pcurr;
    for(i = left + 1; i < right; i++)
    {
        pleft = (char *)arry + left * size;
        pcurr = (char *)arry + i * size;
        if(cmp(pleft, pcurr) > 0)
        {
            swap(arry, ++last, i, size, ptmp);
        }
    }
    swap(arry, left, last, size, ptmp);
    quick_fun(arry, left, last, size, cmp, ptmp);
    quick_fun(arry, last + 1, right, size, cmp, ptmp);
    return;
}

static void swap(void *arry, int left, int right, int size, void *ptmp)
{
    char *pl = (char *)arry + left * size;
    char *pr = (char *)arry + right * size;
    if(pl == pr)
    {
        return;
    }

    memcpy(ptmp, pl, size);
    memcpy(pl, pr, size);
    memcpy(pr, ptmp, size);
    return;
}

