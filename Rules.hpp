#ifndef RULES_H
#define RULES_H

#include <stdexcept>
#include <iostream>

#include "t_tile.hpp"

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
    const Rule m_rules[12] = {
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
    const int size() { return m_size; }
    const Rule& operator[](int index) {
        return m_rules[index];
    }

    Rule getByT_tile(const t_tile x) {
        for (Rule i: m_rules) {
            if (i.tileType == x) return i;
        }
        throw std::invalid_argument("Element with no Rule::Rule() defined or not loaded into Rules::m_rules");
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