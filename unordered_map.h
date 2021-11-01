#pragma once
#include <iostream>
//#include <utility>
#include "array.h"

using namespace std;

template<typename T>
class LouiseUnorderedMap {
    int _size;
    int capacity;
    LouiseArray<LouiseArray<pair<int, T>>> data; 
    int hashit(int key) {
        return hash_function(key) % capacity;
    }
public:
    LouiseUnorderedMap() {
        this->data.resize(1);
        this->capacity = 1;
        this->_size = 0;
    }
    bool contains(int key) {
        LouiseArray<pair<int, T>> loc = this->data.get(hashit(key));
        bool present = false;
        for(int i = 0; i < loc.size(); i++) {
            if(loc.get(i).first == key) {
                present = true;
            }
        }
        return present;
    }
    void insert(int key, T value) {
        if(!contains(key)) {
            _size++;
            if(_size == capacity){
                capacity *= 2;
                LouiseArray<LouiseArray<pair<int, T>>> new_data = LouiseArray<LouiseArray<pair<int, T>>>(capacity);
                for(int i = 0; i < capacity/2; i++){
                    for(int j = 0; j < this->data.get(i).size(); j++){
                        pair<int, T> val = this->data.get(i).get(j);
                        new_data.get(hashit(val.first)).push(val);
                    }
                }
                this->data = new_data;
            }
            this->data.get(hashit(key)).push({key, value});
        } else {
            get(key) = value;
        }
    }
    void remove(int key) {
        if(!contains(key)){
            return;
        }
        _size--;
        if(_size == capacity/4){
            capacity /= 2;
            LouiseArray<LouiseArray<pair<int, T>>> new_data = LouiseArray<LouiseArray<pair<int, T>>>(_size*2);
            for(int i = 0; i < this->data.size(); i++){
                for(int j = 0; j < this->data.get(i).size(); j++){
                    pair<int, T> val = this->data.get(i).get(j);
                    new_data.get(hashit(val.first) ).push(val);
                }
            }
            this->data = new_data;
        }
        LouiseArray<pair<int, T>> newbucket;
        LouiseArray<pair<int, T>>& loc = this->data.get(hashit(key));
        for(int i = 0; i < loc.size(); i++) {
            if(loc.get(i).first != key){
                newbucket.push(loc.get(i));
            }
        }
        loc = newbucket;
    }
    int size() {
        return this->_size;
    }
    T& get(int key) {
        LouiseArray<pair<int, T>>& bucket = this->data.get(hashit(key));
        for (int i = 0; i < bucket.size(); i++) {
            if(bucket.get(i).first == key) {
                return bucket.get(i).second;
            }
        }
        throw "key not found";
    }
};