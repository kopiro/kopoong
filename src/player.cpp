#include "player.h"

player::player() : QObject() {
    this->points=0;
    this->name="UNDEF";
}

void player::addID(int id) {
    this->ID.push_back(id);
}

int player::getIDat(int i) {
    if (i<0 && i>=this->ID.size()) return NULL;
    return this->ID[i];
}

void player::addPoint(int p) {
    points += p;
    emit pointsChanged();
}

int player::getPoints() {
    return points;
}

std::string player::getName() {
    return name;
}

void player::setName(std::string name) {
    this->name = name;
}
