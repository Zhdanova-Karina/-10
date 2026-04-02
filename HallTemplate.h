// HallTemplate.h
#pragma once
#include "Hall.h"
#include "Session.h"
#include "Cloneable.h"
#include <memory>
#include <vector>

using namespace std;

// === НАСТРОЙКИ: Шаблоны залов ===
struct HallTemplateData {
    string name;
    int capacity;
    string equipmentType;
    int cleanupTimeMinutes;
};

vector<HallTemplateData> hallTemplates = {
    {"StandardHall", 150, "Standard", 15},
    {"VipHall", 50, "VIP", 25},
    {"ImaxHall", 300, "IMAX", 30}
};

class HallTemplate : public Cloneable {
private:
    int number;
    int capacity;
    string hallType;
    int cleanupTimeMinutes;
    vector<Session> defaultSchedule;

public:
    HallTemplate(int num, const HallTemplateData& data)
        : number(num), capacity(data.capacity), hallType(data.equipmentType),
        cleanupTimeMinutes(data.cleanupTimeMinutes) {}

    // Конструктор копирования (глубокое копирование)
    HallTemplate(const HallTemplate& other)
        : number(other.number), capacity(other.capacity),
        hallType(other.hallType), cleanupTimeMinutes(other.cleanupTimeMinutes) {
        // Глубокое копирование вектора сеансов
        for (const auto& session : other.defaultSchedule) {
            defaultSchedule.push_back(session);
        }
    }

    // Поверхностное копирование
    HallTemplate shallowCopy() const {
        HallTemplate copy(number, hallTemplates[0]);
        copy.number = number;
        copy.capacity = capacity;
        copy.hallType = hallType;
        copy.cleanupTimeMinutes = cleanupTimeMinutes;
        // defaultSchedule НЕ копируется
        return copy;
    }

    static HallTemplate* createFromTemplate(const string& templateName, int hallNumber) {
        for (const auto& tmpl : hallTemplates) {
            if (tmpl.name == templateName) {
                return new HallTemplate(hallNumber, tmpl);
            }
        }
        return new HallTemplate(hallNumber, hallTemplates[0]);
    }

    // Клонирование с выбором глубины
    void* clone(CloneDepth depth = CloneDepth::DEEP) const override {
        switch (depth) {
        case CloneDepth::SHALLOW:
            cout << "  [HallTemplate] Поверхностное копирование (сеансы НЕ скопированы)" << endl;
            return new HallTemplate(*this); // shallow copy

        case CloneDepth::DEEP:
            cout << "  [HallTemplate] Глубокое копирование (сеансы скопированы)" << endl;
            return new HallTemplate(*this); // deep copy (конструктор копирования)

        case CloneDepth::CUSTOM:
            cout << "  [HallTemplate] Пользовательское копирование (копируем только первые 2 сеанса)" << endl;
            HallTemplate* custom = new HallTemplate(*this);
            // Пользовательская логика: ограничиваем количество сеансов
            if (custom->defaultSchedule.size() > 2) {
                custom->defaultSchedule.resize(2);
            }
            return custom;
        }
        return nullptr;
    }

    unique_ptr<Hall> createHall() {
        unique_ptr<Hall> hall;
        if (hallType == "Standard") hall = make_unique<StandardHall>(number, capacity);
        else if (hallType == "IMAX") hall = make_unique<ImaxHall>(number, capacity);
        else hall = make_unique<VipHall>(number, capacity);

        for (const auto& session : defaultSchedule) {
            hall->addSession(session);
        }
        return hall;
    }

    void setNumber(int num) { number = num; }
    void addDefaultSession(const Session& session) { defaultSchedule.push_back(session); }
    int getNumber() const { return number; }
    int getCapacity() const { return capacity; }
    int getCleanupTime() const { return cleanupTimeMinutes; }
    size_t getScheduleCount() const { return defaultSchedule.size(); }
};
