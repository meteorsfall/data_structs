#pragma once
#include <iostream>
#include "array.h"
#include <math.h>

using namespace std;

int find_parent(int index) {
    if (index % 2 == 0) {
        return index/2 - 1;
    } else {
        return (index-1)/2;
    }
}

class LouisePriorityQueue {
    LouiseArray<int> data;
    void bubble(int index) {
        int value = data.get(index);
        if (index == 0) {
            return;
        }
        int& parent_value = data.get(find_parent(index));
        if (value > parent_value) {
            data.set(index, parent_value);
            data.set(find_parent(index), value);
            bubble(find_parent(index));
        }
    }
    void reverse_bubble(int index) {
        int value = data.get(index);
        int lchild_index = 2*index + 1;
        int rchild_index = 2*index + 2;
        if (lchild_index >= data.size()) {
            return;
        }
        int& biggest = data.get(lchild_index);
        int biggest_index = lchild_index;
        if (rchild_index < data.size() && data.get(rchild_index) > biggest) {
            biggest = data.get(rchild_index);
            biggest_index = rchild_index;
        }
        if (biggest > value) {
            data.set(index, biggest);
            data.set(biggest_index, value);
            reverse_bubble(biggest_index);
        }
    }
public:
    LouisePriorityQueue() {
    }
    void push(int value) {
        data.push(value);
        bubble(data.size() - 1);
    }
    int pop() {
        int largest = data.get(0);
        data.set(0, data.get(data.size() - 1));
        data.pop();
        reverse_bubble(0);
        return largest;
    }
    int top() {
        return data.get(0);
    }
    int size() {
        return data.size();
    }
};