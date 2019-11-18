//
// Created by 81406 on 2019/11/9.
//

#ifndef ARTIFICIALINTELLIGENCEPROJECT_QUEUE_H
#define ARTIFICIALINTELLIGENCEPROJECT_QUEUE_H

template <class T>
struct TNode{
    T data;
    TNode<T> *next = nullptr;
};

template<class T>
class Queue{
private:
    TNode<T> *Front;
    TNode<T> *Rear;
    int length;

public:
    Queue();
    ~Queue();
    bool isEmpty();
    bool EnQueue(T e);
    bool DeQueue(T &e);
    int getLength();
    TNode<T>* getFirst();
    T isInQueue(T e);
    bool InList(T e);
    void OutList(T e);
    bool InList_A_Star(T e);
};

template <class T>
Queue<T>::Queue() {
    Front = new TNode<T>;
    Front->next = nullptr;
    Rear = Front;
    length = 0;
}

template <class T>
bool Queue<T>::isEmpty() {
    return Front == Rear;
}

template <class T>
bool Queue<T>::EnQueue(const T e) {
    if(&e == nullptr)
        return false;
    auto *p = new TNode<T>;
    p->data = e;
    p->next = nullptr;
    Rear->next = p;
    Rear = p;
    length++;
    return true;
}

template <class T>
bool Queue<T>::DeQueue(T &e) {
    TNode<T> *p;
    if(isEmpty ())
        return false;
    p = Front->next;
    e = p -> data;
    Front->next = p->next;
    if(Rear == p) Rear = Front;
    length--;
    return true;

}


template <class T>
Queue<T>::~Queue() {
}

template <class T>
int Queue<T>::getLength() {
    return length;
}

template <class T>
TNode<T> *Queue<T>::getFirst() {
    if(!isEmpty ())
        return Front->next;
    else
        return nullptr;
}

template <class T>
bool Queue<T>::InList(T e) {
    if(&e == nullptr)
        return false;

    auto *p = new TNode<T>;
    p->data = e;

    auto *q = Front;
    for (int i = 0; i < length-1; ++i) {
        if(e < q->next->data){
            p->next = q->next;
            q->next = p;
            length++;
            return true;
        }else
            q = q->next;
    }
    Rear->next = p;
    Rear = p;
    length++;
    return true;
}

template <class T>
T Queue<T>::isInQueue(T e) {
    auto *p = Front;
    while(p->next != nullptr){
        if(p->next->data == e)
            return p->next->data;
        p = p->next;
    }
    return e;
}

template <class T>
void Queue<T>::OutList(T e) {
    auto *p = Front;
    while(p->next != nullptr){
        if(p->next->data == e){
            p->next = p->next->next;
            return;
        }
        p = p->next;
    }
}

template <class T>
bool Queue<T>::InList_A_Star(T e) {
    auto *p = Front;
    while(p->next != nullptr){
        if(p->next->data == e){
            p->next->data = e;
            return true;
        }
        p = p->next;
    }
    return InList (e);
}


#endif //ARTIFICIALINTELLIGENCEPROJECT_QUEUE_H
