#include "CircularQueue.h"
#include <iostream>

CircularQueue* createQueue() {
    CircularQueue* q = new CircularQueue();
    q->front = nullptr;
    q->rear = nullptr;
    return q;
}

Node* createNode(std::string cipher, long long val) {
    Node* newNode = new Node();
    newNode->c_txt = cipher;
    newNode->nonce = val;
    newNode->next = nullptr;
    return newNode;
}

void enqueue(CircularQueue* q, std::string cipher, long long val) {
    Node* newNode = createNode(cipher, val);

    if (q->front == nullptr) {
        q->front = newNode;
        q->rear = newNode;
        q->rear->next = q->front;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
        q->rear->next = q->front;
    }
    std::cout << "Added to queue, nonce = " << val << "\n";
}

void displayQueue(CircularQueue* q) {
    if (q->front == nullptr) {
        std::cout << "Queue is empty\n";
        return;
    }

    Node* temp = q->front;
    std::cout << "Queue contents: ";
    do {
        std::cout << "(cipher: " << temp->c_txt << ", nonce: " << temp->nonce << ") ";
        temp = temp->next;
    } while (temp != q->front);
    std::cout << "-> back to front\n";
}
