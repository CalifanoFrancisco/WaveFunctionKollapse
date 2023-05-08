#ifndef WFC_HPP
#define WFC_HPP

#include <stdexcept>
#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>       // for srand()

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
    unsigned int m_seed;

    template <typename T>
    void setCroto(vector<T> &list, const T& element) {
        for (T i:list)
            if (i == element) return;
        
        list.push_back(element);
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

    // clockwise <@>   UP: 0 | RIGHT: 1 | DOWN: 2 | LEFT: 3
    void calculate(const int index, const int displacement, const int side) {

        const Tile tile_a = m_map[index];
        const Tile tile_b = m_map[displacement];

        vector<t_tile> aux_b_tiles; //turn to hashset

        for (t_tile a: tile_a.m_tilePossibilities) {
            for (t_tile b:tile_b.m_tilePossibilities) {

                const Rule a_rule = m_rules.getByT_tile(a);
                const Rule b_rule = m_rules.getByT_tile(b);

                //if rules check up, keep them in rules list, else, dont load them
                switch (side) {
                case 0:     //UP
                    if (a_rule.UP    == b_rule.DOWN)  setCroto(aux_b_tiles, b);
                    break;
                case 1:     //RIGHT
                    if (a_rule.RIGHT == b_rule.LEFT)  setCroto(aux_b_tiles, b);
                    break;
                case 2:     //DOWN
                    if (a_rule.DOWN  == b_rule.UP)    setCroto(aux_b_tiles, b);
                    break;
                case 3:    //LEFT
                    if (a_rule.LEFT  == b_rule.RIGHT) setCroto(aux_b_tiles, b);
                    break;
                }
            }
        }
        /*
        cout <<"pos: "<<displacement<<" | aux_b_tiles: ";
        for (t_tile i: aux_b_tiles)
            cout << to_string(i) << " ";
        cout << endl;
        */
        m_map[displacement].m_tilePossibilities = aux_b_tiles;
    }
    
    // Spreads tile info throught map
    void propagate() {
        
        for (int i = 0; i < m_map.size(); i++) {                    // iterate through map

            if (m_map[i].entropy() == 12) continue;

            if (int(i - m_size.x) > 0           ) calculate(i, i - m_size.x, 0);     // calculate up    tile if possible
            if (i + 1             < m_map.size()) calculate(i, i + 1,        1);     // calculate right tile if possible
            if (i + m_size.x      < m_map.size()) calculate(i, i + m_size.x, 2);     // calculate down  tile if possible
            if (int(i - 1)        > 0           ) calculate(i, i - 1,        3);     // calculate left  tile if possible
            
        }
    }

    // returns lowest entropy in map
    int findLowestEntropy() {
        
        int pos = -1;                                   // impossible direction
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
        //cout << "lowest entropy: " << to_string(pos) << " " << pos << endl;

        if (pos == -1) return findUncollapsed();        // if lowest entropy position not found, get random position
        return pos;
    }
    
    // returns random m_map position which is not collapsed
    int findUncollapsed() {
        // optimise using list with invalid positions so less cycles are run

        bool loop = true;

        for (int i=0; loop; i++) {
            int n = rand() % m_map.size();  // choose random tile
            if (!observe(n))                // if not collapsed
                return n;                   // return position of not collapsed tile
            
            if (i > 200000) {
                loop = false;
                throw std::invalid_argument("Eternal loop in int WFC::findUncollaped()");
            }
        }
        return -1;
    }

public:
    WFC(const unsigned int x, const unsigned int y, const unsigned int seed) {
        this->m_size = Vector2u(x, y);
        this->m_seed = seed;
        this->m_map.resize(x * y);
        srand(m_seed);

        for (int i = 0; i < m_map.size(); i++)
            this->m_map[i] = Tile(seed);

    }
    WFC(const unsigned int x, const unsigned int y) {
        this->m_size = Vector2u(x, y);
        this->m_map.resize(x * y);
        this->m_seed = time(NULL);
        srand(m_seed);

        for (int i = 0; i < m_map.size(); i++)
            this->m_map[i] = Tile(m_seed);            
    }

    // run Wave Function Collapse algorythm
    void run(const bool render) {

        // collapse random tile to init chain collapses
        //m_map[rand() % m_map.size()].collapse();
        m_map[0].collapse();
        //m_map[(m_size.y * m_size.x) - 1].collapse();

        // iteration percentage
        int percentage = 0, temp;

        // while map isnt fully collapsed
        for (int i = 0; !hasEntirelyCollapsed(); i++) {
            
            //render WFC progress
            //cout << "--("<<(i * 100) / m_map.size() << "%)-<" << i << ">----" << "\n";
            if (render) draw();

            // propagate info from collapsed tiles
            propagate();

            //collapse tile with lowest entropy
            m_map[findLowestEntropy()].collapse();
        }
        cout << "-----------------------------------------------------------------------" << endl;
        cout << "Final: " << endl;
        draw();
        cout << "Seed: " << m_seed << endl;
    }

    void draw() {
        for (int y = 0; y < m_size.y; y++) {
            for(int x = 0; x < m_size.x; x++) {
                std::cout << to_string(m_map[y * m_size.x + x].ref);
                //cout << m_map[y * m_size.x + x].entropy() << " ";
            }
            std::cout << std::endl;
        }
    }

    void fexport(const std::string& filename) {
        std::ofstream file(filename);
        for (int y = 0; y < m_size.y; y++)  {
            for (int x = 0; x < m_size.x; x++) {
                file << to_string(m_map[y * m_size.x + x].ref);
            }
            file << std::endl;
        }

    }
};

#endif 