#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

extern int errno;

void ssort(void *arry, int num, int size, int (*cmp)(const void *, const void *))
{
    void *ptmp = malloc(size);
    if(ptmp == NULL)
    {
        fprintf(stderr, "%s:%s:%s\n", __FILE__, __LINE__, strerror(errno));
        return;
    }

    int i, j, min;
    char *pmin, *pcurr;
    for(i = 0; i < num; i++)
    {
        min = i;
        for(j = i + 1; j < num; j++)
        {
            pmin = (char *)arry + min * size;
            pcurr = (char *)arry + j * size;
            if(cmp(pmin, pcurr) > 0)
            {
                min = j;
            }
        }
        
        if(min == i)
        {
            continue;
        }
        pcurr = (char *)arry + i * size;
        memcpy(ptmp, pcurr, size);
        memcpy(pcurr, pmin, size);
        memcpy(pmin, ptmp, size);
    }

    free(ptmp);
    return;
}

