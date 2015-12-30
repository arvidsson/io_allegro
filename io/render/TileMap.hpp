#pragma once

#include "Tile.hpp"
#include "../resource/Image.hpp"
#include <allegro5/allegro.h>
#include <vector>

namespace io
{

class Camera;

class Tilemap
{
public:
    Tilemap(int width, int height, int tileWidth, int tileHeight);
    void LoadTileset(Image tileSheet, Vector<int> offsetCorner = { 0, 0 }, Vector<int> offsetBetween = { 0, 0 });

    Image GetImageById(int id);

    int GetWidth() const { return width; }
    int GetHeight() const { return height; }
    int GetTileWidth() const { return tileWidth; }
    int GetTileHeight() const { return tileHeight; }
    int GetWorldWidth() const { return width * tileWidth; }
    int GetWorldHeight() const { return height * tileHeight; }

    Tile::Ptr GetTile(int x, int y);
    int GetTileX(float x) { return x / tileWidth; }
    int GetTileY(float y) { return y / tileHeight; }

private:
    Image tileSheet;
    std::vector<Image> tileBitmaps;
    int width, height;
    int tileWidth, tileHeight;
    std::vector<Tile::Ptr> tiles;
};

}