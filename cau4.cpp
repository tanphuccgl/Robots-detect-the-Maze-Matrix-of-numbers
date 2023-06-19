#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

pair<int, int> findMaxDirection(vector<vector<int>> &maze, vector<vector<bool>> &visited, int x, int y)
{
    int rows = maze.size();
    int cols = maze[0].size();

    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    int maxVal = -1;
    pair<int, int> maxDir = {-1, -1};

    for (auto &dir : directions)
    {
        int new_x = x + dir.first;
        int new_y = y + dir.second;

        if (new_x >= 0 && new_x < rows && new_y >= 0 && new_y < cols && !visited[new_x][new_y] && maze[new_x][new_y] > maxVal)
        {
            maxVal = maze[new_x][new_y];
            maxDir = {new_x, new_y};
        }
    }

    return maxDir;
}

void printMaxPath(vector<vector<int>> &maze, int startX1, int startY1, int startX2, int startY2)
{
    int rows = maze.size();
    int cols = maze[0].size();

    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    unordered_set<int> visitedCells1, visitedCells2;

    int maxPath1 = 0;
    int maxPath2 = 0;

    int x1 = startX1;
    int y1 = startY1;

    int x2 = startX2;
    int y2 = startY2;

    cout << "Robot 1 Path: " << endl;
    while (true)
    {
        visited[x1][y1] = true;
        visitedCells1.insert(x1 * cols + y1);
        maxPath1 += maze[x1][y1];
        cout << maze[x1][y1] << endl;

        pair<int, int> next = findMaxDirection(maze, visited, x1, y1);
        if (next.first == -1 && next.second == -1)
        {
            break;
        }

        x1 = next.first;
        y1 = next.second;

        // Kiểm tra xem ô tiếp theo đã được đi qua bởi robot 2 chưa
        if (visitedCells2.find(x1 * cols + y1) != visitedCells2.end())
        {
            // Nếu đã được đi qua, tìm ô khác có giá trị lớn nhất
            pair<int, int> alternative = findMaxDirection(maze, visited, x1, y1);
            if (alternative.first == -1 && alternative.second == -1)
            {
                // Nếu không còn ô khả dụng, kết thúc vòng lặp
                break;
            }
            else
            {
                // Chọn ô khác có giá trị lớn nhất để tiếp tục đi
                x1 = alternative.first;
                y1 = alternative.second;
            }
        }
    }

    cout << "Max Path for Robot 1: " << maxPath1 << endl;

    cout << endl;

    cout << "Robot 2 Path: " << endl;
    while (true)
    {
        visited[x2][y2] = true;
        visitedCells2.insert(x2 * cols + y2);
        maxPath2 += maze[x2][y2];
        cout << maze[x2][y2] << endl;

        pair<int, int> next = findMaxDirection(maze, visited, x2, y2);
        if (next.first == -1 && next.second == -1)
        {
            break;
        }

        x2 = next.first;
        y2 = next.second;

        // Kiểm tra xem ô tiếp theo đã được đi qua bởi robot 1 chưa
        if (visitedCells1.find(x2 * cols + y2) != visitedCells1.end())
        {
            // Nếu đã được đi qua, tìm ô khác có giá trị lớn nhất
            pair<int, int> alternative = findMaxDirection(maze, visited, x2, y2);
            if (alternative.first == -1 && alternative.second == -1)
            {
                // Nếu không còn ô khả dụng, kết thúc vòng lặp
                break;
            }
            else
            {
                // Chọn ô khác có giá trị lớn nhất để tiếp tục đi
                x2 = alternative.first;
                y2 = alternative.second;
            }
        }
    }

    cout << "Max Path for Robot 2: " << maxPath2 << endl;
}

int main()
{
    vector<vector<int>> maze = {
        {2, 1, 14, 12, 17},
        {3, 16, 22, 91, 23},
        {4, 56, 87, 31, 65},
        {27, 43, 90, 100, 101},
        {76, 54, 32, 99, 66},
        {178, 154, 150, 200, 543},
    };

    int startX1 = 0;
    int startY1 = 1;
    int startX2 = 0;
    int startY2 = 4;

    cout << "Maze:" << endl;
    for (auto &row : maze)
    {
        for (auto &cell : row)
        {
            cout << cell << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "Robot Paths:" << endl;
    printMaxPath(maze, startX1, startY1, startX2, startY2);

    return 0;
}
