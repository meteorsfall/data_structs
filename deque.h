#pragma once
#include <iostream>
#include "array.h"
#include <math.h>
#include "optional"
#include <vector>

using namespace std;

template<typename T>
class FastLouiseDeque {
    vector<T> front_data;
    vector<T> back_data;
    void split(vector<T>& empty, vector<T>& full) {
        int M = full.size()/2;
        empty.resize(M);
        for (int i = 0; i < M; i++) {
            empty[i] = full[M - 1 - i];
        }
        for (int i = M; i < full.size(); i++) {
            full[i - M] = full[i];
        }
        full.resize(full.size() - M);
    }
    T pop(vector<T>& target, vector<T>& spare) {
        T value;
        if (target.size() > 0) {
            value = target.back();
            target.pop_back();
        } else if (spare.size() <= 8) {
            value = spare.at(0);
            spare.erase(spare.begin());
        } else {
            split(target, spare);
            value = target.back();
            target.pop_back();
        }
        return value;
    }
public:
    void push_back(T value) {
        back_data.push_back(value);
    }
    void push_front(T value) {
        front_data.push_back(value);
    }
    T pop_back() {
        return pop(back_data, front_data);
    }
    T pop_front() {
        return pop(front_data, back_data);
    }
    T& front() {
        if (front_data.size() > 0) {
            return front_data[front_data.size() - 1];
        } else {
            return back_data.at(0);
        }
    }
    T& back() {
        if (back_data.size() > 0) {
            return back_data[back_data.size() - 1];
        } else {
            return front_data.at(0);
        }
    }
};

template<typename T>
class LouiseDeque {
    LouiseArray<T> front_data;
    LouiseArray<T> back_data;
    void split(LouiseArray<T>& empty, LouiseArray<T>& full) {
        int M = full.size()/2;
        for (int i = 0; i < M; i++) {
            empty.push(full[M - 1 - i]);
        }
        for (int i = M; i < full.size(); i++) {
            full[i - M] = full[i];
        }
        for (int i = 0; i < M; i++) {
            full.pop();
        }
    }
    T pop(LouiseArray<T>& target, LouiseArray<T>& spare) {
        T value;
        if (target.size() > 0) {
            value = target.pop();
        } else if (spare.size() <= 8) {
            value = spare.get(0);
            spare.remove(0);
        } else {
            split(target, spare);
            value = target.pop();
        }
        return value;
    }
public:
    void push_back(T value) {
        back_data.push(value);
    }
    void push_front(T value) {
        front_data.push(value);
    }
    T pop_back() {
        return pop(back_data, front_data);
    }
    T pop_front() {
        return pop(front_data, back_data);
    }
    T& front() {
        if (front_data.size() > 0) {
            return front_data[front_data.size() - 1];
        } else {
            return back_data.get(0);
        }
    }
    T& back() {
        if (back_data.size() > 0) {
            return back_data[back_data.size() - 1];
        } else {
            return front_data.get(0);
        }
    }
};

template<typename T>
class SlowLouiseDeque {
    struct Node {
        Node* prev = NULL;
        Node* next = NULL;
        optional<T> data;
    };
    Node* start;
    Node* end;
public:
    SlowLouiseDeque() {
        this->start = new Node();
        this->end = new Node();
        this->start->next = end;
        this->end->prev = start;
    }
    ~SlowLouiseDeque() {
        delete this->start;
        delete this->end;
    }
    SlowLouiseDeque(const SlowLouiseDeque& other) {
        this->start = NULL;
        this->end = NULL;
        *this = other;
    }
    SlowLouiseDeque& operator=(const SlowLouiseDeque& other) {
        if (this == &other)
            return *this;
        this->~SlowLouiseDeque();
        this->start = new Node();
        this->end = new Node();
        this->start->next = end;
        this->end->prev = start;

        if (other->start->next == other->end) {
            return *this;
        } else {
            Node* n = other->start->next;
            while (n != other->end) {
                this->push_back(n->data);
                n = n->next;
            }
        }

        return *this;
    }
    void push_back(T value){
        Node* anode = new Node();
        anode->data = value;
        anode->prev = end->prev;
        anode->next = end;
        end->prev = anode;
        anode->prev->next = anode;
    }
    void push_front(T value){
        Node* anode = new Node();
        anode->data = value;
        anode->next = start->next;
        anode->prev = start;
        start->next = anode;
        anode->next->prev = anode;
    }
    T pop_back(){
        if (end->prev == start) {
            throw "popped empty";
        }
        Node* anode = end->prev;
        T value = *anode->data;
        end->prev = anode->prev;
        end->prev->next = end;
        delete anode;
        return value;
    }
    T pop_front(){
        if (start->next == end) {
            throw "popped empty";
        }
        Node* anode = start->next;
        T value = *anode->data;
        start->next = anode->next;
        start->next->prev = start;
        delete anode;
        return value;
    }
    T& front(){
        return *start->next->data; 
    }
    T& back(){
        return *end->prev->data;
    }
};