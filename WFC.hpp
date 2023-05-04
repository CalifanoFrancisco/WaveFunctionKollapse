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

using std::cout;
using std::endl;

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

    // if tile is collapsed returns true
    bool observe(int pos) {
        return m_map[pos].entropy() == COLLAPSED_TILE_SIZE;
    }

    // checks if map is collapsed
    bool hasEntirelyCollapsed() {
        for (int i = 0; i < m_map.size(); i++) {
            if (!observe(i)) return false;
        }
        return true;
    }

    // clockwise <{@}>   UP: 0 | RIGHT: 1 | DOWN: 2 | LEFT: 3
    void calculate(const int index, const int displacement, const int side) {

        const Tile tile_a = m_map[index];
        const Tile tile_b = m_map[displacement];

        vector<t_tile> aux_b_tiles;

        //if its already collapsed
        //if (tile_a.m_tilePossibilities.size() == 0) a = tile_a.ref;

        for (t_tile a: tile_a.m_tilePossibilities) {
            for (t_tile b:tile_b.m_tilePossibilities) {

                const Rule a_rule = m_rules.getByT_tile(a);
                const Rule b_rule = m_rules.getByT_tile(b);

                //if rules check up, keep them in rules list, else, dont load them
                switch (side) {
                case 0:     //UP
                    if (a_rule.UP    == b_rule.DOWN)  aux_b_tiles.push_back(b);
                    break;
                case 1:     //RIGHT
                    if (a_rule.RIGHT == b_rule.LEFT)  aux_b_tiles.push_back(b);
                    break;
                case 2:     //DOWN
                    if (a_rule.DOWN  == b_rule.UP)    aux_b_tiles.push_back(b);
                    break;
                case 3:    //LEFT
                    if (a_rule.LEFT  == b_rule.RIGHT) aux_b_tiles.push_back(b);
                    break;
                }
            }
        }
        //for (t_tile i: aux_b_tiles) cout << to_string(i) << " "; cout << endl;

        m_map[displacement].m_tilePossibilities = aux_b_tiles;

    }
    
    // Spreads tile info throught map
    void propagate() {
        
        for (int i = 0; i < m_map.size(); i++) {                    // iterate through map

            //if (i < 10) std::cout << " " << i; else std::cout << i;
            //std::cout << " | " << m_map[i] << " -> ";

            //if (i - m_size.x > 0           ) calculate(i, i - m_size.x, 0);     // calculate up    tile if possible
            //if (i + 1        < m_map.size()) calculate(i, i + 1,        1);     // calculate right tile if possible
            if (i + m_size.x < m_map.size()) calculate(i, i + m_size.x, 2);     // calculate down  tile if possible
            //if (i - 1        > 0           ) calculate(i, i - 1,        3);     // calculate left  tile if possible
            
            //std::cout << " " << m_map[i] << "\n";

        }
    }

    // returns lowest entropy in map
    int findLowestEntropy() {
        int pos = 0; 
        int lowest_entropy = 12;                        // set to max entropy value (12)
        for (int i = 0; i < m_map.size(); i++) {        // iterate through map
            if (
                m_map[i].entropy() < lowest_entropy &&  // checks tile A has lower entropy than tile B
                !observe(i)                             // checks tile isnt already collapsed
            ) {
                pos = i;
                lowest_entropy = m_map[i].entropy();
            }
        }
        return pos;
    }
    
    // returns random m_map position which is not collapsed
    int findUncollapsed() {
        while (true) {
            int n = rand() % m_map.size();
            if (m_map[n].entropy() != 0) 
                return n;
        }
    }
    
    // run Wave Function Collapse algorythm
    void run() {
        // collapse random tile to init chain collapses
        int n = rand() % m_map.size();
        n = 0;
        m_map[n].collapse();

        // while map isnt fully collapsed
        while (!hasEntirelyCollapsed()) {
            
            //render WFC progress

            // propagate info from collapsed tiles
            propagate();

            //collapse tile with lowest entropy
            m_map[findUncollapsed()].collapse();
        }
        draw();
    }

    void draw() {
        for (int y = 0; y < m_size.y; y++) {
            for(int x = 0; x < m_size.x; x++) {
                std::cout << to_string(m_map[y * m_size.x + x].ref);
            }
            std::cout << std::endl;
        }
    }
};

#endif 