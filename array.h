#pragma once
#include <iostream>

using namespace std;

template<typename T>
class LouiseArray {
    int _size = 0;
    T* data;
    int capacity;
public:
    LouiseArray() {
        this->_size = 0;
        this->capacity = 1;
        this->data = new T[capacity];
    }
    LouiseArray(int size) {
        this->_size = size;
        this->capacity = 1;
        while(capacity < size) {
            capacity *= 2;
        }
        this->data = new T[capacity];
    }
    void set(int index, T value) {
        this->data[index] = value;
    }
    T get(int index) {
        return this->data[index];  
    }
    void push(T value) {
        if(_size == capacity) {
            capacity *= 2;
            T* double_array = new T[capacity];
            for(int i = 0; i < _size; i++) {
                double_array[i] = this->data[i];
            }
            delete[] this->data;
            this->data = double_array;
        }
        this->data[_size] = value;
        _size++;
    }
    T pop() {
        _size--;
        T popped = this->data[_size];
        if(_size == capacity/4){
            T* new_array = new T[_size*2];
            for(int i = 0; i < _size; i++){
                new_array[i] = this->data[i];
            }
            delete[] this->data;
            this->data = new_array;
            capacity /= 2;
        }
        return popped;
    }
    int size() {
        return this->_size; 
    }
    void print() {
        for (int i = 0; i < this->_size; i++) {
            cout << this->data[i] << " ";
        }
        cout << endl;
    }
};