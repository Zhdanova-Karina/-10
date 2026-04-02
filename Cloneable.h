// Cloneable.h
#pragma once
#include <string>
#include <iostream>

using namespace std;

// Глубина клонирования
enum class CloneDepth {
    SHALLOW,    // Поверхностное (копируются только указатели)
    DEEP,       // Глубокое (копируются все данные)
    CUSTOM      // Пользовательское
};

class Cloneable {
public:
    virtual ~Cloneable() = default;
    virtual void* clone(CloneDepth depth = CloneDepth::DEEP) const = 0;
};