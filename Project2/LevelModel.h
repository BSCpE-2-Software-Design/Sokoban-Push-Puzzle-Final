#ifndef LEVELMODEL_H
#define LEVELMODEL_H

#include <vector>

class LevelModel {
private:
    std::vector<int> grid;
    int width;
    int height;

public:
    
    LevelModel(int w, int h);
    LevelModel();

    int getTile(int x, int y) const;
    void setTile(int x, int y, int value);

    int getWidth() const;
    int getHeight() const;
};

#endif