#pragma once
#include <string>
#include <map>
#include <iostream>

using namespace std;

class Equipment {
protected:
    string deviceId;
    string status;
    bool isOn;

public:
    Equipment(const string& id);
    virtual ~Equipment() = default;

    virtual void turnOn();   // включение оборудования
    virtual void turnOff();  // выключение оборудования
    virtual string getStatus() const;  // получение статуса
    virtual map<string, string> diagnose(); // диагностика: возвращает параметры оборудования
    string getDeviceId() const; // получение ID оборудования

    virtual string getType() const = 0;  // возвращает тип оборудования
};