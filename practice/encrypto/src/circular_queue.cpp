#include "circular_queue.hpp"

QueueItem::QueueItem(const std::string& cipher, long long value)
    : cipher_text(cipher), nonce(value), next(nullptr) {}

CircularQueue::CircularQueue() : front_(nullptr), rear_(nullptr), size_(0) {}

CircularQueue::~CircularQueue() {
    while (!empty()) {
        QueueItem* old_front = front_;
        if (size_ == 1) {
            front_ = nullptr;
            rear_ = nullptr;
        } else {
            front_ = front_->next;
            rear_->next = front_;
        }
        delete old_front;
        --size_;
    }
}

void CircularQueue::enqueue(const std::string& cipher, long long nonce) {
    QueueItem* node = new QueueItem(cipher, nonce);
    if (empty()) {
        front_ = rear_ = node;
        node->next = node;
    } else {
        node->next = front_;
        rear_->next = node;
        rear_ = node;
    }
    ++size_;
}

bool CircularQueue::empty() const { return front_ == nullptr; }

std::size_t CircularQueue::size() const { return size_; }

bool CircularQueue::front(QueueItem& out) const {
    if (empty()) return false;
    out.cipher_text = front_->cipher_text;
    out.nonce = front_->nonce;
    out.next = nullptr;
    return true;
}

bool CircularQueue::dequeue(QueueItem& out) {
    if (empty()) return false;
    out.cipher_text = front_->cipher_text;
    out.nonce = front_->nonce;
    out.next = nullptr;

    QueueItem* old_front = front_;
    if (size_ == 1) {
        front_ = rear_ = nullptr;
    } else {
        front_ = front_->next;
        rear_->next = front_;
    }
    delete old_front;
    --size_;
    return true;
}

std::vector<QueueItem> CircularQueue::snapshot() const {
    std::vector<QueueItem> items;
    if (empty()) return items;

    const QueueItem* current = front_;
    do {
        items.emplace_back(current->cipher_text, current->nonce);
        current = current->next;
    } while (current != front_);
    return items;
}
