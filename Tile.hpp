#ifndef TILE_HPP
#define TILE_HPP

#include <iostream>
#include <vector>

#include "t_tile.hpp"
#include <time.h>

#define COLLAPSED_TILE_SIZE 1

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

    Tile(vector<t_tile> tilePos):
        ref(t_tile::NONE), m_tilePossibilities(tilePos)
    { }

    int entropy() {
        return this->m_tilePossibilities.size();
    }

    void collapse() {
        int num   = rand() % m_tilePossibilities.size();
        this->ref = m_tilePossibilities[num];
        m_tilePossibilities.clear();                        // thus entropy = 0
        m_tilePossibilities.push_back(ref);                 // entropy = 1 when collapsed
    }

    Tile& operator=(const Tile& tile) {
        if (this != &tile) {
            ref = tile.ref;
            m_tilePossibilities = tile.m_tilePossibilities;
        }
        return *this;
    }

};

std::ostream &operator<<(std::ostream &os, const Tile& tile) {    
    os << "Possibilities: ";
    if (tile.m_tilePossibilities.size() == COLLAPSED_TILE_SIZE) 
        return os << to_string(tile.ref);

    for (int i = 0; i < tile.m_tilePossibilities.size(); i++) 
        os << to_string(tile.m_tilePossibilities[i]) << " ";
    return os;
}


#endif