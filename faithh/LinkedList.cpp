#include "LinkedList.h"
#include<QFileDialog>
class LinkedListData : public QSharedData
{
public:
};

LinkedList::LinkedList()
    : data(new LinkedListData)
{}

LinkedList::LinkedList(const LinkedList &rhs)
    : data{rhs.data}
{}

LinkedList &LinkedList::operator=(const LinkedList &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

LinkedList::~LinkedList() {}

void LinkedList::addiTem(QFileInfo newItem)
{
    Node* newElem= new Node;
    newElem->data=newItem;
    if(head==nullptr){
        head=tail=newElem;
        sz++;
        return;
    }
    tail->next=newElem;
    tail=newElem;
    sz++;
}

QFileInfo LinkedList::searchByName(QString ItemName)
{
    Node* cur=head;
    while(cur!=nullptr){
        if(cur->data.baseName()==ItemName){
            return cur->data;
        }
        cur=cur->next;
    }
}

QFileInfo LinkedList::searchByIndex(int ItemIndex)
{
    int i=0;
    Node* cur=head;
    while(cur!=nullptr && i<ItemIndex){
        cur=cur->next;
        i++;
    }
    return cur->data;
}

QFileInfo LinkedList::getNextItem(QFileInfo curItem)
{
    if(tail->data==curItem){
        return head->data;
    }
    Node*cur=head;
    while(cur!=nullptr){
        if(cur->data==curItem){
            return cur->next->data;
        }
        cur=cur->next;
    }
}

QFileInfo LinkedList::getPrevItem(QFileInfo curItem)
{
    if(head->data==curItem){
        return tail->data;
    }
    Node* cur=head;
    Node* parent=head;
    while(cur!=nullptr){
        if(cur->data==curItem){
            return parent->data;
        }
        parent=cur;
        cur=cur->next;
    }
}

bool LinkedList::isSongThere(QFileInfo song)
{
    Node* cur=head;
    while(cur!=nullptr){
        if(cur->data==song){
            return true;
        }
        cur=cur->next;
    }
    return false;
}

