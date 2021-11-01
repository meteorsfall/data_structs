#pragma once
#include <iostream>
#include "array.h"
#include <math.h>
#include <tuple>
#include <vector>
#include <queue>
#include <functional>
#include <limits.h>

using namespace std;
// {distance, edge1, edge2}

vector<pair<int, int>> prim(const vector<vector<pair<int, int>>>& graph) {
    vector<pair<int,int>> spanning_tree;
    vector<bool> visited(graph.size(), false);
    visited[0] = true;
    priority_queue< tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>> > cut;
    for (int i = 0; i < graph[0].size(); i++) {
        pair<int, int> edge = graph[0][i];
        cut.push({edge.first, 0, edge.second});
    }
    for (int i = 1; i < graph.size(); i++) {   
        while (visited[get<2>(cut.top())]) {
            cut.pop();
        }
        tuple<int,int,int> edge = cut.top();
        cut.pop();
        int target_edge = get<2>(edge);
        spanning_tree.push_back({get<1>(edge), target_edge});
        visited[target_edge] = true;
        for (int j = 0; j < graph[target_edge].size(); j++){
            pair<int, int> target_neighbor = graph[target_edge][j];
            if (!visited[target_neighbor.second]){
                cut.push({target_neighbor.first, target_edge, target_neighbor.second});
            }
        }
    }
    return spanning_tree;
}