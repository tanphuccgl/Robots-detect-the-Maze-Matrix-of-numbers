#include <iostream>
#include <vector>

using namespace std;

struct Point {
    int x;
    int y;
};

// Hàm tìm hướng đi có giá trị lớn nhất từ vị trí (x, y) trong ma trận maze
// visited: ma trận đánh dấu các ô đã được thăm
// Trả về một cặp gồm giá trị lớn nhất và vị trí của ô tiếp theo
pair<int, Point> findMaxDirection(vector<vector<int>>& maze, vector<vector<bool>>& visited, int x, int y) {
    int rows = maze.size();
    int cols = maze[0].size();
    vector<Point> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int maxVal = -1;
    Point maxDir = {-1, -1};

    for (auto& dir : directions) {
        int new_x = x + dir.x;
        int new_y = y + dir.y;
        if (new_x >= 0 && new_x < rows && new_y >= 0 && new_y < cols && !visited[new_x][new_y] && maze[new_x][new_y] > maxVal) {
            maxVal = maze[new_x][new_y];
            maxDir = {new_x, new_y};
        }
    }

    return make_pair(maxVal, maxDir);
}

// Hàm in ra đường đi có giá trị lớn nhất bắt đầu từ vị trí (x, y)
// maze: ma trận mê cung
// visited: ma trận đánh dấu các ô đã được thăm
// x, y: tọa độ ban đầu
// maxPath: biến lưu giá trị lớn nhất của đường đi
void printMaxPathHelper(vector<vector<int>>& maze, vector<vector<bool>>& visited, int x, int y, int& maxPath) {
    visited[x][y] = true;
    maxPath += maze[x][y];
    cout << maze[x][y] << endl;

    pair<int, Point> next = findMaxDirection(maze, visited, x, y);
    if (next.second.x != -1 && next.second.y != -1) {
        printMaxPathHelper(maze, visited, next.second.x, next.second.y, maxPath);
    }
}

// Hàm tìm và in ra các vị trí mà hai robot đi trùng nhau
// maze: ma trận mê cung
// visited: ma trận đánh dấu các ô đã được thăm
// x1, y1: tọa độ ban đầu của robot 1
// x2, y2: tọa độ ban đầu của robot 2
// overlappingPositions: vector lưu trữ các vị trí trùng nhau
void printOverlappingPositions(vector<vector<int>>& maze, vector<vector<bool>>& visited, int x1, int y1, int x2, int y2, vector<Point>& overlappingPositions) {
    if (x1 == x2 && y1 == y2) {
        overlappingPositions.push_back({x1, y1});
    } else {
        visited[x1][y1] = true;
        visited[x2][y2] = true;

        pair<int, Point> next1 = findMaxDirection(maze, visited, x1, y1);
        pair<int, Point> next2 = findMaxDirection(maze, visited, x2, y2);

        if (next1.second.x != -1 && next1.second.y != -1) {
            printOverlappingPositions(maze, visited, next1.second.x, next1.second.y, x2, y2, overlappingPositions);
        }

        if (next2.second.x != -1 && next2.second.y != -1) {
            printOverlappingPositions(maze, visited, x1, y1, next2.second.x, next2.second.y, overlappingPositions);
        }
    }
}

// Hàm in ra đường đi có giá trị lớn nhất của hai robot
// maze: ma trận mê cung
// startX1, startY1: tọa độ ban đầu của robot 1
// startX2, startY2: tọa độ ban đầu của robot 2
void printMaxPath(vector<vector<int>>& maze, int startX1, int startY1, int startX2, int startY2) {
    int rows = maze.size();
    int cols = maze[0].size();
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    int maxPath1 = 0;
    int maxPath2 = 0;
    vector<Point> overlappingPositions;

    cout << "Robot 1 Path:" << endl;
    printMaxPathHelper(maze, visited, startX1, startY1, maxPath1);

    cout << "Robot 2 Path:" << endl;
    printMaxPathHelper(maze, visited, startX2, startY2, maxPath2);

    cout << "Robot 1 Path Max: " << maxPath1 << endl;
    cout << "Robot 2 Path Max: " << maxPath2 << endl;

    visited = vector<vector<bool>>(rows, vector<bool>(cols, false));
    cout << "Overlapping Positions:" << endl;
    printOverlappingPositions(maze, visited, startX1, startY1, startX2, startY2, overlappingPositions);

    if (overlappingPositions.empty()) {
        cout << "No overlapping positions." << endl;
    } else {
        for (const auto& pos : overlappingPositions) {
            cout << "(" << pos.x << ", " << pos.y << ")" << endl;
        }
    }
}

int main() {
    vector<vector<int>> maze = {
        {2, 1, 14, 12, 17},
        {3, 16, 22, 91, 23},
        {4, 56, 87, 31, 65},
        {27, 43, 90, 100, 101},
        {76, 54, 32, 99, 66},
        {178, 154, 150, 200, 543}
    };

    int startX1 = 0;
    int startY1 = 0;
    int startX2 = 5;
    int startY2 = 4;

    printMaxPath(maze, startX1, startY1, startX2, startY2);

    return 0;
}
