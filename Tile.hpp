#ifndef TILE_HPP
#define TILE_HPP

#include <iostream>
#include <vector>

#include "t_tile.hpp"
#include <time.h>

using std::vector;

class Tile {
private:

public:
    t_tile ref;
    vector<t_tile> m_tilePossibilities;

    Tile():
        ref(t_tile::NONE)
    {
        m_tilePossibilities = {
            t_tile::ALL,
            t_tile::DOWN_LEFT,
            t_tile::DOWN_LEFT_RIGHT,
            t_tile::DOWN_RIGHT,
            t_tile::DOWN_UP,
            t_tile::LEFT_RIGHT,
            t_tile::LEFT_UP_DOWN,
            t_tile::NONE,
            t_tile::RIGHT_UP_DOWN,
            t_tile::UP_LEFT,
            t_tile::UP_LEFT_RIGHT,
            t_tile::UP_RIGHT
        };
        srand(time(NULL));
    }

    int entropy() {
        return m_tilePossibilities.size();
    }

    void collapse() {
        int num   = rand() % m_tilePossibilities.size();
        this->ref = m_tilePossibilities[num];
        m_tilePossibilities.clear();
    }

};

std::ostream &operator<<(std::ostream &os, Tile const& tile) {
    //os << "> Pos X:" << tile.x << " Y:" << tile.y << " | ";
    os << "Possibilities: ";
    for (int i = 0; i < t_tile::NONE + 1; i++) 
        os << to_string(i) << " ";
    return os;
}


#endif