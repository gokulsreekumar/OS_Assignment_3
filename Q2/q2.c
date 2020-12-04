#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Change Input File Here
// "sample_input1" is Example Discussed in Class

#define INPUT_FILE_NAME "sample_input1"

// n = Number of Procedure
// m = Number of Resources

int *copy(int *x, int r, int c)
{
    int *temp = (int *)calloc(r * c, sizeof(int));
    for (int i = 0; i < r; i += 1)
        for (int j = 0; j < c; j += 1)
            *(temp + i * c + j) = *(x + i * c + j);
    return temp;
}

void printMatrix(int *x, int r, int c)
{
    for (int i = 0; i < r; i += 1)
    {
        for (int j = 0; j < c; j += 1)
            printf("%d ", *(x + i * c + j));
        printf("\n");
    }
}

int *getSafeState(int *rem, int *alloc, int *avail, int n, int m)
{
    int *safeSeq = (int *)calloc(n, sizeof(int));

    // Making Copies to use
    int *r = copy(rem, n, m);
    int *a = copy(alloc, n, m);
    int *av = copy(avail, 1, m);

    int safeProc, i, j, k, safe;
    for (k = 0; k < n; k += 1)
    {
        safeProc = -1;
        for (i = 0; i < n; i += 1)
        {
            safe = 1;
            for (j = 0; j < m; j += 1)
            {
                if (*(r + i * m + j) > av[j])
                {
                    safe = 0;
                    break;
                }
            }
            if (safe == 1)
            {
                safeProc = i;
                break;
            }
        }
        if (safeProc != -1)
        {
            safeSeq[k] = safeProc + 1;
            for (j = 0; j < m; j += 1)
            {
                av[j] += *(a + safeProc * m + j) + *(r + safeProc * m + j);
                *(r + safeProc * m + j) = INT_MAX;
                *(a + safeProc * m + j) = -1;
            }
        }
        else
        {
            for (int p = 0; p < n; p += 1)
                safeSeq[i] = -1;
        }
    }
    free(a);
    free(r);
    free(av);
    return safeSeq;
}

int checkSafe(int *seq, int *rem, int *alloc, int *avail, int n, int m)
{
    int *r = copy(rem, n, m);
    int *a = copy(alloc, n, m);
    int *av = copy(avail, 1, m);

    int safe, i, j, k;

    for (i = 0; i < n; i += 1)
    {
        k = seq[i];
        for (j = 0; j < m; j += 1)
        {
            if (*(r + k * m + j) > av[j])
            {
                free(a);
                free(r);
                free(av);
                return 0;
            }
        }
        for (j = 0; j < m; j += 1)
        {
            av[j] += *(a + k * m + j) + *(r + k * m + j);
            *(r + k * m + j) = INT_MAX;
            *(a + k * m + j) = -1;
        }
    }

    free(a);
    free(r);
    free(av);
    return 1;
}

int main()
{
    FILE *f;

    int n, m, i, j, flag;

    f = fopen(INPUT_FILE_NAME, "r");
    fscanf(f, "%d", &n);
    printf("Number of Processes Read From Input File: %d\n", n);
    fscanf(f, "%d", &m);
    printf("Number of Resources Read From Input File: %d\n",m);

    int *allocTable = (int *)calloc(n * m, sizeof(int));
    int *maxTable = (int *)calloc(n * m, sizeof(int));
    int *needTable = (int *)calloc(n * m, sizeof(int));
    int *avail = (int *)calloc(m, sizeof(int));
    int *input_sequence = (int *)calloc(n, sizeof(int));
    int *request_sequence = (int *)calloc(m, sizeof(int));
    int *res;

    // Read Available Resources
    printf("\nAvailable Resources read from input File...");
    for (i = 0; i < m; i += 1)
        fscanf(f, "%d", avail + i);

    // Read AllocTable
    printf("\nAllocTable Read From input File...");
    for (i = 0; i < n; i += 1)
        for (j = 0; j < m; j += 1)
            fscanf(f, "%d", allocTable + i * m + j);

    // Read MaxTable
    printf("\nMaxTable Read from input File...");
    for (i = 0; i < n; i += 1)
        for (j = 0; j < m; j += 1)
            fscanf(f, "%d", maxTable + i * m + j);

    // Calculate needTable
    for (i = 0; i < n; i += 1)
        for (j = 0; j < m; j += 1)
            *(needTable + i * m + j) = *(maxTable + i * m + j) - *(allocTable + i * m + j);

    // Calculate Remaining Resources
    for (i = 0; i < n; i += 1)
        for (j = 0; j < m; j += 1)
            avail[j] -= *(allocTable + i * m + j);

    printf("\n\n");
    printf("----------------------------\n");
    printf("Available Resources \n");
    printMatrix(avail, 1, m);
    printf("\n");
    printf("----------------------------\n");
    printf("Alloc Table \n");
    printMatrix(allocTable, n, m);
    printf("\n");
    printf("----------------------------\n");
    printf("Max Table \n");
    printMatrix(maxTable, n, m);
    printf("\n");
    printf("----------------------------\n");
    printf("Need Table \n");
    printMatrix(needTable, n, m);
    printf("\n");
    printf("----------------------------\n");

    char ch = 'y';
    while (ch != 't' || ch == 'T')
    {
        fscanf(f, "%c", &ch);
        switch (ch)
        {
        case 'a':
            res = getSafeState(needTable, allocTable, avail, n, m);
            printf("A Safe Sequence: \n");
            for (i = 0; i < n; i += 1)
                printf("%d ", res[i]);
            printf("\n");
            printf("\n");
            break;
        case 'b':
            printf("Sequence Read From File for Checking Safe:\n");
            for (i = 0; i < n; i += 1)
            {
                fscanf(f, "%d", input_sequence + i);
                printf("%d ", *(input_sequence + i));
                input_sequence[i] -= 1;
            }
            printf("\n");
            if (checkSafe(input_sequence, needTable, allocTable, avail, n, m))
                printf("SAFE STATE\n\n");
            else
                printf("NOT SAFE STATE\n\n");
            break;
        case 'c':
            printf("Request Resources Read From File: \n");
            for (i = 0; i < m; i += 1)
            {
                fscanf(f, "%d", request_sequence + i);
                printf("%d ", *(request_sequence + i));
            }
            printf("\n");
            flag = 1;
            for (j = 0; j < m; j += 1)
            {
                if (avail[j] < request_sequence[j])
                {
                    flag = 0;
                    break;
                }
            }
            if (flag == 1)
                printf("REQUEST IS SAFE TO BE GRANTED\n\n");
            else
                printf("REQUEST IS NOT SAFE TO BE GRANTED\n\n");
            break;
        default:
            break;
        }
    }
}