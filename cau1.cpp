#include <iostream>
#include <vector>

using namespace std;

// Khai báo struct Point để đại diện cho một tọa độ trong ma trận
struct Point {
    int x;
    int y;
};

// Hàm tìm hướng đi có giá trị lớn nhất
pair<int, Point> findMaxDirection(vector<vector<int>>& maze, vector<vector<bool>>& visited, int x, int y) {
    int rows = maze.size();
    int cols = maze[0].size();

    // Các hướng đi (trên, dưới, trái, phải)
    vector<Point> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    int maxVal = -1;
    Point maxDir = {-1, -1};

    // Duyệt qua các hướng đi và tìm hướng có giá trị lớn nhất
    for (auto& dir : directions) {
        int new_x = x + dir.x;
        int new_y = y + dir.y;

        // Kiểm tra xem ô mới có hợp lệ và lớn hơn ô hiện tại hay không
        if (new_x >= 0 && new_x < rows && new_y >= 0 && new_y < cols && !visited[new_x][new_y] && maze[new_x][new_y] > maxVal) {
            maxVal = maze[new_x][new_y];
            maxDir = {new_x, new_y};
        }
    }

    // Trả về giá trị lớn nhất và tọa độ của ô có giá trị lớn nhất
    return make_pair(maxVal, maxDir);
}

// Hàm đệ quy để in ra đường đi có giá trị lớn nhất
void printMaxPathHelper(vector<vector<int>>& maze, vector<vector<bool>>& visited, int x, int y, int& maxPath) {
    // Đánh dấu ô hiện tại đã được đi qua
    visited[x][y] = true;
    // Cộng giá trị của ô hiện tại vào maxPath
    maxPath += maze[x][y];
    // In ra giá trị của ô hiện tại
    cout << maze[x][y] << endl;

    // Tìm hướng có giá trị lớn nhất và tiếp tục tìm đường đi từ ô đó
    pair<int, Point> next = findMaxDirection(maze, visited, x, y);

    // Nếu tìm được hướng đi tiếp theo
    if (next.second.x != -1 && next.second.y != -1) {
        // Tiếp tục đệ quy từ ô tiếp theo
        printMaxPathHelper(maze, visited, next.second.x, next.second.y, maxPath);
    }
}

// Hàm chính để in ra đường đi có giá trị lớn nhất
void printMaxPath(vector<vector<int>>& maze, int startX, int startY) {
    int rows = maze.size();
    int cols = maze[0].size();

    // Tạo một mảng visited để lưu trạng thái đi qua của các ô
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));

    int maxPath = 0;
    // Gọi hàm đệ quy để in ra đường đi có giá trị lớn nhất
    printMaxPathHelper(maze, visited, startX, startY, maxPath);

    cout << "Path Max: " << maxPath << endl;
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

    int startX = 0;
    int startY = 0;

    // Gọi hàm printMaxPath để in ra đường đi có giá trị lớn nhất
    printMaxPath(maze, startX, startY);

    return 0;
}
