#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

extern int errno;

void shell(void *arry, int num, int size
    , int (*cmp)(const void *, const void *))
{
    void *ptmp = malloc(size);
    if(ptmp == NULL)
    {
        fprintf(stderr, "%s:%s:%s\n", __FILE__, __LINE__, strerror(errno));
        return;
    }

    int gap, i, j;
    char *pfront, *pcurr;
    for(gap = num / 2; gap > 0; gap /= 2)
    {
        for(i = gap; i < num; i++)
        {
            for(j = i - gap
                ; j > 0 && (pfront = (char *)arry + j * size\
, pcurr = (char *)arry + (j + gap) * size, cmp(pfront, pcurr) > 0)
                ; j -= gap)
            {
                memcpy(ptmp, pfront, size);
                memcpy(pfront, pcurr, size);
                memcpy(pcurr, ptmp, size);
            }
        }
    }

    free(ptmp);
    return;
}

