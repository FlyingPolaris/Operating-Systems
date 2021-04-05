#include "banker.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int read_file()
{
    FILE *f;
    f = fopen("test.txt", "r");
    if (f == NULL)
    {
        fprintf(stderr, "File not found!\n");
        return -1;
    }
    else
    {
        for (int i = 0; i < NUMBER_OF_CUSTOMERS; ++i)
            for (int j = 0; j < NUMBER_OF_RESOURCES; ++j)
            {
                fscanf(f, "%d", &maximum[i][j]);
                fgetc(f);
            }
        for (int i = 0; i < NUMBER_OF_CUSTOMERS; ++i)
            for (int j = 0; j < NUMBER_OF_RESOURCES; ++j)
            {
                need[i][j] = maximum[i][j];
                allocation[i][j] = 0;
            }
        return 0;
    }
}

int request_resources(int num, int request[])
{
    if (num < 0 || num >= NUMBER_OF_CUSTOMERS)
    {
        fprintf(stderr, "Error customer id!\n");
        return -1;
    }
    int available_[NUMBER_OF_RESOURCES];
    int allocation_[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
    int need_[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];

    for (int i = 0; i < NUMBER_OF_RESOURCES; ++i)
    {
        available_[i] = available[i];
        for (int j = 0; j < NUMBER_OF_CUSTOMERS; ++j)
        {
            allocation_[j][i] = allocation[j][i];
            need_[j][i] = need[j][i];
        }
    }

    for (int i = 0; i < NUMBER_OF_RESOURCES; ++i)
    {
        allocation_[num][i] += request[i];
        need_[num][i] += request[i];
        available_[i] -= request[i];
    }

    int safe = check_safe(allocation_, need_, available_);
    if (safe == 0)
    {
        for (int i = 0; i < NUMBER_OF_RESOURCES; ++i)
        {
            allocation[num][i] += request[i];
            need[num][i] += request[i];
            available[i] -= request[i];
        }
        printf("Safe. Resource allocation succeeded.\n");
        return 0;
    }
    else
    {
        fprintf(stderr, "Unsafe! Resource allocation failed!\n");
        return -1;
    }
}

int release_resources(int num, int release[])
{
    if (num < 0 || num >= NUMBER_OF_CUSTOMERS)
    {
        fprintf(stderr, "Error customer id!\n");
        return -1;
    }
    for (int i = 0; i < NUMBER_OF_RESOURCES; ++i)
    {
        if (allocation[num][i] < release[i])
        {
            fprintf(stderr, "Don't have so much to release!\n");
            return -1;
        }
    }
    for (int i = 0; i < NUMBER_OF_RESOURCES; ++i)
    {
        available[i] += release[i];
        need[num][i] += release[i];
        allocation[num][i] -= release[i];
    }
    return 0;
}

void print_resources()
{
    printf("Available:\n");
    printf("  \tA\tB\tC\tD\n");
    printf("  \t");
    for (int i = 0; i < NUMBER_OF_RESOURCES; ++i)
    {
        printf("%d\t", available[i]);
    }
    printf("\n");
    printf("\n");
    printf("Maximum:\n");
    printf("  \tA\tB\tC\tD\n");
    for (int i = 0; i < NUMBER_OF_CUSTOMERS; ++i)
    {
        printf("P%d\t", i);
        for (int j = 0; j < NUMBER_OF_RESOURCES; ++i)
        {
            printf("%d\t", maximum[i][j]);
        }
    }
    printf("\n");
    printf("\n");
    printf("Allocation:\n");
    printf("  \tA\tB\tC\tD\n");
    for (int i = 0; i < NUMBER_OF_CUSTOMERS; ++i)
    {
        printf("P%d\t", i);
        for (int j = 0; j < NUMBER_OF_RESOURCES; ++i)
        {
            printf("%d\t", allocation[i][j]);
        }
    }
    printf("\n");
    printf("\n");
    printf("Need:\n");
    printf("  \tA\tB\tC\tD\n");
    for (int i = 0; i < NUMBER_OF_CUSTOMERS; ++i)
    {
        printf("P%d\t", i);
        for (int j = 0; j < NUMBER_OF_RESOURCES; ++i)
        {
            printf("%d\t", need[i][j]);
        }
    }
    printf("\n");
}

int check_safe(int allocation[][NUMBER_OF_RESOURCES], int need[][NUMBER_OF_RESOURCES], int available[])
{
    int safe = 0;
    int finish[NUMBER_OF_CUSTOMERS];
    int work[NUMBER_OF_RESOURCES];
    for (int i = 0; i < NUMBER_OF_CUSTOMERS; ++i)
    {
        finish[i] = 0;
    }
    for (int i = 0; i < NUMBER_OF_RESOURCES; ++i)
    {
        work[i] = available[i];
    }
    int all_finished;
    int all_checked;
    while (1)
    {
        all_finished = 1;
        all_checked = 1;
        for (int i = 0; i < NUMBER_OF_CUSTOMERS; ++i)
        {
            if (finish[i] == 0)
                all_finished = 0;
            else
                continue;

            int flag = 1;
            for (int j = 0; j < NUMBER_OF_RESOURCES; ++j)
            {
                if (need[i][j] > work[j])
                    flag = 0;
            }

            if (flag)
            {
                all_checked = 0;
                for (int j = 0; j < NUMBER_OF_RESOURCES; ++j)
                {
                    work[j] += allocation[i][j];
                    finish[i] = 1;
                }
            }
        }

        if (all_checked || all_finished)
            break;
    }
    if (all_finished == 1)
        return 0;
    else
        return -1;
}

int main(int argc, char *argv[])
{
    if (argc != 5)
    {
        fprintf(stderr, "Error input!\n");
        return -1;
    }

    for (int i = 1; i <= NUMBER_OF_RESOURCES; ++i)
    {
        available[i - 1] = atoi(argv[i]);
    }

    if (read_file() != 0)
        return -1;

    while (1)
    {
        char ch[10];
        scanf("%s", ch);
        if (strcmp(ch, "exit") == 0)
        {
            break;
        }
        else if (strcmp(ch, "*") == 0)
        {
            print_resources();
            continue;
        }
        else if (strcmp(ch, "RQ") == 0)
        {
            int num;
            scanf("%d", &num);
            int request[NUMBER_OF_RESOURCES];
            for (int i = 0; i < NUMBER_OF_RESOURCES; ++i)
            {
                scanf("%d", &request[i]);
            }
            request_resources(num, request);
        }
        else if (strcmp(ch, "RL") == 0)
        {
            int num;
            scanf("%d", &num);
            int release[NUMBER_OF_RESOURCES];
            for (int i = 0; i < NUMBER_OF_RESOURCES; ++i)
            {
                scanf("%d", &release[i]);
            }
            release_resources(num, release);
        }
        else
        {
            fprintf(stderr, "Error input!\n");
        }
    }

    return 0;
}
