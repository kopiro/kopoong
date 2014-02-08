#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <string>
#include <QObject>

class player : public QObject {
    Q_OBJECT
private:
    int points;
    std::string name;
    std::vector<int> ID;
public:
    player();
    int getPoints();
    void addPoint(int p = 1);
    std::string getName();
    void setName(std::string name);
    int getIDat(int i);
    void addID(int id);
signals:
    void pointsChanged();
};

#endif // PLAYER_H
