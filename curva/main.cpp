#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

ifstream in_file("curva.in");
ofstream out_file("curva.out");

struct Result;
struct Point;

struct Point{
    long x, y;
};

struct Result{
    Point ini, cur, fin;
};

long curva(vector< vector<int> > barrio, int &K, Result &result);

int main()
{
    int M = 0, K = 0;
    vector< vector<int> > barrio;
    Result result;
    in_file >> M;

    int altura = 0;
    for(int i = 0; i < M; i++){
        vector< int > talturas;
        for(int j = 0; j < M; j++)
        {
            in_file >> altura;
            talturas.push_back(altura);
        }
        barrio.push_back(talturas);
    }

    curva(barrio, K, result);

    if(K != 0)
        cout << "El largo de la pista es " << K << "." << endl;
    else {
        cout << "Sin pistas" << endl;
        return 0;
    }
    // Columna primero y despues row
    cout << "Inicio: (" << result.ini.y << "," << result.ini.x << ") Curva(" << result.cur.y << "," << result.cur.x << ") Fin(" << result.fin.y << "," << result.fin.x << ")" << endl;

    return 0;
}

// Implementacion -------

int Direction[][2] = {{1,0}, {0, 1}, {-1, 0}, {0, -1}};

struct Tramo : public Result {
    int largo = 0;
    bool operator < (Tramo & r) { return this->largo < r.largo; }
    void addonetoall () {
        ini.x++;
        ini.y++;
        cur.x++;
        cur.y++;
        fin.x++;
        fin.y++;
    }
};

struct Cell : public Point{
    int DFS(int direction, int capacity, Tramo &tramo);
    int altura;
    vector<Cell*> adj;
};

vector< vector <Cell*> > cells;
vector< Tramo > tramos;

int Cell::DFS(int direction, int capacity, Tramo &tramo)
{
    // si no puede seguir la direccion entrante.
    if(adj[direction] == nullptr)
    {
        // si tiene la capasidad de curvar.
        if(capacity > 0)
        {
            tramo.cur.x = x;
            tramo.cur.y = y;
            // para comparar los resultados a todas direcciones.
            int max_num = 0, max_index = 0;
            for(int d = 0; d < 4; d++)
            {
                // si no es la direccion entrante y tiene nodo a proxima nodo.
                if(adj[d] && d != direction){
                    int result = adj[d]->DFS(d, capacity - 1, tramo);
                    if(max_num < result)
                        max_num = result;
                }
            }
            return max_num;
        }
        else
        {
            tramo.fin.x = x;
            tramo.fin.y = y;
            return 1;
        }
    }
    // seguis la direccion porque tiene nodo.
    return 1 + adj[direction]->DFS(direction, capacity, tramo);
}

long curva(vector< vector<int> > barrio, int &k, Result &result)
{
    int m = barrio.size();
    cells.resize(m);
    for(int i = 0; i < m; i++)
    {
        cells[i].resize(m);
        for(int j = 0; j < m; j++)
        {
            Cell *c = new Cell;
            c->x = i; c->y = j;
            c->altura = barrio[i][j];
            cells[i][j] = (c);
        }
    }

    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < m; j++)
        {
            for(int d = 0; d < 4; d++)
            {
                Cell *current = cells[i][j];
                if(i + Direction[d][0] < 0 || i + Direction[d][0] >= m || j + Direction[d][1] < 0 || j + Direction[d][1] >= m)
                    { current->adj.push_back(nullptr); continue;}
//                cout << i+ Direction[d][0] << " " << j + Direction[d][1] << endl;
                Cell *next = cells[i+ Direction[d][0]][j + Direction[d][1]];
//                cout << "next :" << next->altura << endl;

//                cout << current->x << " " << current->y << " " << current->adj.size() << endl;
                Cell *cell = (next->altura < current->altura) ? next : nullptr;
                current->adj.push_back(cell);
            }
        }
    }
//    cout << "...." << endl;
    int max_num = 0;
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < m; j++)
        {
            for(int d = 0; d < 4; d++)
            {
                if(cells[i][j]->adj[d] == nullptr)
                    continue;
                Tramo tramo;
                tramo.ini.x = i;
                tramo.ini.y = j;
                int r = cells[i][j]->DFS(d, 1, tramo);
                tramo.largo = r;
                tramos.push_back(tramo);
                max_num = (max_num < r) ? r : max_num;
            }
        }
    }

    std::sort(tramos.begin(), tramos.end());
    auto it = std::max_element(tramos.begin(), tramos.end());
    int number = std::distance(it, tramos.end());
    cout << "Possible :" << number << endl;
    it++;
//    cout << (int)it->cur.x << "," << (int)it->cur.y << " " << it->largo << endl;
//    cout << it << endl;
    k = max_num;
    it->addonetoall();
    result = *it;
}
