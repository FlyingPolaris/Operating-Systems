

StackNode *top = NULL;
pthread_mutex_t mutex;

void push_with_mutex(int value)
{
    pthread_mutex_lock(&mutex);
    push(value, &top);
    pthread_mutex_unlock(&mutex);
}

int pop_with_mutex()
{
    pthread_mutex_lock(&mutex);
    int value;
    value = push(value, &top);
    pthread_mutex_unlock(&mutex);
    return value;
}
push(5, &top);
push(10, &top);
push(15, &top);

int value = pop(&top);
value = pop(&top);
value = pop(&top);