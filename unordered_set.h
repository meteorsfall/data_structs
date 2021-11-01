#pragma once
#include <iostream>
#include "array.h"

using namespace std;

class LouiseUnorderedSet {
    int _size;
    int capacity;
    LouiseArray<LouiseArray<int>> data; 
    int hashit(int key) {
        return hash_function(key) % capacity;
    }
public:
    LouiseUnorderedSet() {
        this->data.resize(1);
        this->capacity = 1;
        this->_size = 0;
    }
    bool contains(int key) {
        LouiseArray<int> loc = this->data.get(hashit(key));
        bool present = false;
        for(int i = 0; i < loc.size(); i++) {
            if(loc.get(i) == key) {
                present = true;
            }
        }
        return present;
    }
    void insert(int key) {
        if(!contains(key)) {
            _size++;
            if(_size == capacity){
                capacity *= 2;
                LouiseArray<LouiseArray<int>> new_data = LouiseArray<LouiseArray<int>>(capacity);
                for(int i = 0; i < capacity/2; i++){
                    for(int j = 0; j < this->data.get(i).size(); j++){
                        int val = this->data.get(i).get(j);
                        new_data.get(hashit(val)).push(val);
                    }
                }
                this->data = new_data;
            }
            this->data.get(hashit(key)).push(key);
        }
    }
    void remove(int key) {
        if(!contains(key)){
            return;
        }
        _size--;
        if(_size == capacity/4){
            capacity /= 2;
            LouiseArray<LouiseArray<int>> new_data = LouiseArray<LouiseArray<int>>(_size*2);
            for(int i = 0; i < this->data.size(); i++){
                for(int j = 0; j < this->data.get(i).size(); j++){
                    int val = this->data.get(i).get(j);
                    new_data.get(hashit(val) ).push(val);
                }
            }
            this->data = new_data;
        }
        LouiseArray<int>& loc = this->data.get(hashit(key));
        for(int i = 0; i < loc.size(); i++) {
            if(loc.get(i) == key){
                loc.remove(i);
            }
        }
    }
    int size() {
        return this->_size;
    }
};