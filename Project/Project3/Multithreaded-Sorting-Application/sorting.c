#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

int *num, *ans;
int begin, mid, end;
void *sorting(void *param);
void *merging(void *param);
int main(int argc, char *argv[])
{
    pthread_t tid1, tid2, tid3;
    pthread_attr_t attr;
    begin = 0;
    end = argc - 1;
    mid = (begin + end) / 2;

    num = (int *)malloc(end * sizeof(int));
    ans = (int *)malloc(end * sizeof(int));

    void *flag_1 = "1";
    void *flag_2 = "2";

    if (argc < 2)
    {
        fprintf(stderr, "Please input at least one number!\n");
        return -1;
    }
    for (int i = 1; i <= end; ++i)
    {
        num[i - 1] = atoi(argv[i]);
        if (num[i - 1] == 0 && strcmp(argv[i], "0") != 0)
        {
            fprintf(stderr, "Please input valid numbers!\n");
            return -1;
        }
    }

    pthread_attr_init(&attr);
    pthread_create(&tid1, &attr, sorting, flag_1);
    pthread_create(&tid2, &attr, sorting, flag_2);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_create(&tid3, &attr, merging, NULL);
    pthread_join(tid3, NULL);

    for (int i = begin; i < end; ++i)
    {
        printf("%d ", ans[i]);
    }
    printf("\n");
    free(num);
    free(ans);
    return 0;
}

void *sorting(void *param)
{
    int left, right;
    if (atoi(param) == 1)
    {
        left = begin;
        right = mid;
    }
    else
    {
        left = mid;
        right = end;
    }
    int len = right - left;
    int gap;
    int tmp;
    int k;
    for (gap = len / 2; gap > 0; gap /= 2)
    {
        for (int i = left; i < right; ++i)
        {
            int tmp = num[i];
            int j = i - gap;
            while(j>=left && tmp<=num[j])
            {
                num[j + gap] = num[j];
                j -= gap;
            }
            num[j + gap] = tmp;
        }
    }
    pthread_exit(0);
}

void *merging(void *param)
{
    int a = begin, b = mid;
    int i = begin;
    while (a < mid && b < end)
    {
        if (num[a] <= num[b])
        {
            ans[i] = num[a];
            i++;
            a++;
        }
        else
        {
            ans[i] = num[b];
            i++;
            b++;
        }
    }
    while (a < mid)
    {
        ans[i] = num[a];
        i++;
        a++;
    }
    while (b < end)
    {
        ans[i] = num[b];
        i++;
        b++;
    }
    pthread_exit(0);
}