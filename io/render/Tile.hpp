#pragma once

#include <memory>

namespace io
{

class Tile
{
public:
    Tile(int id = 0) : id(id) {}

    int GetID() const { return id; }
    void SetID(int newId) { id = newId; }

    using Ptr = std::shared_ptr<Tile>;

private:
    int id;
};

}