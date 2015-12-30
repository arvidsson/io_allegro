#pragma once

#include <memory>

namespace io
{

class Screen
{
public:
    using Ptr = std::shared_ptr<Screen>;

    virtual ~Screen() {}

    virtual void Update() = 0;
    virtual void Render() = 0;

    virtual void Initialize() {}
    virtual void Terminate() {}
};

}