#include <stdio.h>

// 버블 정렬 구현해보자

// 오름차순 정렬
void BubbleSort(int DataSet[], int length)
{
    int temp = 0;

    for (int i = 0; i < length - 1; i++)
    {
        for (int j = 0; j < length - (i + 1); j++)
        {
            if (DataSet[j] > DataSet[j + 1])
            {
                temp = DataSet[j + 1];
                DataSet[j + 1] = DataSet[j];
                DataSet[j] = temp;
            }
        }
    }
}

/*
    정렬되어 있는 경우 루프를 취소하고 빠져나오도록 알고리즘을 개선
*/
void BubbleSort_remake(int DataSet[], int length)
{
    int temp = 0;
    int cnt = 0;

    for (int i = 0; i < length - 1; i++)
    {
        for (int j = 0; j < length - (i + 1); j++)
        {
            if (DataSet[j] > DataSet[j + 1])
            {
                temp = DataSet[j + 1];
                DataSet[j + 1] = DataSet[j];
                DataSet[j] = temp;
                cnt++;
            }
        }
        if (cnt == 0)
        {
            printf("이미 정렬된 배열 입니다.");
            break;
        }
    }
}

int main(void)
{
    int arr[10] = {3, 2, 5, 1, 7, 30, 13, 8, 9, 6};
    int length = sizeof(arr) / sizeof(int);
    BubbleSort(arr, length);
    for (int i = 0; i < length; i++)
    {
        printf("%d ", arr[i]);
    }
}