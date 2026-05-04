#include "LevelModel.h"

LevelModel::LevelModel(int w, int h) : width(w), height(h) {
    grid.resize(w * h, 0);
}

LevelModel::LevelModel() : width(0), height(0) {}

int LevelModel::getTile(int x, int y) const {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        return grid[y * width + x];
    }
    return 1;
}

void LevelModel::setTile(int x, int y, int value) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        grid[y * width + x] = value;
    }
}

int LevelModel::getWidth() const { return width; }
int LevelModel::getHeight() const { return height; }