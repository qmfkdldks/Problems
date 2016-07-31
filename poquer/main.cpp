#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>

void startGame(std::string * manos, std::string * result);

int main()
{

    std::ifstream file;
    file.open("manos.in");

    int gameCount;
    std::string *str;

    if(file.is_open())
    {
        gameCount = std::count(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>(), '\n');
        str = new std::string[gameCount];
        file.seekg(0);

        for(int i = 0; i < gameCount; ++i)
        {
            char c;
            for(int j = 0; j < 20 && file.good(); ++j)
            {
                file >> c;
                str[i].push_back(c);
            }
        }

        for(int i = 0; i < gameCount; ++i)
        {
            std::cout << i << ":" << str[i] << std::endl;
        }
    }

    file.clear();
    file.close();
    return 0;
}

#define NSUITS 4
#define NCARDS 52

// Code section
char values[] = "23456789JQKA";
char suits[] = "CDHS";

int rank_card(char value, char suit)
{
    int i,j;

// Find the given card
    for(i = 0; i < (NCARDS/NSUITS); ++i)
        if(values[i] == value)
            for(j = 0; j < NSUITS; ++j)
                if(suits[j] == suit)
                    return (i * NSUITS + j);

    /*return card number in 52 number of card
    after searching card number(12) and shape(4)
    each card has four different shape
    so multiplying number of card with 4 gives 52*/
}

struct Card
{
    Card(char s, char n) : shape(s), number(n){ value = rank_card(shape, number); }
    int index() {
        for(int i = 0; i < (NCARDS / NSUITS); ++i)
            if(values[i] == number)
                return i;
    }
    char shape, number;
    int value;
};

struct Player
{
    Player(std::string cartas) {

    }
};



void startGame(std::string * manos, std::string * result)
{

}
