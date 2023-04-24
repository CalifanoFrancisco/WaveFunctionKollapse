#include <iostream>
#include <vector>

#include "Tile.hpp"
#include "Map.hpp"
#include "WFC.hpp"


using std::cout;
using std::string;
using std::endl;

int main() {
    Map map(80, 10);
    for (int y = 0; y < map.size().y; y++) {
        for (int x = 0; x < map.size().x; x++) {
            map.m_map[y * map.size().x + x].collapse();
        }
    }
    map.draw();

    WFC wfc(4, 4);
    wfc.run();


    //cout << "Exit success" << endl;
    return 0;
}