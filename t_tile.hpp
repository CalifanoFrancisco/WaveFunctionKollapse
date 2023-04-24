#ifndef T_TILE_HPP
#define T_TILE_HPP

enum t_tile {
    DOWN_RIGHT      = 0,
    DOWN_UP         = 1,
    DOWN_LEFT       = 2,
    LEFT_RIGHT      = 3,
    UP_RIGHT        = 4,
    UP_LEFT         = 5,
    LEFT_UP_DOWN    = 6,
    RIGHT_UP_DOWN   = 7,
    UP_LEFT_RIGHT   = 8,
    DOWN_LEFT_RIGHT = 9,
    ALL             = 10,
    NONE            = 11
};
/*
const std::string to_string(t_tile tile) {
    switch (tile) {
        case DOWN_RIGHT:        return "┏"; break;
        case DOWN_UP:           return "┃"; break;
        case DOWN_LEFT:         return "┓"; break;
        case LEFT_RIGHT:        return "━"; break;
        case UP_RIGHT:          return "┗"; break;
        case UP_LEFT:           return "┛"; break;
        case LEFT_UP_DOWN:      return "┫"; break;
        case RIGHT_UP_DOWN:     return "┣"; break;
        case UP_LEFT_RIGHT:     return "┻"; break;
        case DOWN_LEFT_RIGHT:   return "┳"; break;
        case ALL:               return "╋"; break;
        case NONE:              return "."; break;
        default:                return " "; break;
    }
}
*/
const std::string to_string(int n_tile) {
    switch (n_tile) {
        case 0:  return "┏"; break;
        case 1:  return "┃"; break;
        case 2:  return "┓"; break;
        case 3:  return "━"; break;
        case 4:  return "┗"; break;
        case 5:  return "┛"; break;
        case 6:  return "┫"; break;
        case 7:  return "┣"; break;
        case 8:  return "┻"; break;
        case 9:  return "┳"; break;
        case 10: return "╋"; break;
        case 11: return "."; break;
        default: return " "; break;
    }
}


#endif