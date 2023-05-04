#include <iostream>
#include <vector>

#include "Tile.hpp"
#include "Map.hpp"
#include "WFC.hpp"

using std::cout;
using std::string;
using std::endl;

using std::vector;

void collapseAtRandom(Map &map) {
    for (int y = 0; y < map.size().y; y++) {
        for (int x = 0; x < map.size().x; x++) {
            map.m_map[y * map.size().x + x].collapse();
        }
    }
}

template <typename T> 
std::ostream &operator<<(std::ostream &os, vector<T> const& list) {
    for (T i:list) {
        os << i << " ";
    }
    return os;
}

int main() {

    WFC wfc(1, 2);
    wfc.run();

    //cout << "Exit success" << endl;
    return 0;
}


