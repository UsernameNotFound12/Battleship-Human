//
// Created by Nishanth on 5/15/2026.
//


#include "Board.h"
#include <iostream>

namespace BattleShip {

Board::Board(int rows, int cols) : rows(rows), cols(cols),
      placementGrid(rows, std::vector<char>(cols, '*')),
      firingGrid(rows, std::vector<char>(cols, '*')) {}

int Board::getRows() const { return rows; }
int Board::getCols() const { return cols; }

bool Board::isInBounds(int row, int col) const {
    return row >= 0 && row < rows && col >= 0 && col < cols;
}

bool Board::placeShip(Ship& ship, int row, int col, bool horizontal) {
    std::vector<std::pair<int,int>> coords;
    for (int i = 0; i < ship.getSize(); i++) {
        int r = horizontal ? row : row + i;
        int c = horizontal ? col + i : col;
        if (!isInBounds(r, c)) return false;
        if (placementGrid[r][c] != '*') return false;
        coords.push_back({r, c});
    }
    for (auto& [r, c] : coords) {
        placementGrid[r][c] = ship.getSymbol();
    }
    ship.setCoordinates(coords);
    ships.push_back(&ship);
    return true;
}

ShotResult Board::receiveShot(int row, int col, Ship*& shipHit) {
    if (!isInBounds(row, col)) return ShotResult::INVALID;

    char cell = placementGrid[row][col];
    if (cell == 'X' || cell == '~') return ShotResult::ALREADY_SHOT;

    if (cell == '*') {
        placementGrid[row][col] = '~';
        shipHit = nullptr;
        return ShotResult::MISS;
    }

    placementGrid[row][col] = 'X';
    for (Ship* s : ships) {
        for (auto& [r, c] : s->getCoordinates()) {
            if (r == row && c == col) {
                s->hit();
                shipHit = s;
                return ShotResult::HIT;
            }
        }
    }
    shipHit = nullptr;
    return ShotResult::HIT;
}

void Board::markFiringBoard(int row, int col, bool hit) {
    firingGrid[row][col] = hit ? 'X' : 'O';
}

bool Board::allShipsSunk() const {
    for (Ship* s : ships) {
        if (!s->isSunk()) return false;
    }
    return true;
}

void Board::printGrid(const std::vector<std::vector<char>>& grid) const {
    std::cout << " ";
    for (int c = 0; c < cols; c++) std::cout << " " << c;
    std::cout << "\n";
    for (int r = 0; r < rows; r++) {
        std::cout << r;
        for (int c = 0; c < cols; c++) std::cout << " " << grid[r][c];
        std::cout << "\n";
    }
}

void Board::displayPlacementBoard() const {
    std::vector<std::vector<char>> display = placementGrid;
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++)
            if (display[r][c] == '~') display[r][c] = '*';
    printGrid(display);
}

void Board::displayFiringBoard() const {
    printGrid(firingGrid);
}

}