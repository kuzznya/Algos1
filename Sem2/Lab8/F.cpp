#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

struct Point {
    int x;
    int y;
    Point() = default;
    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }
};

vector<char> BFSmod(vector<vector<char>>& maze, Point start, Point end) {
    vector<vector<vector<char>>> path(maze.size(), vector<vector<char>>(maze[0].size(), vector<char>()));
    queue<Point> q;
    q.push(start);
    while (!q.empty()) {
        Point u = q.front();
        q.pop();
        
        if (u.x == end.x && u.y == end.y) {
            return path[u.y][u.x];
        }
        
        if (u.y - 1 >= 0 && maze[u.y - 1][u.x] != '#' &&
        path[u.y - 1][u.x].empty() &&
        !(u.x == start.x && u.y - 1 == start.y)) {
            path[u.y - 1][u.x] = path[u.y][u.x];
            path[u.y - 1][u.x].push_back('U');
            q.push(Point(u.x, u.y - 1));
        }
        if (u.y + 1 < maze.size() && maze[u.y + 1][u.x] != '#' &&
        path[u.y + 1][u.x].empty() &&
        !(u.x == start.x && u.y + 1 == start.y)) {
            path[u.y + 1][u.x] = path[u.y][u.x];
            path[u.y + 1][u.x].push_back('D');
            q.push(Point(u.x, u.y + 1));
        }
        if (u.x - 1 >= 0 && maze[u.y][u.x - 1] != '#' &&
        path[u.y][u.x - 1].empty() &&
        !(u.x - 1 == start.x && u.y == start.y)) {
            path[u.y][u.x - 1] = path[u.y][u.x];
            path[u.y][u.x - 1].push_back('L');
            q.push(Point(u.x - 1, u.y));
        }
        if (u.x + 1 < maze[u.y].size() && maze[u.y][u.x + 1] != '#' &&
        path[u.y][u.x + 1].empty() &&
        !(u.x + 1 == start.x && u.y == start.y)) {
            path[u.y][u.x + 1] = path[u.y][u.x];
            path[u.y][u.x + 1].push_back('R');
            q.push(Point(u.x + 1, u.y));
        }
    }
    return vector<char>();
}

int main() {
    ifstream input("input.txt");
    int n, m;
    input >> n >> m;

    vector<vector<char>> maze(n, vector<char>(m, '.'));

    Point start, end;    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            input >> maze[i][j];
            if (maze[i][j] == 'S') {
                start.y = i;
                start.x = j;
            }
            else if (maze[i][j] == 'T') {
                end.y = i;
                end.x = j;
            }
        }
    }
    input.close();
    
    vector<char> path = BFSmod(maze, start, end);

    ofstream output("output.txt");
    if (!path.empty()) {
        output << path.size() << endl;
        for (char c : path) {
            output << c;
        }
        output << endl;
    }
    else {
        output << -1 << endl;
    }
    output.close();
    return 0;
}