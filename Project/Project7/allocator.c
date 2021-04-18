#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int total_memory;

typedef struct Hole
{
    int begin;
    int end;
    int size;
    int used;
    char *name;
} Hole;

typedef struct Node
{
    struct Node *next;
    struct Hole hole;
} Node;

Node *head;

void first_fit(char *name, int size)
{
    Node *p = head;
    while (1)
    {
        if (p->hole.used == 0 && p->hole.size > size)
        {
            Node *q = (Node *)malloc(sizeof(Node));
            p->hole.used = 1;
            q->hole.used = 0;
            p->hole.name = name;
            q->hole.name = "";
            q->hole.end = p->hole.end;
            p->hole.end = p->hole.begin + size;
            p->hole.size = size;
            q->hole.begin = p->hole.end;
            q->hole.size = q->hole.end - q->hole.begin;
            q->next = p->next;
            p->next = q;
            break;
        }
        else if (p->hole.used == 0 && p->hole.size == size)
        {
            p->hole.used = 1;
            p->hole.name = name;
            break;
        }
        else
        {
            if (p->next != NULL)
            {
                p = p->next;
            }
            else
            {
                fprintf(stderr, "Error: Failed! No suitable space!\n");
                break;
            }
        }
    }
}

void best_fit(char *name, int size)
{
    Node *p = head;
    int minsize = __INT_MAX__;
    Node *minnode = NULL;
    while (1)
    {
        if (p->hole.used == 0 && p->hole.size >= size)
        {
            if (p->hole.size < minsize)
            {
                minsize = p->hole.size;
                minnode = p;
            }
        }
        if (p->next != NULL)
        {
            p = p->next;
        }
        else
        {
            if (minsize == __INT_MAX__)
                fprintf(stderr, "Error: Failed! No suitable space!\n");
            break;
        }
    }
    if (minsize != __INT_MAX__)
    {
        p = minnode;
        if (minsize == size)
        {
            p->hole.used = 1;
            p->hole.name = name;
        }
        else
        {
            Node *q = (Node *)malloc(sizeof(Node));
            p->hole.used = 1;
            q->hole.used = 0;
            p->hole.name = name;
            q->hole.name = "";
            q->hole.end = p->hole.end;
            p->hole.end = p->hole.begin + size;
            p->hole.size = size;
            q->hole.begin = p->hole.end;
            q->hole.size = q->hole.end - q->hole.begin;
            q->next = p->next;
            p->next = q;
        }
    }
}

void worst_fit(char *name, int size)
{
    Node *p = head;
    int maxsize = -1;
    Node *maxnode = NULL;
    while (1)
    {
        if (p->hole.used == 0 && p->hole.size >= size)
        {
            if (p->hole.size > maxsize)
            {
                maxsize = p->hole.size;
                maxnode = p;
            }
        }

        if (p->next != NULL)
        {
            p = p->next;
        }
        else
        {
            if (maxsize == -1)
                fprintf(stderr, "Error: Failed! No suitable space!\n");
            break;
        }
    }
    if (maxsize != -1)
    {
        p = maxnode;
        if (maxsize == size)
        {
            p->hole.used = 1;
            p->hole.name = name;
        }
        else
        {
            Node *q = (Node *)malloc(sizeof(Node));
            p->hole.used = 1;
            q->hole.used = 0;
            p->hole.name = name;
            q->hole.name = "";
            q->hole.end = p->hole.end;
            p->hole.end = p->hole.begin + size;
            p->hole.size = size;
            q->hole.begin = p->hole.end;
            q->hole.size = q->hole.end - q->hole.begin;
            q->next = p->next;
            p->next = q;
        }
    }
}

