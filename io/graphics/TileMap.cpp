#include "Tilemap.hpp"
#include "../Debug.hpp"
#include "Camera2D.hpp"
using namespace alcpp;

namespace io
{

Tilemap::Tilemap(int width, int height, int tileWidth, int tileHeight, Bitmap tilesheet, alcpp::Vec2<int> offset, alcpp::Vec2<int> padding) : width(width), height(height), tileWidth(tileWidth), tileHeight(tileHeight), tilesheet(tilesheet)
{
    // populate tiles with zero ids
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            tiles.push_back(Tile());
        }
    }

    if (tilesheet) {
        SetTileset(tilesheet, offset);
    }
}

void Tilemap::SetTileset(alcpp::Bitmap tilesheet, alcpp::Vec2<int> offset, alcpp::Vec2<int> padding)
{
    this->tilesheet = tilesheet;
    this->offset = offset;
    this->padding = padding;

    int tileX = tilesheet.GetWidth() / tileWidth;
    int tileY = tilesheet.GetHeight() / tileHeight;

    // cut up the tilesheet
    for (int j = 0; j < tileY; j++) {
        for (int i = 0; i < tileX; i++) {
            int x = i * tileWidth + (i ? padding.x : offset.x);
            int y = j * tileHeight + (j ? padding.y : offset.y);
            Bitmap bmp(tilesheet, x, y, tileWidth, tileHeight);
            tileset.push_back(bmp);
        }
    }
}

Tile& Tilemap::GetTile(int x, int y)
{
    Assert(x >= 0 && x < width);
    Assert(y >= 0 && y < height);
    return tiles[x + width * y];
}

void Tilemap::Render(Display &display, const Vec2<int> &topLeft, const Vec2<int> &bottomRight)
{
    display.HoldDrawing();
    for (int y = topLeft.y; y < bottomRight.y; y++) {
        for (int x = topLeft.x; x < bottomRight.x; x++) {
            float w = GetTileWidth();
            float h = GetTileHeight();
            auto tile = GetTile(x, y);
            display.Draw(GetTilesetBitmapById(tile.GetID()), x * w, y * h);
        }
    }
    display.ReleaseDrawing();
}

void Tilemap::Render(Display &display, const Camera2D &camera)
{
    auto cameraSize = camera.ToWorld(display.GetWidth(), display.GetHeight());
    auto cameraPos = Vec2<float>(camera.GetX() - cameraSize.x / 2, camera.GetY() - cameraSize.y / 2);

    // figure out what tiles to draw depending on camera movement, so we don't waste time trying to draw every tile, visible or not
    Vec2<int> topLeft = { (int)cameraPos.x / GetTileWidth(), (int)cameraPos.y / GetTileHeight() };
    if (topLeft.x < 0) topLeft.x = 0;
    if (topLeft.y < 0) topLeft.y = 0;
    Vec2<int> bottomRight = { (int)(cameraSize.x) / GetTileWidth() + 1, (int)(cameraSize.y) / GetTileHeight() + 1 };
    if (bottomRight.x > GetWidth()) bottomRight.x = GetWidth();
    if (bottomRight.y > GetHeight()) bottomRight.y = GetHeight();

    Render(display, topLeft, bottomRight);
}

Bitmap Tilemap::GetTilesetBitmapById(int id) const
{
    Assert(id >= 0 && id < (int)tileset.size());
    return tileset[id];
}

}