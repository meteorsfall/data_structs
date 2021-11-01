#include <vector>
#include <math.h>

using namespace std;

// Returns -1 if elem not found
template<typename T>
int bounded_binary(vector<T>& arr, T target, int L, int R) {
    int M = (L+R)/2;
    if (arr[M] == target) {
        return M;
    } else if (L >= R) {
        return -1;
    } else if (arr[M] > target) {
        return binary_search_element(arr, target, L, M-1 > L ? M-1 : L);
    } else {
        return binary_search_element(arr, target, M+1, R);
    }
}

template<typename T>
int binary_search_element(vector<T>& arr, T target) {
    return bounded_binary(arr, target, 0, arr.size() - 1);
}

template<typename T>
int bounded_ternary(const vector<T>& arr, int L, int R) {
    if (L == R){
        return L;
    }

    int M1 = (L+R)/2;
    int M2 = M1+1;
    if (arr[M1] > arr[M2]) {
        return bounded_ternary(arr, L, M1);
    } 
    if (arr[M1] < arr[M2]) {
        return bounded_ternary(arr, M2, R);
    }
    return M1;
}

template<typename T>
int ternary_search(const vector<T>& arr) {
    int L = 0;
    int R = arr.size() - 1;
    return bounded_ternary(arr, L, R);
}