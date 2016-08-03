#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>

void startGame(int gameCount, std::string * manos);

int main()
{

    std::ifstream file;
    file.open("manos.in");

    int gameCount;
    std::string *allCards;

    if(file.is_open())
    {
        gameCount = std::count(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>(), '\n');
        allCards = new std::string[gameCount];
        file.seekg(0);

        for(int i = 0; i < gameCount; ++i)
        {
            char c;
            for(int j = 0; j < 20 && file.good(); ++j)
            {
                file >> c;
                allCards[i].push_back(c);
            }
        }

        for(int i = 0; i < gameCount; ++i)
        {
            std::cout << i << ":" << allCards[i] << std::endl;
        }
    }

    startGame(gameCount, allCards);

    file.clear();
    file.close();
    return 0;
}

#define NSHAPES 4
#define NCARDS 52

// Code section
char values[] = "23456789JQKA";
char shapes[] = "CDHS";

int rank_card(char value, char suit)
{
    int i,j;

// Find the given card
    for(i = 0; i < (NCARDS/NSHAPES); ++i)
        if(values[i] == value)
            for(j = 0; j < NSHAPES; ++j)
                if(shapes[j] == suit)
                    return (i * NSHAPES + j);

    /*return card number in 52 number of card
    after searching card number(12) and shape(4)
    each card has four different shape
    so multiplying number of card with 4 gives 52*/
}

int convertToInt(char num)
{
    int pos = std::distance(values, std::find(values, values + 12, num));
    return pos;
}

struct Card
{
    Card() {}
    Card(char n, char s) : mShape(s), mNumber(n){ value = rank_card(mNumber, mShape); }
    int index() {
        for(int i = 0; i < (NCARDS / NSHAPES); ++i)
            if(values[i] == mNumber)
                return i;
    }


    bool operator < (const Card& right) const
    {
        return convertToInt(mNumber) < convertToInt(right.mNumber);
    }

    char mShape, mNumber;
    int value;
};

typedef std::vector<Card> Cards;

void rank_mano(Cards inCards, int &index, char &number, char &shape, int &tNumber, int &tShape)
{
    number = shape = ' ';
    index = tNumber = tShape = 0;

    for(int i = 0; i < inCards.size(); ++i)
    {
        Card init = inCards[i];

        int iqualCount = std::count_if(inCards.begin(), inCards.end(), [init](Card c){ return (init.mNumber == c.mNumber);});

        if(tNumber < iqualCount)
        {
            index = i;
            number = (init.mNumber);
            tNumber = iqualCount;
            break;
        }
//
//        iqualCount = std::count_if(inCards.begin(), inCards.end(), [init](Card c){ return (init.mShape == c.mShape);});
//
//        if(tShape < iqualCount)
//        {
//            shape = init.mShape;
//            tShape = iqualCount;
//        }

    }

    std::cout << index << " " << number << " " << shape << " " << tNumber << " " << tShape << std::endl;
}

bool EscaleraDeColor(Cards inCards)
{
    int compares[5];
    int seed = convertToInt(inCards[0].mNumber);
    std::generate_n(compares, 5, [seed]()mutable{ return ++seed; });

    bool isConsecutive = true;
    for(int i = 0; i < 5; ++i)
    {
        std::cout  << "i: "<< inCards[i].mNumber << " ";
        std::cout << compares[i] << std::endl;

        if(compares[i] != inCards[i].mNumber)
        {
            isConsecutive = false;
            break;
        }
    }

    Card init = inCards[0];
    int iqualCount = std::count_if(inCards.begin(), inCards.end(), [init](Card c){ return (init.mShape == c.mShape);});

    std::cout << iqualCount << std::endl;

    return ( isConsecutive && iqualCount == 5);
}

bool poquer(Cards inCards, int & v)
{
    int maxCount = 0;
    for(int i = 0; i < 5; ++i)
    {
        Card init = inCards[i];
        int iqualCount = std::count_if(inCards.begin(), inCards.end(), [init](Card c){ return (init.mNumber == c.mNumber);});

        if(maxCount < iqualCount)
        {
           maxCount = iqualCount;
           v = convertToInt(init.mNumber);
        }
    }

    return maxCount == 4;
}

bool full(Cards inCards, int & v)
{
    int trioValue = 0;
    int maxCount = 0;
    for(int i = 0; i < 5; ++i)
    {
        Card init = inCards[i];
        int iqualCount = std::count_if(inCards.begin(), inCards.end(), [init](Card c){ return (init.mNumber == c.mNumber);});

        if(maxCount < iqualCount)
        {
            maxCount = iqualCount;
            trioValue = init.mNumber;
            v = trioValue;
        }
    }

    // if it's TRIO
    if(maxCount == 3)
    {
        for(int i = 0; i < 5; ++i)
        {
            Card init = inCards[i];

            if(init.mNumber != trioValue){
                int iqualCount = std::count_if(inCards.begin(), inCards.end(), [init](Card c)
                                           {
                                               return (init.mNumber == c.mNumber);
                                           });
                return (iqualCount == 2);
            }
        }
    }
    else
        return false;
}

struct Player
{
    Player(std::string name, std::string cartas) : mName(name) {
        std::cout << "Cards:" << cartas << std::endl;
        for(int i = 0; i < cartas.size(); i = i + 2)
        {
            Card c(cartas[i], cartas[i + 1]);
            mCards.push_back(c);
        }

        std::sort(mCards.begin(), mCards.end());
    }

    int calculate()
    {
        char number, shape, except;
        int index = 0,tnumber = 0, tshape = 0;


//        if(EscaleraDeColor(mCards))
//        {
//            mPoint = 9;
//            mHighestCard = *(mCards.end() - 1);
//        }

        do
        {
            rank_mano(mCards, index, number, shape, tnumber, tshape);
            mHighestCard.push_back(mCards[index]);
            mCards.erase(mCards.begin(), mCards.begin() + tnumber);

            std::cout << mCards[index].mNumber << std::endl;
        } while (mCards.size() > 0);






    }

    std::string mName;
    std::vector<Card> mCards;
    int mPoint;
    Cards mHighestCard;
};



void startGame(int gameCount, std::string * manos)
{
    for(int i = 0; i < gameCount; ++i)
    {
        Player p1("Black", std::string(manos[i], 0, 10 ) );
        Player p2("White", std::string(manos[i], 10, 10) );

        p1.calculate();

    }


}
