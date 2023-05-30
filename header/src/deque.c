#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include <deque.h>

// Structs for a stack and a queue respectively
typedef struct deque
{
    void **deque;

    long size;
    long count;
} deque;

deque *init_deque(void **values, long size, long count)
{
    deque *retval = malloc(sizeof(deque));
    
    retval->deque = values == NULL && size != 0 ? malloc(sizeof(void *) * size) : values;
    if (retval->deque == NULL && values != NULL)
    {
        dlt_deque(retval);
        return NULL;
    }
    

    retval->size = values == NULL || size < 0 ? 0 : size;
    retval->count = values == NULL || count < 0 ? 0 : count;

    return retval;
}

void **dlt_deque(deque *deque)
{
    // Stores the list of pointers
    void **retval = deque->deque;
    
    deque->deque = NULL;
    deque->count = 0;
    deque->size = 0;

    free(deque);

    return retval;
}

int push(deque *stack, void *value)
{
    if (stack == NULL || value == NULL)
    {
        return -1;
    }
    
    if (stack->count++ <= stack->size)
    {
        stack->deque[stack->count-1] = value;
        return 0;
    }
    

    void **new_mem = realloc(stack->deque, sizeof(void *) * (stack->size++));
    if (new_mem == NULL)
    {
        return -2;
    }
    
    new_mem[stack->count] = value;
    
    free(stack->deque);
    stack->deque = NULL;

    stack->deque = new_mem;

    return 0;
}

void *pop(deque *stack)
{
    if (stack == NULL)
    {
        return NULL;
    }
    
    void *popped_val = stack->deque[stack->count--];
    void **new_mem = realloc(stack->deque, sizeof(void *) * (stack->size--));
    if (new_mem == NULL)
    {
        return NULL;
    }
    
    free(stack->deque);
    stack->deque = NULL;

    stack->deque = new_mem;
    
    return popped_val;
}

int queue(deque *queue, void *value)
{
    if (queue == NULL || value == NULL)
    {
        return -1;
    }
    
    if (queue->count++ <= queue->size)
    {
        queue->deque[queue->count-1] = value;
        return 0;
    }


    void **new_mem = realloc(queue->deque, sizeof(void *) * (queue->size++));
    if (new_mem == NULL)
    {
        return -2;
    }
    
    new_mem[queue->count] = value;
    
    free(queue->deque);
    queue->deque = NULL;

    queue->deque = new_mem;
    queue->count++;

    return 0;
}

void *dequeue(deque *queue)
{
    if (queue == NULL || queue->size == 0 || queue->count == 0)
    {
        return NULL;
    }
    
    void *popped_val = queue->deque[0];
    void **new_mem = realloc(queue->deque, sizeof(void *) * (queue->size--));
    if (new_mem == NULL)
    {
        return NULL;
    }
    
    free(queue->deque);
    queue->deque = NULL;

    queue->deque = new_mem;
    queue->count--;
    
    return popped_val;
}

// Accesses a certain element in the array in a deque using index
void *get_element(deque *dequeue, long index)
{
    void *retval = index > (dequeue->count - 1) ? NULL : dequeue->deque[index];

    return retval;
}

// Accesses count member of deque
void *get_count(deque *dequeue)
{
    return dequeue->count;
}

void **search(deque *dequeue, void *value, bool same(const void *, const void *))
{
    for (long i = 0, count = dequeue->count; i < count; i++)
    {
        void *push_val = same(dequeue->deque[i], value) ? dequeue->deque[i] : NULL;
        int retval = push(dequeue, push_val);
        if (retval == -2)
        {
            return NULL;
        }
    }

    return dlt_deque(dequeue);
}