#include "Equipment.h"

using namespace std;

// Конструктор: инициализирует оборудование с заданным ID
Equipment::Equipment(const string& id)
    : deviceId(id), status("off"), isOn(false) {}

// Включение оборудования
void Equipment::turnOn() {
    isOn = true;        // устанавливаем флаг включения
    status = "on";      // обновляем статус
    cout << "[" << deviceId << "] включен" << endl;
}

// Выключение оборудования
void Equipment::turnOff() {
    isOn = false;       // сбрасываем флаг включения
    status = "off";     // обновляем статус
    cout << "[" << deviceId << "] выключен" << endl;
}

// Возвращает текущий статус оборудования
string Equipment::getStatus() const {
    return status;
}

// Выполняет диагностику оборудования
// Возвращает карту с параметрами в зависимости от оборудования
map<string, string> Equipment::diagnose() {
    map<string, string> diag;
    diag["deviceId"] = deviceId;  // ID оборудования
    diag["status"] = status;      // текущий статус
    diag["type"] = getType();     // тип оборудования
    return diag;
}

// Возвращает идентификатор оборудования
string Equipment::getDeviceId() const {
    return deviceId;
}