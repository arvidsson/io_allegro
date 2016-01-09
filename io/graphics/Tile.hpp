#pragma once

#include <memory>

namespace io
{

class Tile : public std::shared_ptr<Tile>
{
public:
    Tile(int id = 0) : id(id) {}

    int GetID() const { return id; }
    void SetID(int newId) { id = newId; }

private:
    int id;
};

}