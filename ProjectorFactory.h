// ProjectorFactory.h
#pragma once
#include "Projector.h"
#include <memory>

using namespace std;

// Абстрактная фабрика проекторов
class ProjectorFactory {
public:
    virtual ~ProjectorFactory() = default;
    virtual unique_ptr<Projector> createProjector(const string& id) = 0;
};

// Фабрика для обычных проекторов
class StandardHallFactory : public ProjectorFactory {
public:
    unique_ptr<Projector> createProjector(const string& id) override {
        return make_unique<Projector>(id);
    }
};

// Фабрика для VIP залов (3D проекторы)
class VipHallFactory : public ProjectorFactory {
public:
    unique_ptr<Projector> createProjector(const string& id) override {
        return make_unique<ThreeDProjector>(id);
    }
};

// Фабрика для IMAX залов
class ImaxHallFactory : public ProjectorFactory {
public:
    unique_ptr<Projector> createProjector(const string& id) override {
        return make_unique<ImaxProjector>(id);
    }
};