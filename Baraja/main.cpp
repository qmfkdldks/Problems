#include <iostream>

#define NCARDS 52
#define NSUITS 4

char values[] = "23456789JQKA";
char suits[] = "cdhs";

using namespace std;


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

int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
