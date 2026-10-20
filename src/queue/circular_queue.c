#include "queue/circular_queue.h"
#include <stdlib.h>

int cq_init(CircularQueue *q, size_t capacity) {
    if (!q || capacity == 0) return -1;
    q->data = (uint8_t *)malloc(capacity);
    if (!q->data) return -1;
    q->capacity = capacity;
    q->front = 0;
    q->size = 0;
    return 0;
}

void cq_free(CircularQueue *q) {
    if (!q) return;
    free(q->data);
    q->data = NULL;
    q->capacity = q->front = q->size = 0;
}

int cq_is_empty(const CircularQueue *q) { return q->size == 0; }
int cq_is_full(const CircularQueue *q)  { return q->size == q->capacity; }
size_t cq_size(const CircularQueue *q)  { return q->size; }

int cq_enqueue(CircularQueue *q, uint8_t value) {
    if (cq_is_full(q)) return -1;
    q->data[(q->front + q->size) % q->capacity] = value;
    q->size++;
    return 0;
}

int cq_dequeue(CircularQueue *q, uint8_t *out) {
    if (cq_is_empty(q)) return -1;
    *out = q->data[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->size--;
    return 0;
}

void cq_rotate_left(CircularQueue *q, size_t k) {
    if (q->size < 2) return;
    k %= q->size;
    while (k--) {
        uint8_t v;
        cq_dequeue(q, &v);
        cq_enqueue(q, v);
    }
}

void cq_rotate_right(CircularQueue *q, size_t k) {
    if (q->size < 2) return;
    k %= q->size;
    cq_rotate_left(q, q->size - k);
}
