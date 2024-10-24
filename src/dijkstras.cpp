// dijsktras.cpp
#include <map>
#include <vector>
#include <iostream>

#include <algorithm>
#include <queue>
#include <random>

using namespace std;

// Main Execution

struct maze{
    map<char, int> costs;
    vector<int> tiles;
    int start, end;
    int row, col;
    vector<signed int> visited;

    vector<int> path;
    int path_length;
};

void generate_map(int n){

    default_random_engine gen;
    uniform_int_distribution<int> dista(97, 122);
    uniform_int_distribution<int> distb(1, n+1);
    uniform_int_distribution<int> distc(0, n);

    cout << n/2 << endl;
    vector<int> g(n, 0);
    for(int i = 0; i < n/2; i++){
        int choc = dista(gen);
        if(find(g.begin(), g.end(), choc) == g.end()){
            cout << i << " " << distb(gen) << endl;
            g[i] = choc;
        }
    }

    cout << n << " " << n;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            int b = g[distc(gen)];
            while(!b){
                b = g[distc(gen)];
            }
            cout << (char)b << " ";
        }
        cout << endl;
    }

    cout << "0 0" << endl;
    cout << n << " " << n << endl;
    return;
}

void dikstras(maze &m){
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    m.visited[m.start] = 0;
    pq.emplace(0, m.start);

    while(!pq.empty()){
        int distance = pq.top().first, position = pq.top().second;
        pq.pop();

        if(position == m.end){
            m.path_length = distance;
            return;
        }

        if(m.visited[position] < distance){
            continue;
        }

        vector<int> directions = {-1, 1, -m.col, m.col};
        for (int dir : directions) {
            int neighbor = position + dir;
                    // Check bounds
            if (neighbor >= 0 && neighbor < m.row * m.col) {
                // Calculate new distance
                int new_distance = distance + m.tiles[neighbor];

                // If this new distance is better, update and push to queue
                if (m.visited[neighbor] == -1 || new_distance < m.visited[neighbor]) {
                    m.visited[neighbor] = new_distance;
                    pq.emplace(new_distance, neighbor);
                    m.path[neighbor] = position; // Track the path
                }
            }
        }
    }
    m.path_length = m.visited[m.end];
}

void store_map(maze &m){
    int num;
    cin >> num;

    for(int i = 0; i < num; i++){
        char a;
        int b;
        cin >> a >> b;

        m.costs.emplace(make_pair(a, b));
    }

    int row, col;
    cin >> row >> col;
    m.tiles = vector<int>(col*row, 0);
    m.path = vector<int>(col*row, 0);

    for(int k = 0; k < col; k++){
        for(int j = 0; j < row; j++){
            char c;
            cin >> c;

            m.tiles[j*col+k] = m.costs[c];
        }
    }
    m.visited = vector<signed int>(row*col, -1);

    int tx, ty;
    cin >> tx >> ty;
    m.start = tx*col+ty;

    cin >> tx >> ty;
    m.end = tx*col+ty;

    m.row = row;
    m.col = col;

    return;
}

int main(int argc, char *argv[]) {
    maze* m = new maze;
    store_map(*m);
    cout<<"stored map"<<endl;
    dikstras(*m);

    cout<<(m->path_length)<<endl;
    vector<string> s;

    for(int i = m->end; i != 0; i = m->path[i]){
	   s.push_back(to_string(i%m->col) + " " + to_string(i/m->col));
    }
    s.push_back("0 0");
    reverse(s.begin(), s.end());
    reverse(s[s.size()-1].begin(), s[s.size()-1].end());

    for(auto j = s.begin(); j != s.end(); ++j){
        cout<<*j<<endl;
    }

    return 0;
}

