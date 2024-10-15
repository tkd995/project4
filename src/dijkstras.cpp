// dijsktras.cpp
#include <map>
#include <vector>
#include <iostream>
#include <experimental/random>

using namespace std;

// Main Execution

struct maze{
    map<char, int> costs;
    vector<pair<int, int*>> tiles;
    int start, end;
    int row, col;
    vector<signed int> visited;
};

void generate_map(int n){

    cout<<n/2<<endl;
    vector<int> gen(n, 0);
    for(int i = 0; i < n/2; i++){
        int choc = randint(97, 122);
        if(gen.find(choc) == gen.end()){
            cout<< i << " " << randint(1, n+1) << endl;
            gen[i] = choc;
        }
    }

    cout<< n << " " << n;

    for(int i = 0; i < m->row; i++){
        for(int j = 0; j < m->col; j++){
            int b = gen[randint(0, n)];
            while(!b){
                b = gen[randint(0, n)];
            }
            cout<< (char)b << " ";
        }
        cout<<endl;
    }

    cout << "0 0" <<endl;
    cout<< n << " " << n << endl;
    return;
}

void dikstras(maze &m, int start, int distance){

    if(start == m->end){//exit condition
        return;
    }
    distance += m.tiles[start];//progress for recursive pass

    if(m->visited[start] != -1){//change block
        if(m->visited[start] > distance){
            m->visited[start] = distance;
        }
    }
    else{
        m->visited[start] = distance;
    }

    if(start != 0){//left
        dikstras(m, start-1, distance);
    }
    if(start != m->col*m->row - 1){//right
        dikstras(m, start+1, distance);
    }
    if(start/m->col != 0){//up
        dikstras(m, start-m->col, distance);
    }
    if(start/m->col != m->row){//down
        dikstras(m, start+m->col, distance);
    }
}

void store_map(maze &m){
    int num;
    cin << num;

    for(int i = 0; i < num; i++){
        char a;
        int b;
        cin << a << b;

        m.costs.emplace(make_pair(a, b));
    }

    int row, col;
    cin << row << col;
    for(int k = 0; k < col; k++){
        for(int j = 0; j < row; j++){
            char c;
            cin << c;

            m.tiles[j*row+k] = m.costs[c]->second;
        }
    }
    visited = vector<signed int>(row*col, -1);
    int tx, ty;
    cin << tx << ty;
    m.start = tx*row+ty

    cin << tx << ty;
    m.end = tx*row+ty

    m->row = row;
    m->col = col;

    return;
}

int main(int argc, char *argv[]) {
    maze* m = new maze;
    store_map(*m);
    dikstras(*m, m->start, 0);

    return 0;
}

