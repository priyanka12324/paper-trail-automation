#ifndef CIRCULAR_QUEUE_HPP
#define CIRCULAR_QUEUE_HPP

#include <cstddef>
#include <string>
#include <vector>

struct QueueItem {
    std::string cipher_text;
    long long nonce;
    QueueItem* next;

    QueueItem(const std::string& cipher, long long value);
};

class CircularQueue {
public:
    CircularQueue();
    ~CircularQueue();

    CircularQueue(const CircularQueue&) = delete;
    CircularQueue& operator=(const CircularQueue&) = delete;

    void enqueue(const std::string& cipher, long long nonce);
    bool empty() const;
    std::size_t size() const;
    bool front(QueueItem& out) const;
    bool dequeue(QueueItem& out);
    std::vector<QueueItem> snapshot() const;

private:
    QueueItem* front_;
    QueueItem* rear_;
    std::size_t size_;
};

#endif
