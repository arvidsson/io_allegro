#include "Tilemap.hpp"
#include "../Debug.hpp"
#include "Camera2D.hpp"

namespace io
{

Tilemap::Tilemap(int width, int height, int tileWidth, int tileHeight) : width(width), height(height), tileWidth(tileWidth), tileHeight(tileHeight)
{
    // populate tiles with zero ids
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            tiles.push_back(std::make_shared<Tile>());
        }
    }
}

void Tilemap::LoadTileset(Image tileSheet, Vector<int> offsetCorner, Vector<int> offsetBetween)
{
    this->tileSheet = tileSheet;
    int tileX = tileSheet.GetWidth() / tileWidth;
    int tileY = tileSheet.GetHeight() / tileHeight;

    // cut up the tilesheet
    for (int j = 0; j < tileY; j++) {
        for (int i = 0; i < tileX; i++) {
            int x = i * tileWidth + (i ? offsetBetween.x : offsetCorner.x);
            int y = j * tileHeight + (j ? offsetBetween.y : offsetCorner.y);
            Image bmp(tileSheet, x, y, tileWidth, tileHeight);
            tileBitmaps.push_back(bmp);
        }
    }
}

Image Tilemap::GetImageById(int id)
{
    Assert(id >= 0 && id < (int)tileBitmaps.size());
    return tileBitmaps[id];
}

Tile::Ptr Tilemap::GetTile(int x, int y)
{
    Assert(x >= 0 && x < width);
    Assert(y >= 0 && y < height);
    return tiles[x + width * y];
}

}