void release(char *name)
{
    Node *p = head->next;
    Node *q = head;

    while (1)
    {
        if (q == head && strcmp(q->hole.name, name) == 0)
        {
            if (p == NULL)
            {
                q->hole.begin = 0;
                q->hole.end = total_memory;
                q->hole.used = 0;
                q->hole.size = total_memory;
                q->hole.name = "";
                break;
            }
            else if (p->hole.used == 1)
            {
                q->hole.used = 0;
                q->hole.name = "";
                break;
            }
            else
            {
                q->hole.end = p->hole.end;
                q->hole.size = q->hole.end;
                q->hole.name = "";
                q->hole.used = 0;
                q->next = p->next;
                free(p);
            }
        }

        if (p == NULL)
        {
            fprintf(stderr, "Error: Failed! No that process!\n");
            break;
        }

        if (strcmp(p->hole.name, name) == 0)
        {
            Node *r = p->next;
            if (q->hole.used == 0)
            {
                if (r == NULL)
                {
                    q->hole.end = p->hole.end;
                    q->hole.size = q->hole.end - q->hole.begin;
                    q->next = p->next;
                    free(p);
                }
                else if (r->hole.used == 1)
                {
                    q->hole.end = p->hole.end;
                    q->hole.size = q->hole.end - q->hole.begin;
                    q->next = p->next;
                    free(p);
                }
                else
                {
                    q->hole.end = r->hole.end;
                    q->hole.size = q->hole.end - q->hole.begin;
                    q->next = r->next;
                    free(p);
                    free(r);
                }
            }
            else
            {
                if (r == NULL)
                {
                    p->hole.used = 0;
                    p->hole.name = "";
                }
                else if (r->hole.used == 1)
                {
                    p->hole.used = 0;
                    p->hole.name = "";
                }
                else
                {
                    p->hole.used = 0;
                    p->hole.name = "";
                    p->hole.end = r->hole.end;
                    p->hole.size = p->hole.end - p->hole.begin;
                    p->next = r->next;
                    free(r);
                }
            }
            break;
        }
        else
        {
            if (p->next != NULL)
            {
                q = q->next;
                p = p->next;
            }
            else
            {
                fprintf(stderr, "Error: Failed! No that process!\n");
                break;
            }
        }
    }
}

void compact()
{
    int offset = 0;
    Node *q = head;
    Node *p = head->next;
    if (head->hole.used == 0)
    {
        offset += head->hole.size;
    }
    while (1)
    {
        if (p->next == NULL)
        {
            if (p->hole.used == 0)
            {
                p->hole.begin -= offset;
                p->hole.size += offset;
            }
            else
            {
                p->hole.begin -= offset;
                p->hole.end -= offset;
                Node *end = (Node *)malloc(sizeof(Node));
                end->hole.begin = p->hole.end;
                end->hole.end = total_memory;
                end->hole.size = end->hole.end - end->hole.begin;
                end->hole.used = 0;
                end->hole.name = "";
                p->next = end;
                end->next = NULL;
            }
            break;
        }
        if (p->hole.used == 0)
        {
            offset += p->hole.size;
            q->next = p->next;
            Node *freeNode = p;
            p = p->next;
            free(freeNode);
        }
        else
        {
            p->hole.begin -= offset;
            p->hole.end -= offset;
            p = p->next;
            q = q->next;
        }
    }
    if (head->hole.used == 0 && head->next != NULL)
    {
        Node *freeNode = head;
        head = head->next;
        free(freeNode);
    }
}

void status_report()
{
    Node *p = head;
    while (1)
    {
        printf("Addresses ");
        if (p == head)
            printf("[%d:%d] ", p->hole.begin, p->hole.end);
        else
            printf("[%d,%d] ", p->hole.begin + 1, p->hole.end);

        if (p->hole.used == 0)
            printf("Unused \n");
        else
            printf("Process %s\n", p->hole.name);

        if (p->next != NULL)
            p = p->next;
        else
            break;
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Error: Please input right arguments!\n");
        return -1;
    }
    head = (Node *)malloc(sizeof(Node));
    head->next = NULL;

    total_memory = atoi(argv[1]);
    head->hole.begin = 0;
    head->hole.end = total_memory;
    head->hole.size = total_memory;
    head->hole.used = 0;
    head->hole.name = "";
    char buffer[20];

    while (1)
    {
        printf("allocator>");
        scanf("%s", buffer);
        if (strcmp(buffer, "RQ") == 0)
        {
            Node *q = (Node *)malloc(sizeof(Node));

            char *name_of_process = (char *)malloc(10 * sizeof(char));
            scanf("%s", name_of_process);
            int size_of_process;
            scanf("%d", &size_of_process);
            char *type = (char *)malloc(3 * sizeof(char));
            scanf("%s", type);

            if (strcmp(type, "F") == 0)
            {
                first_fit(name_of_process, size_of_process);
            }
            else if (strcmp(type, "B") == 0)
            {
                best_fit(name_of_process, size_of_process);
            }
            else if (strcmp(type, "W") == 0)
            {
                worst_fit(name_of_process, size_of_process);
            }
        }

        else if (strcmp(buffer, "RL") == 0)
        {
            char *name_of_process = (char *)malloc(10 * sizeof(char));
            scanf("%s", name_of_process);
            release(name_of_process);
            free(name_of_process);
        }
        else if (strcmp(buffer, "C") == 0)
        {
            compact();
        }
        else if (strcmp(buffer, "STAT") == 0)
        {
            status_report();
        }
        else if (strcmp(buffer, "X") == 0)
        {
            break;
        }
        else
        {
            fprintf(stderr, "Error: Please input right commands!\n");
        }
    }

    return 0;
}