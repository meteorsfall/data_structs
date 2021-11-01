#pragma once
#include <iostream>
#include <stdio.h>

int hash_function(int key){
    return 1000*key;
}

using namespace std;

template<typename T>
class LouiseArray {
    int _size;
    T* data;
    int capacity;
public:
    T& operator[](int i) const {
        return data[i];
    }
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
    LouiseArray(const LouiseArray& other) {
        this->data = NULL;
        *this = other;
    }
    LouiseArray& operator=(const LouiseArray& other) {
        if (this == &other)
            return *this;
        this->_size = other._size;
        this->capacity = other.capacity;
        delete[] this->data;
        this->data = new T[this->capacity];
        for(int i = 0; i < this->_size; i++) {
            this->data[i] = other.data[i];
        }
        return *this;
    }
    ~LouiseArray() {
        delete[] this->data;
    }
    void set(int index, T value) {
        if (index >= this->_size) {
            throw "Out of bounds!";
        }
        this->data[index] = value;
    }
    T& get(int index) {
        if (index >= this->_size) {
            throw "Out of bounds!";
        }
        return this->data[index];  
    }
    void push(T value) {
        if(_size == capacity) {
            resize(capacity*2);
            capacity *= 2; 
        }
        this->data[_size] = value;
        _size++;
    }
    T pop() {
        if (_size == 0) {
            throw "Popped, but nothing to pop!";
        }
        _size--;
        T popped = this->data[_size];
        if(_size == capacity/4){
            resize(capacity/2);
            capacity /= 2;
        }
        return popped;
    }
    void remove(int index) {
        if (index >= _size) {
            throw "Can't remove that index!";
        }
        _size--;
        if (_size == capacity/4) {
            T* new_array;
            capacity /= 2;
            new_array = new T[capacity];
            for (int i = 0; i < index; i++) {
                new_array[i] = this->data[i];
            }
            for (int i = index + 1; i < _size+1; i++) {
                new_array[i-1] = this->data[i];
            }
            delete[] this->data;
            this->data = new_array;
        } else {
            for (int i = index + 1; i < _size+1; i++) {
                this->data[i-1] = this->data[i];
            }
        }
    }
    void resize(int newcapacity) {
        T* new_array = new T[newcapacity];
        for(int i = 0; i < _size; i++){
            new_array[i] = this->data[i];
        }
        delete[] this->data;
        this->data = new_array;
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