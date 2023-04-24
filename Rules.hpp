#ifndef RULES_H
#define RULES_H

#include <iostream>
#include "t_tile.hpp"

#define DEBUG 1
#if DEBUG
    #define println(x) std::cout << x << std::endl
#else
    #define println(x)
#endif

class Rule {
public:
    t_tile tileType;
    bool UP, DOWN, LEFT, RIGHT;
    Rule(t_tile _t, bool up = 0, bool down = 0, bool left = 0, bool right = 0):
        tileType(_t), UP(up), DOWN(down), LEFT(left), RIGHT(right)
    { }
};

class Rules {
private:
    const Rule rules[12] = {
        Rule(t_tile::DOWN_RIGHT,      0, 1, 0, 1),
        Rule(t_tile::DOWN_UP,         1, 1, 0, 0),
        Rule(t_tile::DOWN_LEFT,       0, 1, 1, 0),
        Rule(t_tile::LEFT_RIGHT,      0, 0, 1, 1),
        Rule(t_tile::UP_RIGHT,        1, 0, 0, 1),
        Rule(t_tile::UP_LEFT,         1, 0, 1, 0),
        Rule(t_tile::LEFT_UP_DOWN,    1, 1, 1, 0),
        Rule(t_tile::RIGHT_UP_DOWN,   1, 1, 0, 1),
        Rule(t_tile::UP_LEFT_RIGHT,   1, 0, 1, 1),
        Rule(t_tile::DOWN_LEFT_RIGHT, 0, 1, 1, 1),
        Rule(t_tile::ALL,             1, 1, 1, 1),
        Rule(t_tile::NONE,            0, 0, 0, 0)
    };
    const int m_size = 12;

public:
    int size() { return m_size; }
    const Rule& operator[](int index) {
        return rules[index];
    }
};

std::ostream &operator<<(std::ostream &os, Rule const& rule) {
    os << to_string(rule.tileType) << " |";
    os << " UP: "    << rule.UP;
    os << " DOWN: "  << rule.DOWN;
    os << " LEFT: "  << rule.LEFT;
    os << " RIGHT: " << rule.RIGHT;
    //os << "\n";
    return os;
}


#endif