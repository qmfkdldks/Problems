#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <vector>

using namespace std;

ifstream in_file("circuito.in");
ofstream out_file("circuito.out");

// UP RIGHT DOWN LEFT
//int DIRECTION [][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };

int circuito(int EO, int NS, int E, int** Esquinas);

typedef vector<int> VInt;

int main()
{
    int EO, NS, E;
    in_file >> EO >> NS >> E;
    int** Esquinas = new int*[E];
    for(int i = 0; i < E; ++i)
    {
        Esquinas[i] = new int[2];
        int eo, ns;
        in_file >> eo >> ns;
        Esquinas[i][0] = eo;
        Esquinas[i][1] = ns;
//        cout << Esquinas[i][0] << "," << Esquinas[i][1] << endl;
    }
    int largo = circuito(EO, NS, E, Esquinas);
    cout << "Archivo con " << E << " esquinas da largo " << largo << "." << endl;
    return 0;
}
int max_largo = 0;
int circuito(int EO, int NS, int E, int** Esquinas)
{
    vector< vector <int> > esquinas;
    for(int i = 0; i < E; ++i)
    {
        VInt p;
        p.push_back(Esquinas[i][0]);
        p.push_back(Esquinas[i][1]);
        esquinas.push_back(p);
//        cout << p[0] << " " << p[1] << endl;
    }
    sort(esquinas.begin(), esquinas.end());
//    int ** end = Esquinas + E;
    // loop throught esquinas
    for(int i = 0; i < E; ++i)
    {
        VInt c_element = esquinas[i];
//        cout << "Start .." << c_element[0] << "," << c_element[1] << endl;
        for(auto right = esquinas.begin(); (right = std::find_if(right, esquinas.end(), [c_element](VInt p){
                    return p[0] == c_element[0] && c_element[1] < p[1];
                })) != esquinas.end(); )
                {
//                    cout << "Right:" << (*right)[0] << "," << (*right)[1] << endl;
                    for(auto down = esquinas.begin(); (down = std::find_if(down, esquinas.end(), [c_element](VInt p){
                        return p[1] == c_element[1] && c_element[0] < p[0];
                    })) != esquinas.end(); )
                    {
//                        cout << "Down:" << (*down)[0] << "," << (*down)[1] << endl;
                        VInt right_down = {(*down)[0], (*right)[1]};

                        auto result = find_if(esquinas.begin(), esquinas.end(), [right_down](VInt p){
                            return p[0] == right_down[0] && p[1] == right_down[1];
                        });

                        if(result != esquinas.end())
                        {
//                            cout << "Right down:"<< (*result)[0] << "," << (*result)[1] << endl;
                            int largo = 0;
                            largo += (*right)[1] - c_element[1];
                            largo += (*down)[0] - c_element[0];
                            largo = largo * 2;
//                            cout << "Largo" << largo << endl;
                            max_largo = (max_largo < largo) ? largo : max_largo;
                        }

                        down++;
                    }
                    right++;
                }
    }
//    cout << "Max:" << max_largo << endl;
    return max_largo;
    return 0;
}
