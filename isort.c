#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

extern int errno;

void isort(void *arry, int num, int size
    , int (*cmp)(const void *, const void *))
{
    void *ptmp = malloc(size);
    if(ptmp == NULL)
    {
        fprintf(stderr, "%s:%s:%s\n", __FILE__, __LINE__, strerror(errno));
        return;
    }

    int i, j;
    for(i = 1; i < num; i++)
    {
        char *pfront, *pcurr; 
        for(j = i
            ; j > 0 && (pfront = (char *)arry + (j - 1) * size\
, pcurr = (char *)arry + j * size, cmp(pfront, pcurr) > 0)
            ; j--)
        {
            memcpy(ptmp, pfront, size);
            memcpy(pfront, pcurr, size);
            memcpy(pcurr, ptmp, size);
        }
    }

    free(ptmp);
    return;
}

