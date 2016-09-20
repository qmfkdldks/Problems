#include <iostream>
#include <fstream>
#include <queue>
#include <algorithm>

// using BFS Breadth First Traversal

using namespace std;

ifstream in_file("laberinto.in");
ofstream out_file("laberinto.out");

// UP RIGHT DOWN LEFT
int Direction[][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

int A, B, NW;
bool ** HWalls;
bool ** VWalls;
struct Point;

struct Point {
    Point () {}
    Point (int in_x, int in_y, Point *in_parent = nullptr) : x(in_x), y(in_y), parent(in_parent) {}
    int x, y;
    Point *parent;
};

bool point_compare(Point P1, Point P2)
{
    return P1.x < P2.x || (P1.x == P2.x && P1.y < P2.y);
}

void init_data()
{
    in_file >> A >> B >> NW;

    // initialize dynamic array
    VWalls = new bool*[A + 1];
    for(int i = 0; i < A + 1; ++i) {
        VWalls[i] = new bool[B];
        std::fill(VWalls[i], VWalls[i] + B, 0);
    }
    HWalls = new bool*[A];
    for(int i = 0; i < A; ++i) {
        HWalls[i] = new bool[B + 1];
        std::fill(HWalls[i], HWalls[i] + B + 1, 0);
    }

//    cout << "Vertical walls" << endl;
//    for(int i = 0; i < A + 1; ++i) {
//        for(int j = 0; j < B; ++j)
//            cout << std::boolalpha << i << "," << j << " :" << VWalls[i][j] << "  ";
//        cout << endl;
//    }
//    cout << "Horizontal walls" << endl;
//    for(int i = 0; i < A; ++i) {
//        for(int j = 0; j < B + 1; ++j)
//            cout << std::boolalpha << i << "," << j << " :" << HWalls[i][j] << "  ";
//        cout << endl;
//    }


    // Create edge walls.
    for(int i = 0; i < B; ++i){
        VWalls[0][i] = true;
        VWalls[A][i] = true;
    }
    for(int i = 0; i < A; ++i){
        HWalls[i][0] = true;
        HWalls[i][B] = true;
    }


    for(int i = 0; i < NW; ++i)
    {
        // the order of the entry is random, so we
        // must keep watching which point is greater and smaller.
        Point p1, p2;
        in_file >> p1.x >> p1.y >> p2.x >> p2.y;
        if(!point_compare(p1, p2)) // if p1 is not initial (smaller) than p2
            swap(p1, p2);
        if(p1.x == p2.x) // Vertical wall
        {
            // change y position
            int x = p1.x;
            int y1 = p1.y, y2 = p2.y;
            for(int i = y1; i < y2; ++i)
                VWalls[x][i] = 1;
        }
        else
        {
            int y = p1.y;
            int x1 = p1.x, x2 = p2.x;
            for(int i = x1; i < x2; ++i)
                HWalls[i][y] = 1;
        }
    }

//    out_file << "Vertical walls" << endl;
//    for(int i = 0; i < A + 1; ++i) {
//        for(int j = 0; j < B; ++j)
//            out_file << std::boolalpha << i << "," << j << " :" << VWalls[i][j] << "  ";
//        out_file << endl;
//    }
//    out_file << "Horizontal walls" << endl;
//    for(int i = 0; i < A; ++i) {
//        for(int j = 0; j < B + 1; ++j)
//            out_file << std::boolalpha << i << "," << j << " :" << HWalls[i][j] << "  ";
//        out_file << endl;
//    }
}

int parent_track(Point *p)
{
    if(p->parent)
        return 1 + parent_track(p->parent);
    else
        return 1;
}

void BFS(Point current)
{
    int mini_path = -1;

    bool ** visited = new bool*[A];
    for(int i = 0; i < A; ++i) {
        visited[i] = new bool[B];
        std::fill(visited[i], visited[i] + B, false);
    }

    visited[current.x][current.y] = true;

    queue<Point> q;
    q.push(current);

    while(!q.empty())
    {
        current = q.front();
//        cout << "current: " << current.x << "," << current.y << endl;
        q.pop();

        if(current.x == A - 1 && current.y == B - 1)
        {
            mini_path = parent_track(current.parent);
            break;
        }

        // for all Directions
        for(int d = 0; d < 4; ++d)
        {
            Point next(current.x + Direction[d][0], current.y + Direction[d][1]);

            bool blocked = false;

            switch(d)
            {
            case 0:
                blocked = HWalls[next.x][next.y]; break;
            case 1:
                blocked = VWalls[next.x][next.y]; break;
            case 2:
                blocked = HWalls[next.x][next.y + 1]; break;
            case 3:
                blocked = VWalls[next.x + 1][next.y]; break;
            }

            if(next.x >= 0 && next.x < A && next.y >= 0 && next.y < B) {
//                cout << std::boolalpha << "filter :" << !visited[next.x][next.y] << "," << !blocked << endl;
                if(!visited[next.x][next.y] && !blocked)
                {
                    visited[next.x][next.y] = true;
                    Point *p = new Point(current.x, current.y);
                    p->parent = current.parent;
                    next.parent = p;
                    q.push(next);
                }
            }
        }
    }

    if(mini_path != -1)
        out_file << mini_path << endl;
    else
        out_file << "imposible" << endl;
}

int main()
{
    init_data();
    BFS({0,0});
    return 0;
}
