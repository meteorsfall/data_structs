#pragma once
#include <iostream>
#include <math.h>
#include <vector>
#include <functional>

using namespace std;

template<typename T>
class SegmentTree {
    T init;
    std::function<T(T, T)> combine;
    vector<T> data;
    vector<pair<int, int>> range;
    int size;
    vector<T> arr;
    T recurse_range(int i, int j, int cur) {
        int l = range[cur].first;
        int r = range[cur].second;
        if ( j < l || r < i) {
            return init;
        }
        if (i <= l && r <= j) {
            return data[cur];
        }
        return combine(recurse_range(i, j, 2*cur), recurse_range(i, j, 2*cur + 1));
    }
public:
    SegmentTree(const vector<T>& arr, T init, std::function<T(T, T)> combine) {
        this->size = arr.size();
        this->arr = arr;
        int next_pow = 2;
        while (next_pow < arr.size()) {
            next_pow *= 2;
        }
        data.resize(next_pow*2);
        for (int i = 0; i < arr.size(); i++) {
            data[next_pow + i] = arr[i];
        }
        for (int i = next_pow + arr.size(); i < data.size(); i++) {
            data[i] = init;
        } 
        this->init = init;
        this->combine = combine;
        for (int i = next_pow - 1; i >= 1; i--) {
            data[i] = combine(data[2*i], data[2*i + 1]);
        }
        range.resize(data.size());
        int cur_pow = 1;
        for (int i = 1; i < data.size(); i++) {
            if (cur_pow*2 <= i) {
                cur_pow *= 2;
            }
            int l = (i - cur_pow)*next_pow/cur_pow;
            int r = (i + 1 - cur_pow)*next_pow/cur_pow - 1;
            range[i] = {l, r};
        }
    }
    T get_range(int i, int j) {
        return recurse_range(i, j, 1);
    }
    void update(int i, T value) {
        // data.size()/2 + i < data.size()
        int coord = data.size()/2 + i;
        data[coord] = value;
        arr[i] = value;
        coord /= 2;
        while (coord > 0) {
            data[coord] = combine(data[2*coord], data[2*coord+1]);
            coord /= 2;
        }
    }
    void push(T value) {
        arr.push_back(value);
        if (this->size < data.size()/2) {
            update(this->size, value);
        } else {
            *this = SegmentTree<T> (this->arr, this->init, this->combine);
        }
        this->size++;
    }
    T pop() {
        T value = arr.back();
        arr.pop_back();
        update(size - 1, init);
        size--;
        return value;
    }
};