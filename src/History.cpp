//
// Created by 19912 on 2024/9/30.
//

#include <iostream>
#include "History.h"

History::History() {
    head = tail = nullptr;
}

QString History::undo() {
    if (tail == head) {
        return tail->data;
    }
    tail = tail->prev;
    return tail->data;
}

QString History::redo() {
    if (tail->next == nullptr) {
        return tail->data;
    } else {
        tail = tail->next;
        return tail->data;
    }
}

void History::add(const QString &str) {
    Node *new_node = new Node(str);
    if (head == nullptr) {
        head = tail = new_node;
    } else {
        clear_behind(tail->next);
        tail->next = new_node;
        new_node->prev = tail;
        tail = new_node;
    }
}

void History::clear() {
    clear_behind(head);
    head = tail = nullptr;
}

void History::clear_behind(Node *node) {
    if (node == nullptr) return;
    Node *p = node;
    while (p) {
        Node *tmp = p;
        p = p->next;
        delete tmp;
    }
}

bool History::isOldest() {
    return head == tail;
}

bool History::isNewest() {
    return tail->next == nullptr;
}

void History::print() {
    if (head == nullptr) return;
    Node *p = head;
    while (p) {
       std::cout << p->data.toStdString()  << "->";
        p = p->next;
    }
    std::cout << std::endl;

    std::cout << "head: " << head->data.toStdString() << std::endl;
    std::cout << "tail: " << tail->data.toStdString() << std::endl;
}
