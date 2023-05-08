#ifndef TILE_HPP
#define TILE_HPP

#include <iostream>
#include <vector>
#include <time.h>

#include "t_tile.hpp"

#define COLLAPSED_TILE_SIZE 1

using std::ostream;
using std::vector;
using std::cout;
using std::endl;  

class Tile {
public:
    t_tile ref;
    vector<t_tile> m_tilePossibilities;

    Tile():
        ref(t_tile::NONE)
    {
        for (int i = 0; i < t_tile::TILE_MAX_SIZE; i++) 
            m_tilePossibilities.push_back(static_cast<t_tile>(i));
        
        srand(time(NULL));
    }

    Tile(unsigned int seed):
        ref(t_tile::NONE)
    { 
        for (int i = 0; i < t_tile::TILE_MAX_SIZE; i++) 
            m_tilePossibilities.push_back(static_cast<t_tile>(i));
            
        srand(seed);
    }

    int entropy() {
        return this->m_tilePossibilities.size();
    }

    void collapse() {
        int num   = rand() % m_tilePossibilities.size();
        this->ref = m_tilePossibilities[num];
        m_tilePossibilities.clear();                        // set entropy = 0
        m_tilePossibilities.push_back(this->ref);           // entropy = 1 when collapsed
    }

    Tile& operator=(const Tile& tile) {
        if (this != &tile) {
            ref = tile.ref;
            m_tilePossibilities = tile.m_tilePossibilities;
        }
        return *this;
    }

};

inline ostream &operator<<(std::ostream &os, const Tile& tile) {    
    os << "Possibilities: ";
    if (tile.m_tilePossibilities.size() == COLLAPSED_TILE_SIZE) 
        return os << to_string(tile.ref);

    for (int i = 0; i < tile.m_tilePossibilities.size(); i++) 
        os << to_string(tile.m_tilePossibilities[i]) << " ";
    return os;
}


#endif