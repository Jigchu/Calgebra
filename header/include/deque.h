#pragma once

typedef struct deque deque;

deque *init_deque(void **values, long size, long count);
void **dlt_deque(deque *deque);
int push(deque *stack, void *value);
void *pop(deque *stack);
int queue(deque *queue, void *value);
void *dequeue(deque *queue);
void *get_element(deque *dequeue, long index);
void *get_count(deque *dequeue)
void **search(deque *dequeue, void *value, bool same(const void *, const void *));