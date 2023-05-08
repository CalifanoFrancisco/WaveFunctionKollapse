#include <iostream>
#include <vector>

#include "Tile.hpp"
#include "Map.hpp"
#include "WFC.hpp"

using std::cout;
using std::endl;
using std::ostream;
using std::string;
using std::vector;

void collapseAtRandom(Map &map)
{
    for (int y = 0; y < map.size().y; y++)
    {
        for (int x = 0; x < map.size().x; x++)
        {
            map.m_map[y * map.size().x + x].collapse();
        }
    }
}

template <typename T>
ostream &operator<<(ostream &os, const vector<T> &list)
{
    for (T i : list)
    {
        os << i << " ";
    }
    return os;
}

int main()
{
    // 80*30 = 180s
    // 20*20 = 5s
    WFC wfc(60, 5);
    wfc.run(true);
    // wfc.fexport("wesexing.txt");

    // cout << "Exit success" << endl;
    return 0;
}
/*
size (60 * 5)
error seeds:
1683577162

*/