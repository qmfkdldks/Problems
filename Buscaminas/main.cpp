#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
ifstream in_file("10189.in");
ofstream out_file("10189.out");

struct Element;
typedef vector< vector <Element> > Table;
bool validate(int posx , int posy, int dx, int dy);

// up upright right rightdown down downleft left leftup
int Direction [][2] = { {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1} };

bool validate(int posx, int posy, int dx, int dy)
{
    bool xrange = posx > -1 && posx < dx;
    bool yrange = posy > -1 && posy < dy;
    return xrange && yrange;
}

struct Element
{
    Element(int i) : identity(i){}

    bool isMina() const { return identity == -1; }

    int identity = 0;
    int value = 0;
};

int main(int argc, char *argv[])
{
    int x, y, index = 1;
    while(in_file >> x >> y)
    {
        if(x == 0 && y == 0)
            break;
        if(index != 1)
            out_file << endl;

        Table table;
        for(int i = 0; i < x; ++i)
        {
            vector <Element> line;
            for(int j = 0; j < y; ++j)
            {
                char c;
                in_file >> c;
                int identity = (c == '*') ? -1 : 0;
                line.push_back(Element(identity));
            }
            table.push_back(line);
        }

        // if is mine do iterate throught all direction
        // and add 1 to each element.
        for(int i = 0; i < x; ++i)
            for(int j = 0; j < y; ++j)
                if(table[i][j].identity == -1)
                for(int d = 0; d < 8; ++d)
                {
                    int posx = i + Direction[d][0], posy = j + Direction[d][1];
                    if(validate(posx, posy, x, y))
                        ++table[posx][posy].value;
                }

        // Out put
        out_file << "Field #" << index << ":" << endl;
        for(int i = 0; i < x; ++i)
        {
            for(int j = 0; j < y; ++j)
                if(table[i][j].identity == -1)
                    out_file << "*";
                else
                    out_file << std::to_string(table[i][j].value);
            out_file << endl;
        }
        ++index;
    }
    return 0;
}
