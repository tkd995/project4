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
    int start, end;//goal and beginning
    int row, col;//size of matrix
    vector<signed int> visited;

    vector<int> path;
    int path_length;
};

void generate_map(int n){

    default_random_engine gen;//random number generators for new game creation
    uniform_int_distribution<int> dista(97, 122);
    uniform_int_distribution<int> distb(1, n+1);
    uniform_int_distribution<int> distc(0, n);

    cout << n/2 << endl;
    vector<int> g(n, 0);
    for(int i = 0; i < n/2; i++){
        int choc = dista(gen);//random letters
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
    pq.emplace(0, m.start);//start

    while(!pq.empty()){
        int distance = pq.top().first, position = pq.top().second;
        pq.pop();//remove searched

        if(position == m.end){//if successful
            m.path_length = distance;
            return;
        }

        if(m.visited[position] < distance){
            continue;
        }

        vector<int> directions;
        
        if(position%m.col != m.col-1){
            directions.push_back(1);
        }
        if(position/m.col != m.row-1){
            directions.push_back(m.col);
        }
        if(position/m.col != 0){
            directions.push_back(-m.col);
        }
        if(position%m.col != 0){
            directions.push_back(-1);
        }

        for (int dir : directions) {//check each direction
            int neighbor = position + dir;

            if (neighbor >= 0 && neighbor < m.row * m.col) {
                int new_distance = distance + m.tiles[neighbor];//distance of new path

                if (m.visited[neighbor] == -1 || new_distance < m.visited[neighbor]) {
                    m.visited[neighbor] = new_distance;
                    pq.emplace(new_distance, neighbor);
                    m.path[neighbor] = position;//add to traversed
                }
            }
        }
    }
}

void store_map(maze &m){
    int num;
    cin >> num;

    for(int i = 0; i < num; i++){
        char a;
        int b;
        cin >> a >> b;

        m.costs.emplace(make_pair(a, b));//add to dict
    }

    int row, col;
    cin >> row >> col;//init based on size
    m.tiles = vector<int>(col*row, 0);
    m.path = vector<int>(col*row, -1);

    for(int k = 0; k < col; k++){
        for(int j = 0; j < row; j++){
            char c;
            cin >> c;

            m.tiles[j*col+k] = m.costs[c];//value of tile
        }
    }
    m.visited = vector<signed int>(row*col, -1);//init

    int tx, ty;
    cin >> tx >> ty;
    m.start = ty*col+tx;

    cin >> tx >> ty;
    m.end = ty*col+tx;

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

    for(int i = m->end; i != -1; i = m->path[i]){
	   s.push_back(to_string(i%m->col) + " " + to_string(i/m->col));
    }

    reverse(s.begin(), s.end());
    //reverse(s[s.size()-1].begin(), s[s.size()-1].end());

    for(auto j = s.begin(); j != s.end(); ++j){
        cout<<*j<<endl;
    }

    return 0;
}

