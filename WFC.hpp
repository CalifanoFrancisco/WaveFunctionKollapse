#ifndef WFC_HPP
#define WFC_HPP

#include <iostream>
#include <cstdlib>
#include <vector>
#include <time.h>

#include "Vector2u.hpp"
#include "Rules.hpp"
#include "Tile.hpp"
#include "Map.hpp"

using std::vector;

class WFC {
private:
    vector<Tile> m_map;
    Vector2u     m_size;
    Rules        m_rules;

public:
    WFC(const unsigned int x, const unsigned int y) {
        m_map.resize(x * y);
        m_size = Vector2u(x, y);
        srand(time(NULL));
    }

    bool observe(int pos) {
        return m_map[pos].entropy() == 0;
    }
    
    void calculateUP   (const int index) {
        vector<t_tile> tilePoss_a = m_map[index           ].m_tilePossibilities;
        vector<t_tile> tilePoss_b = m_map[index + m_size.x].m_tilePossibilities;

        for (t_tile i:tilePoss_a) {
            for (t_tile e:tilePoss_b) {
                
            }
        }

    }


    void calculateDOWN (int index) {}
    void calculateLEFT (int index) {}
    void calculateRIGHT(int index) {}
    
    void propagate() {

        for (int i = 0; i < m_map.size(); i++) {

            if (i + m_size.x < m_map.size()) calculateUP   (i);
            if (i - m_size.x > m_map.size()) calculateDOWN (i);
            if (i + 1        < m_map.size()) calculateRIGHT(i);
            if (i - 1        > 0           ) calculateLEFT (i);

        }
    }

    int findLowestEntropy() {
        int pos = 0; 
        for (int i = 0; i < m_map.size(); i++) {
            int lowest_entropy = 12;
            if (
                m_map[i].entropy() <  lowest_entropy &&  // checks tile A has lower entropy than B
                !observe(i)                              // checks tile isnt already collapsed
            ) {
                pos = i;
                lowest_entropy = m_map[i].entropy();
            }
        }
        return pos;
    }

    void run() {
        // collapse random tile to init chain collapses
        m_map[rand() % m_map.size() + 0].collapse();

        while (true) {
            propagate();
            //collapse tile with lowest entropy
            m_map[findLowestEntropy()].collapse();
            break; //para chequear que no hay errores
        }
    }
};

#endif 