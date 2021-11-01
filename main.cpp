#include "array.h"
#include "unordered_set.h"
#include "unordered_map.h"
#include "priority_queue.h"
#include "djikstra.h"
#include "prim.h"
#include "search.h"
#include "sort.h"
#include "knapsack.h"
#include "deque.h"
#include "segment_tree.h"
#include <iostream>
#include <vector>
#include <tuple>
#include <chrono>

using namespace std;

void heapsort(LouiseArray<int> numbers) {
    LouisePriorityQueue queue;
    for (int i = 0; i < numbers.size(); i++) {
        queue.push(numbers.get(i));
    }
    for (int i = 0; i < numbers.size(); i++) {
        cout << queue.pop() << " ";
    }
    cout << endl;
}

template<typename IntDequeType>
void test_deque() {
    IntDequeType deque;
    int SIZE = 50'000'000;
    for (int i = 0; i < SIZE/2; i++) {
        deque.push_back(i);
        deque.push_front(-i);
    }
    for (int i = 0; i < SIZE; i++) {
        if (i % 2 == 3) {
            deque.pop_front();
        } else {
            deque.pop_back();
        }
    }
} 

int main() {
    LouiseArray<int> numbers;
    LouisePriorityQueue queue;
    queue.push(2);
    queue.push(5);
    // cout << queue.top() << endl;
    vector<int> arc = {3, -5, 8, 7, 1, -2, 88, 100, 24, 7, 2, 4, 1, 0, 0, 13, 11};
    for (int elem : arc) {
        numbers.push(elem);
    }
    // heapsort(numbers); 
    vector<vector<pair<int, int>>> graph(6);
    vector<tuple<int, int, int>> edges = {
        {0,1,7},
        {0,2,9},
        {0,5,14},
        {1,2,10},
        {1,3,15},
        {2,3,11},
        {2,5,2},
        {3,4,6},
        {4,5,9}
    };
    for(int i = 0; i < edges.size(); i++){
        graph[get<0>(edges[i])].push_back({get<1>(edges[i]), get<2>(edges[i])});
        graph[get<1>(edges[i])].push_back({get<0>(edges[i]), get<2>(edges[i])});
    }
    vector<vector<pair<int, int>>> graph2 = {
        {{2, 1},{1, 3}},
        {{2, 0},{2, 3}},
        {{3, 3}},
        {{3, 2}, {2, 1}, {1, 0}}
    };
    
    vector<int> t_check = {0, 3, 7, 13, 17, 15, 13, 9, 3, 2, 1, 0};
    // cout << t_check[ternary_search(t_check)] << endl;

    vector<pair<int, int>> backpack = {{12, 4}, {1, 2}, {2, 2}, {1, 1}, {4, 10}};
    //cout << knapsack(15, backpack);

    LouiseDeque<int> aqueue;
    for (int i = 0; i < arc.size(); i++) {
        if (i%2 == 0) {
            aqueue.push_back(arc[i]);
        } else {
            aqueue.push_front(arc[i]);
        }
    }
    /*for (int i = 0; i < arc.size(); i++) {
        cout << aqueue.front() << " ";
        aqueue.pop_front();
    }
    cout << endl;*/
    /* for (int i = 0; i < arc.size(); i++) {
        if (i%2 == 0) {
            cout << aqueue.front() << " ";
            aqueue.pop_front();
        } else {
            cout << aqueue.back() << " ";
            aqueue.pop_back();
        }
    }
    cout << endl; */
    /*
    auto before = chrono::high_resolution_clock::now();
    //test_deque<SlowLouiseDeque<int>>();
    auto after = chrono::high_resolution_clock::now();
    cout << "Slow Time: " << (chrono::duration_cast<chrono::microseconds>(after - before).count() / 1'000'000.0) << endl;

    before = chrono::high_resolution_clock::now();
    test_deque<LouiseDeque<int>>();
    after = chrono::high_resolution_clock::now();
    cout << "Louise Time: " << (chrono::duration_cast<chrono::microseconds>(after - before).count() / 1'000'000.0) << endl;

    before = chrono::high_resolution_clock::now();
    //test_deque<FastLouiseDeque<int>>();
    after = chrono::high_resolution_clock::now();
    cout << "Fast Time: " << (chrono::duration_cast<chrono::microseconds>(after - before).count() / 1'000'000.0) << endl; */
    /* vector<int> segment_test = {2,7,3,4,16,9,1,3};
    SegmentTree<int> seg_tree (segment_test, INT_MAX, [](int a, int b) -> int {
            return min(a, b);
    });
    for (int i = 0; i < segment_test.size(); i++) {
        seg_tree.pop();
    }
    for (int i = 0; i < segment_test.size(); i++) {
        seg_tree.push(segment_test[i]);
    }
    cout << "SEGMIN: " << seg_tree.get_range(0, 5) << endl; */
    /* quicksort<int>(arc);
    for (int i = 0; i < arc.size(); i++) {
        cout << arc[i] << " ";
    }
    cout << endl;
    vector<int> test_arr(1'0'000);
    quicksort<int>(test_arr); */
    /*
    srand(1);
    for(int i = 0; i < 100'000'000; i++) {
        arc.push_back(0);
    }
    auto before = chrono::high_resolution_clock::now();
    quicksort(arc);
    auto after = chrono::high_resolution_clock::now();
    cout << "Time: " << (chrono::duration_cast<chrono::microseconds>(after - before).count() / 1'000'000.0) << endl;
    for (int i = 1; i < arc.size(); i++) {
        if (arc[i-1] > arc[i]) {
            cout << "BAD!" << endl;
            break;
        }
        //cout << arc[i] << " ";
    } */

}  
