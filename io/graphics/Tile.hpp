#pragma once

namespace io
{

class Tile
{
public:
    Tile(int id = 0, bool solid = false) : id(id), solid(solid) {}

    int GetID() const { return id; }
    void SetID(int newId) { id = newId; }
    
    void SetSolid(bool solid) { this->solid = solid; }
    bool IsSolid() const { return solid; }

private:
    int id;
    bool solid;
};

}