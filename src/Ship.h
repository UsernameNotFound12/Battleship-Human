//
// Created by Nishanth on 5/16/2026.
//

#ifndef ECS36BBATTLESHIPHUMANSONLY_SHIP_H
#define ECS36BBATTLESHIPHUMANSONLY_SHIP_H

#include <vector>
#include <utility>

namespace BattleShip {

    class Ship {
    public:
        Ship(char symbol, int size);

        char getSymbol() const;
        int getSize() const;
        bool isSunk() const;
        void hit();

        void setCoordinates(const std::vector<std::pair<int,int>>& coords);
        const std::vector<std::pair<int,int>>& getCoordinates() const;

    private:
        char symbol;
        int size;
        int hits;
        std::vector<std::pair<int,int>> coordinates;
    };

}


#endif //ECS36BBATTLESHIPHUMANSONLY_SHIP_H
