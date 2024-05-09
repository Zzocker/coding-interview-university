#include <iostream>
#include <queue>
#include <vector>
#include <cassert>
using namespace std;

template <typename T> void print(const vector<vector<T>>& A){
    for (const vector<int>& row: A){
        for (const int& a: row)cout << a << ' ';
        cout << endl;
    }
}

vector<vector<int>> get_adjacency_list(const vector<vector<int>>& matrix){
    int N = matrix.size();
    vector<vector<int>> list(N);
    for (int i=0;i<N;i++){
        for (int j=0;j<N;j++){
            if (matrix[i][j] == 1){
                list[i].push_back(j);
            }
        }
    }
    return list;
}

void dfs(const vector<vector<int>>& adj, vector<bool>& visited, int u){
    visited[u] = true;
    cout << u << ' ';
    for (const int& v: adj[u]){
        if (!visited[v])dfs(adj, visited, v);
    }
}

void bfs(const vector<vector<int>>& adj, vector<bool>& visited, int u){
    queue<int> q;
    q.push(u);
    visited[u] = true;
    cout << u << ' ';
    while (!q.empty()){
        int u = q.front();q.pop();
        for (const int& v: adj[u]){
            if (!visited[v]){
                visited[v] = true;
                cout << v << ' ';
                q.push(v);
            }
        }
    }
}

int main(){
    int N = 10;
    vector<vector<int>> matrix(N, vector<int> (N, 0));
    matrix[1][2] = 1;
    matrix[1][3] = 1;
    matrix[1][4] = 1;

    matrix[2][1] = 1;
    matrix[2][5] = 1;

    matrix[3][5] = 1;
    matrix[3][1] = 1;
    matrix[3][4] = 1;

    matrix[4][1] = 1;
    matrix[4][3] = 1;

    matrix[6][7] = 1;
    matrix[6][8] = 1;
    
    matrix[7][6] = 1;

    matrix[8][6] = 1;
    
    auto adj = get_adjacency_list(matrix);

    {
        vector<bool> visited(N, false);
        for (int u=0;u<N;u++){
            if (!visited[u])dfs(adj, visited, u);
        }
        cout << endl;
    }
    {
        vector<bool> visited(N, false);
        for (int u=0;u<N;u++){
            if (!visited[u])bfs(adj, visited, u);
        }
        cout << endl;
    }
}