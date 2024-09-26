#ifndef LINKEDLIST_H
#define LINKEDLIST_H

//#include <QDeclarativeItem>
#include <QObject>
#include <QQuickItem>
#include <QSharedDataPointer>
#include <QWidget>
#include<QFileDialog>

class LinkedListData;

class LinkedList
{
   // Q_OBJECT
public:
    class Node{
    public:
        QFileInfo data;
        Node* next=nullptr;
    };
    Node*head=nullptr;
    Node*tail=nullptr;
    LinkedList();
    LinkedList(const LinkedList &);
    LinkedList &operator=(const LinkedList &);
    ~LinkedList();
    void addiTem(QFileInfo newItem);
    QFileInfo searchByName(QString ItemName);
    QFileInfo searchByIndex(int ItemIndex);
    QFileInfo getNextItem(QFileInfo curItem);
    QFileInfo getPrevItem(QFileInfo curItem);
    bool isSongThere(QFileInfo song);

private:
    QSharedDataPointer<LinkedListData> data;
    int sz=0;
};

#endif // LINKEDLIST_H
