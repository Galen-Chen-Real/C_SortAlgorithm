#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

extern int errno;

void psort(void *arry, int num, int size
    , int (*cmp)(const void *, const void *))
{
    void *ptmp = malloc(size);
    if(ptmp == NULL)
    {
        fprintf(stderr, "%s:%s:%s\n", __FILE__, __LINE__, strerror(errno));
        return;
    }

    int i, j;
    for(i = num - 1; i > 0; i--)
    {
        for(j = 1; j <= i; j++)
        {
            char *pfront = (char *)arry + (j - 1) * size;
            char *pcurr = (char *)arry + j * size;
            if(cmp(pfront, pcurr) > 0)
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

