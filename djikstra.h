#pragma once
#include <iostream>
#include <stdio.h>
#include <vector>
#include <limits.h>
#include <queue>
#include <functional>

using namespace std;

pair<vector<int>, vector<int>> djikstra(vector<vector<pair<int, int>>> graph, int source) {
    vector<int> distances(graph.size() , INT_MAX);
    distances[source] = 0;
    vector<int> prev(graph.size(), -1);
    priority_queue <pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > Q;
    vector<bool> visited(graph.size() , false);
    for (int i = 0; i < graph.size(); i++) {
        Q.push({distances[i], i});
    }
    while (Q.size() > 0) {
        if (visited[Q.top().second] == true) {
            Q.pop();
            continue;
        }
        pair<int, int> smallest_Q = Q.top();
        int smallest = smallest_Q.second;
        cout << "size: " << Q.size() << " index: " << smallest << endl;
        Q.pop();
        visited[smallest] = true;
        for (int i = 0; i < graph[smallest].size(); i++) {
            pair<int, int> edge = graph[smallest][i];
            if (visited[edge.first]) {
                continue;
            }
            int alt = edge.second + distances[smallest];
            if (alt < distances[edge.first]) {
                distances[edge.first] = alt;
                prev[edge.first] = smallest;
                Q.push({alt, edge.first});
            }
        }
    }
    return {distances, prev};
}