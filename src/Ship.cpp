//
// Created by Nishanth on 5/16/2026.
//

#include "Ship.h"

namespace BattleShip {

    Ship::Ship(char symbol, int size)
        : symbol(symbol), size(size), hits(0) {}

    char Ship::getSymbol() const { return symbol; }
    int Ship::getSize() const { return size; }
    bool Ship::isSunk() const { return hits >= size; }
    void Ship::hit() { hits++; }

    void Ship::setCoordinates(const std::vector<std::pair<int,int>>& coords) {
        coordinates = coords;
    }

    const std::vector<std::pair<int,int>>& Ship::getCoordinates() const {
        return coordinates;
    }

}