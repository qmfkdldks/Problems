#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

void startGame(string * manos, string * result);

int main()
{

    ifstream file;
    file.open("manos.in");

    int gameCount;
    string *str;

    gameCount = count(std::istreambuf_iterator<char>(file), istreambuf_iterator<char>(), '\n');
    str = new string[gameCount];


    for(int i = 0; i < gameCount; ++i)
    {
        char c;
        while(c = '\n')
        {
            file >> c;
            str[i].push_back(c);
            cout << str[i] << endl;
        }
    }



    file.clear();
    file.close();
    return 0;
}

// Code section

void startGame(string * manos, string * result)
{


}
