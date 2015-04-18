#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SORTCOUNT   87

int *randArray(int len, int maxNum)
{
    int i, *num;
    srand((int)time(0));
    num = (int *)calloc(sizeof(int), len);
    for(i=0;i<len;i++)
    {
        num[i] = rand()%(maxNum + 1);
    }
    return num;
}

void printArray(int *array, int len, int check)
{
    int i;
    for(i=0;i<len;)
    {
        if(check && i>0 && (array[i] < array[i-1]))
            printf("error sort\n");

        if((i>0) && (i%10 == 0))
            printf("\n");
        printf("%5d  ",array[i++]);
    }
    printf("\n-----------------------------------------\n");
}

void swap(int *array, int v1, int v2)
{
    int tmp;
    if(v1 == v2)
        return;
    tmp = array[v1];
    array[v1] = array[v2];
    array[v2] = tmp;
}

void bubbleSort(int *array, int len)
{
    int i,j,swapped;
    swapped = 1;
    for(i=0; i<len-1 && swapped; i++)
    {
        swapped = 0;
        for(j=0; j<len-i-1; j++)
        {
            if(array[j] > array[j+1])
            {
                swapped = 1;
                swap(array, j, j+1);
            }
        }
    }
}

void insertSort(int *array, int len)
{
    int i,j,tmp;
    for(i=1;i<len;i++)
    {
        tmp = array[i];
        for(j=i-1; j>=0 && array[j]>tmp; j--)
        {
            array[j+1] = array[j];
        }
        array[j+1] = tmp;
    }
}

void shellSort(int *array, int len)
{
    int i,j,tmp,gap;
    for(gap=len/2; gap>0; gap/=2)
    {
        for(i=gap; i<len; i++)
        {
            tmp = array[i];
            for(j=i-gap; j>=0 && array[j]>tmp; j-=gap)
            {
                array[j+gap] = array[j];
            }
            array[j+gap] = tmp;
        }
    }
}

int partition(int *array, int len)
{
    int i,pivot,smallLen;
    smallLen = 0;
    pivot = array[0];
    for(i=1;i<len;i++)
    {
        if(array[i] < pivot)
            swap(array, i, ++smallLen);
    }
    swap(array, 0, smallLen);
    return smallLen;
}

void quickSort(int *array, int len)
{
    int smallLen;
    if(len <= 1)
        return;
    smallLen = partition(array, len);
    quickSort(array, smallLen);
    quickSort(&array[smallLen+1], len-smallLen-1);
}

void selectionSort(int *array, int len)
{
    int i,j,min;
    for(i=0;i<len-1;i++)
    {
        min = i;
        for(j=i+1;j<len;j++)
        {
            if(array[j] < array[min])
                min = j;
        }
        swap(array, i, min);
    }
}

void merge(int *array, int *tmp, int start, int mid, int end)
{
    int i = start, j = mid+1, k = start;
    while(i != mid+1 && j != end+1)
    {
        if(array[i] < array[j])
            tmp[k++] = array[i++];
        else
            tmp[k++] = array[j++];
    }
    while(i != mid+1)
        tmp[k++] = array[i++];
    while(j != end+1)
        tmp[k++] = array[j++];

    for(i=start;i<=end;i++)
        array[i] = tmp[i];

}

void msort(int *array, int *tmp, int start, int end)
{
    int mid;
    if(start<end)
    {
        mid = (start+end)/2;
        msort(array, tmp, start, mid);
        msort(array, tmp, mid+1, end);
        merge(array, tmp, start, mid, end);
    }
}

void mergeSort(int *array, int len)
{
    int *tmp = malloc(sizeof(int)*len);
    msort(array, tmp, 0, len-1);
}

int main()
{
    int *array = randArray(SORTCOUNT, 1000);
    printArray(array, SORTCOUNT, 0);
/*
    bubbleSort(array, SORTCOUNT);
    printArray(array, SORTCOUNT, 1);
    insertSort(array, SORTCOUNT);
    printArray(array, SORTCOUNT, 1);
    shellSort(array, SORTCOUNT);
    printArray(array, SORTCOUNT, 1);
    quickSort(array, SORTCOUNT);
    printArray(array, SORTCOUNT, 1);
    selectionSort(array, SORTCOUNT);
    printArray(array, SORTCOUNT, 1);
*/
    mergeSort(array, SORTCOUNT);
    printArray(array, SORTCOUNT, 1);


    free(array);
    return 0;
}
