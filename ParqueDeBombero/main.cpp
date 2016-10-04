#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>
#include <vector>

using namespace std;

ifstream in_file("10278.in");
ofstream out_file("10278.out");

struct Vertex;
int NCaso, NParque, NInter;

vector<Vertex> vertices;
vector<int> ParqueId;

int index = 1;

struct Vertex {
//    Vertex() { this->id = index; index++; }
    int id, cost = INT_MAX;
    bool isSelected = false;
    vector< pair<Vertex*, int> > nodes;
    Vertex* parent;
    int operator + (const Vertex & v) {
        return this->cost + v.cost;
    }
};

int min_vertex()
{
   // Initialize min value
   int min = INT_MAX, min_index = -1;

   for (int v = 0; v < vertices.size(); v++)
     if (vertices[v].isSelected == false && vertices[v].cost <= min)
         min = vertices[v].cost, min_index = v;

   return min_index;
}

void dijkstra()
{
    for(int i = 0; i < NInter - 1; ++i)
    {
        int mini_id = min_vertex();
        if(mini_id == -1)
            break;
        Vertex* mini_it = &vertices[mini_id];

        mini_it->isSelected = true;
        cout << "current selected :" << mini_it->id << endl;
        // Update adjacent vertices cost
        for_each(mini_it->nodes.begin(), mini_it->nodes.end(), [mini_it](pair<Vertex*, int>& element){
            Vertex *adj = element.first;
            int edge_cost = element.second;

            if(adj->isSelected == true)
                return;

            int sum = edge_cost + mini_it->cost;

            if(sum < adj->cost) {
                adj->cost = sum;
                adj->parent = &(*mini_it);
                cout << adj->id << " :" << adj->cost << endl;
            }
        });
    }
}

int main()
{
    in_file >> NCaso;
    for(int i = 0; i < NCaso; ++i)
    {
        in_file >> NParque >> NInter;
        vertices.resize(NInter);

        for(int j = 0; j < NParque; ++j)
        {
            int p;
            in_file >> p;
            ParqueId.push_back(p);
        }

        int v1, v2, cost;
        while(in_file >> v1 >> v2 >> cost)
        {
            cout << v1 << " " << v2 << " " << cost << endl;
//            v1--; v2--;
            vertices[v1].id = v1;
            vertices[v2].id = v2;
            vertices[v1].nodes.push_back({&vertices[v2], cost});
            vertices[v2].nodes.push_back({&vertices[v1], cost});
        }

        vertices[0].cost = 0;
        dijkstra();
    }

    return 0;
}
