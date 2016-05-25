#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

extern int errno;

static void recursion(void *, int, int, int, void *
    , int (*)(const void *, const void *));
static void merge(void *, int, int, int, int, void *
    , int (*cmp)(const void *, const void *));

void msort(void *arry, int num, int size
    , int (*cmp)(const void *, const void *))
{
    void *ptmp = malloc(num * size);

    if(ptmp == NULL)
    {
        fprintf(stderr, "%s:%s:%s\n", __FILE__, __LINE__, strerror(errno));
        return;
    }

    recursion(arry, 0, num, size, ptmp, cmp);

    free(ptmp);
    return;
}

static void recursion(void *arry, int left, int right, int size, void *ptmp
    , int (*cmp)(const void *, const void *))
{
    if(left >= right)
    {
        return;
    }

    int mid = (left + right) / 2;
    recursion(arry, left, mid, size, ptmp, cmp);
    recursion(arry, mid + 1, right, size, ptmp, cmp);
    merge(arry, left, mid, right, size, ptmp, cmp);
    return;
}

static void merge(void *arry, int left, int mid, int right, int size
    , void *ptmp, int (*cmp)(const void *, const void *))
{
    int a, b, m;
    char *pa, *pb, *pm;

    a = left;
    b = mid;
    m = left;
    while(a < mid && b < right)
    {
        pa = (char *)arry + a * size;
        pb = (char *)arry + b * size;
        pm = (char *)ptmp + m * size;
        if(cmp(pa, pb) > 0)
        {
            memcpy(pm, pb, size);
            b++;
        }
        else
        {
            memcpy(pm, pa, size);
            a++;
        }
        m++;
    }
    
    while(a < mid)
    {
        pa = (char *)arry + a * size;
        pm = (char *)ptmp + m * size;
        memcpy(pm, pa, size);
        a++;
        m++;
    }
    while(b < right)
    {
        pb = (char *)arry + b * size;
        pm = (char *)ptmp + m * size;
        memcpy(pm, pb, size);
        b++;
        m++;
    }

    pa = (char *)arry + left * size;
    pm = (char *)ptmp + left * size;
    memcpy(pa, pm, (right - left) * size);
    return;
}

