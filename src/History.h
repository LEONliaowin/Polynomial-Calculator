//
// Created by 19912 on 2024/9/30.
//

#ifndef CALCULATOR_GUI_HISTORY_H
#define CALCULATOR_GUI_HISTORY_H

#include <QString>
//#include <list>
//
//std::list<QString> history;
//


class Node{
public:
    QString data;
    Node *next;
    Node *prev;
    Node(QString data, Node *next = nullptr, Node *prev = nullptr): data(data), next(next), prev(prev) {}
};

// a class to store the history of the calculator
class History {
public:
    History();

    QString undo();

    QString redo();

    void add(const QString &str);

    void clear();

    static void clear_behind(Node *node);

    bool isOldest();

    bool isNewest();

    void print();

private:
    Node *head, *tail;

};


#endif //CALCULATOR_GUI_HISTORY_H
