#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <vector>

#include "Vector2u.hpp"
#include "t_tile.hpp"
#include "Tile.hpp"

using std::cout;
using std::vector;

class Map {
private:
    Vector2u m_size;

    void init() {
        for (int i = 0; i < m_map.size(); i++) 
            m_map[i].ref = t_tile::NONE;
    }

public:
    vector<Tile> m_map;

    Map():
        m_size(0, 0), m_map(0)
    {}
    
    Map(Vector2u _size):
        m_size(_size), m_map(_size.x * _size.y)
    {}
    
    Map(unsigned int x, unsigned int y):
        m_size(Vector2u(x, y)), m_map(x * y)
    {
        init();
    }

    void draw() {
        for (int y = 0; y < m_size.y; y++) {
            for (int x = 0; x < m_size.x; x++) {
                std::cout << to_string(m_map[x + y * m_size.x].ref);
            }
            std::cout << std::endl;
        }
    }

    const Vector2u& size() {
        return m_size;
    }
};

#endif