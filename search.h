#include <vector>
#include <math.h>
#include <random>
#include <thread>

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

template<typename T>
void insertion_sort(vector<T>& arr, int l, int r) {
    for(int i = l; i <= r; i++) {
        for(int j = i+1; j <= r; j++) {
            if (arr[j] < arr[i]) {
                std::swap(arr[i], arr[j]);
            }
        }
    }
}

template<typename T>
class QuickSort {
    vector<T>& arr;
    mt19937 rng;
    uniform_int_distribution<mt19937::result_type> dist6;

    void quicksort(int l, int r) {
        if (l >= r) {
            return;
        }
        if (r - l < 16) {
            insertion_sort(arr, l, r);
            return;
        }
        dist6.param(uniform_int_distribution<mt19937::result_type>::param_type{(long unsigned int)l, (long unsigned int)r});
        T pivot = arr[dist6(rng)];
        int l_swap = l-1;
        int r_swap = r+1;
        while (l_swap < r_swap - 1) {
            if (arr[l_swap + 1] < pivot) {
                l_swap++;
            } else if (arr[r_swap - 1] > pivot) {
                r_swap--;
            } else {
                if (l_swap + 1 == r_swap - 1) {
                    break;
                } else {
                    std::swap(arr[l_swap + 1], arr[r_swap - 1]);
                    l_swap++;
                    r_swap--;
                }
            }
        }
        quicksort(l, l_swap);
        quicksort(r_swap, r);
    }
public:
    QuickSort(vector<T>& arr)
    : arr(arr) {
        std::random_device dev;
        this->rng = mt19937(dev());
        this->dist6 = uniform_int_distribution<mt19937::result_type>(0, arr.size());
        quicksort(0, arr.size()-1);
    }
};


template<typename T>
class SlowQuickSort {
    vector<T>& arr;
    mt19937 rng;
    uniform_int_distribution<mt19937::result_type> dist6;
public:
    void quicksort(int l, int r) {
        if (l >= r) {
            return;
        }
        dist6.param(uniform_int_distribution<mt19937::result_type>::param_type{(long unsigned int)l, (long unsigned int)r});
        int pivot = dist6(rng);
        int r_swap = r;
        for (int i = l; i < r_swap; i++) {
            if (arr[i] > arr[pivot]) {
                while (r_swap > i && arr[r_swap] > arr[pivot]) {
                    r_swap--;
                }
                if (r_swap <= i) {
                    break;
                } 
                if (r_swap == pivot) {
                    pivot = i;
                } else if (i == pivot) {
                    pivot = r_swap;
                }
                swap(arr[i], arr[r_swap]);
                r_swap--;
            }
        }
        while (r_swap > l && arr[r_swap] > arr[pivot]) {
            r_swap--;
        }
        int boundary;
        if (pivot <= r_swap) {
            swap(arr[pivot], arr[r_swap]);
            boundary = r_swap;
        } else {
            swap(arr[pivot], arr[r_swap + 1]);
            boundary = r_swap + 1;
        }
        quicksort(l, boundary - 1);
        quicksort(boundary + 1, r);
    }
    SlowQuickSort(vector<T>& arr)
    : arr(arr) {
        std::random_device dev;
        this->rng = mt19937(dev());
        this->dist6 = uniform_int_distribution<mt19937::result_type>(0, arr.size());
        quicksort(0, arr.size()-1);
    }
};

template<typename T>
void quicksort(vector<T>& arr) {
    QuickSort<T> qs(arr);
}

template<typename T>
void merge(vector<T>& arr, int l, int m, int r, vector<T>& merge) {
    // left[l,..m] right [m+1,...r]
    int l_index = l;
    int r_index = m+1;
    int merge_size = 0;
    while (l_index <= m && r_index <= r) {
        if (arr[l_index] <= arr[r_index]) {
            merge[merge_size++] = arr[l_index];
            l_index++;
        } else {
            merge[merge_size++] = arr[r_index];
            r_index++;
        }
    }
    while (l_index <= m) {
        merge[merge_size++] = arr[l_index];
        l_index++;
    }
    while (r_index <= r) {
        merge[merge_size++] = arr[r_index];
        r_index++;
    }
    for (int i = 0; i < merge_size; i++) {
        arr[l+i] = merge[i];
    }
}

template<typename T>
void mergehelper(vector<T>& arr, int l, int r, vector<T>& merge_arr) {
    if (r - l < 16) {
        insertion_sort(arr, l, r);
        return;
    }
    int M = (l + r)/2;
    mergehelper<T>(arr, l, M, merge_arr);
    mergehelper<T>(arr, M+1, r, merge_arr);
    merge<T>(arr, l, M, r, merge_arr);
}

template<typename T>
void mergesort(vector<T>& arr) {
    vector<T> merge_arr(arr.size());
    return mergehelper<T>(arr, 0, arr.size() - 1, merge_arr);
}

template<typename T>
void mergesort_threaded(vector<T>& arr) {
    const int num_threads = 8;
    vector<thread> mergethreads;
    if (arr.size() < 6*num_threads) {
        vector<T> merge_arr(arr.size());
        mergehelper<T>(arr, 0, arr.size() - 1, merge_arr);
    }
    vector<pair<int, int>> slices;
    vector<vector<T>> merge_arrs;
    for (int i = 0; i < num_threads; i++) {
        slices.push_back({i*arr.size()/num_threads, (i+1)*arr.size()/num_threads - 1});
        merge_arrs.push_back(vector<T>(slices[i].second - slices[i].first + 1));
    }
    for (int i = 0; i < num_threads; i++) {
        mergethreads.push_back(thread(mergehelper<T>, ref(arr), slices[i].first, slices[i].second, ref(merge_arrs[i])));
    }
    for (thread& t : mergethreads) {
        t.join();
    }

    int cur_regions = num_threads;
    int chunk = 1;
    while (cur_regions > 1) {
        vector<thread> more_threads;
        vector<vector<T>> merge_vecs(cur_regions/2);
        for (int i = 0; i < cur_regions/2; i++) {
            int l = slices[2*i*chunk].first;
            int m = slices[(2*i+1)*chunk - 1].second;
            int r = slices[(2*i+2)*chunk-1].second;
            merge_vecs[i] = vector<T>(r-l+1);
            more_threads.push_back(thread(merge<T>, ref(arr), l, m, r, ref(merge_vecs[i])));
        }
        for(thread& t : more_threads) {
            t.join();
        }
        cur_regions /= 2;
        chunk *= 2;
    }
}