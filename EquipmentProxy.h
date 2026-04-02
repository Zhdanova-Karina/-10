#pragma once

#include "Equipment.h"
#include <memory>
#include <iostream>
#include <ctime>

using namespace std;

class EquipmentProxy : public Equipment {
private:
    shared_ptr<Equipment> realEquipment;  // ссылка на реальное оборудование

    // Проверка, есть ли у пользователя права на операцию
    bool checkAccess(const string& userName = "HallController");

    // Записывает действие в лог с указанием времени
    void logAction(const string& action, bool accessGranted) const;

    // Возвращает текущее время в формате строки
    string getCurrentTime() const;

public:
    // Конструктор: создает прокси для оборудования с ID для прокси
    EquipmentProxy(shared_ptr<Equipment> realEq, const string& id);

    // Переопределенные методы Equipment с добавлением логирования и проверки
    void turnOn() override;    // включение (с проверкой)
    void turnOff() override;   // выключение (с проверкой)
    string getStatus() const override;     // получение статуса
    map<string, string> diagnose() override;  // диагностика
    string getType() const override;  // возвращает тип (с указанием Proxy)
};