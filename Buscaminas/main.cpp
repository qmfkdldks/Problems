#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <regex>
#include <iterator>
#include <sstream>

using namespace std;

regex reg("([\\d] [\\d])");

void calculateZone(int gameCount, string terowt);

int main()
{
    ifstream in("10189.inp");
    if(in.is_open())
    {
        int fieldCount;
        smatch result;
        stringstream strStream;
        strStream << in.rdbuf();//read the file
        string str = strStream.str();//str holds the content of the file

        cout << str << endl;//columnou can do ancolumnthing with the string!!!

        const sregex_iterator end;

        fieldCount = std::distance(sregex_iterator(str.begin(), str.end(), reg), end);
        cout << "Count:" << fieldCount << endl;

        for(auto it = sregex_iterator(str.begin(), str.end(), reg); it != end; ++it)
        {
            cout << (*it)[0] << endl;
        }

        calculateZone(fieldCount, str);
        in.clear();
        in.close();
    }


    return 0;
}

typedef vector< vector <char> > Table;

bool point_up(int row, int column, Table& t)
{
    cout << "Row and column size:" << t.size() << "," << t[0].size() << endl;
    cout << "row and column are:" << row << "," << column << endl;
    if ((row < t.size() && row >= 0) && (column < t[0].size() && column >= 0))
    {
        char c = t[row][column];
        cout << "is digit :" << isdigit(c) << endl;

        if(isdigit(c))
        {
            int number = c - '0';
            cout << "number :" << number << endl;
            ++number;
            c = number + '0';
            cout << "number to char :" << c << endl;
            t[row][column] = c;
        }
    }
}

struct Campo
{
    Campo(int counter, int inrow, int incolumn, Table inTable)
    {
        mName = "Field #" + to_string(counter) + ":";
        row = inrow;
        column = incolumn;
        mTable = inTable;
    }

    void convert()
    {
        for(int i = 0; i < row; ++i)
            for(int j = 0; j < column; ++j)
        {
            char c = mTable[i][j];
            cout << i << "," << j << " : " << c << endl;
            if(c == '*')
            {
                // up
                point_up(i - 1, j, mTable);
                // up right
                point_up(i - 1, j + 1, mTable);
                // right
                point_up(i, j + 1, mTable);
                // down right
                point_up(i + 1, j + 1, mTable);
                // down
                point_up(i + 1, j, mTable);
                // down left
                point_up(i + 1, j - 1, mTable);
                // left
                point_up(i, j - 1, mTable);
                // up left
                point_up(i - 1, j - 1, mTable);
            }

        }
    }

    string to_s()
    {
        stringstream stream;
        stream << mName << '\n';

        for(int i = 0; i < row; ++i)
        {
            for(int j = 0; j < column; ++j)
                stream << mTable[i][j];

            stream << endl;
        }

        return stream.str();
    }

    string mName;
    int row, column;
    Table mTable;
};

void calculateZone(int gameCount, string terowt)
{
    stringstream stream;
    stream << terowt;

    ofstream out("10189.oup");

    for(int counter = 1; counter <= gameCount; ++counter)
    {
        int row,column;
        stream >> row >> column;

        cout << "row:column =" << row << "," << column << endl;

        if(row == column && row == 0)
            break;
        else
        {
            Table t;
            t.resize(row);

            for(int i = 0; i < row; ++i)
            {
                t[i].resize(column);
                for(int j = 0; j < column; ++j)
                {
                    char c;
                    stream >> c;
                    if(c == '.')
                        c = '0';

                    t[i][j] = c;

                    cout << t[i][j] << endl;
                }
            }

            Campo campo(counter, row, column, t);
            campo.convert();
            cout << "TO STRING : " << endl << campo.to_s() << endl;
            out << campo.to_s() << endl;
        }

    }

    out.clear();
    out.close();
}

