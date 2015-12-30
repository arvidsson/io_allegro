#pragma once

namespace io
{

template <class T>
class Value
{
public:
    const T& Get() const { return value; }
    T& Get() { return value; }

protected:
    Value() = default;
    Value(const T &value) = default;

private:
    T value;
};

}