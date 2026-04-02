#pragma once 

#include "HallController.h"
#include <string>
#include <vector>
#include <memory>

using namespace std;

// Класс, представляющий один сеанс
class Session {
public:
    string movieName;  // название фильма
    string startTime;  // время начала
    int duration;      // продолжительность в минутах

    // Конструктор сеанса
    Session(const string& movie, const string& time, int dur)
        : movieName(movie), startTime(time), duration(dur) {}
};

// Базовый класс для всех типов залов
class Hall {
protected:
    int number;                          // номер зала
    int capacity;                        // вместимость (кол-во мест)
    string status;                       // статус: "свободен" / "занят"
    unique_ptr<HallController> controller; // контроллер управления оборудованием зала
    vector<Session> schedule;             // расписание сеансов

public:
    Hall(int num, int cap);               // конструктор
    virtual ~Hall() = default;             // виртуальный деструктор

    // Методы подготовки зала (могут отличаться для разных типов залов)
    virtual void prepareForSession(const Session& session) = 0;  // подготовка к сеансу
    virtual void cleanupAfterSession() = 0;                       // уборка после сеанса

    // Методы работы с расписанием
    bool isAvailable(const string& time);              // проверка доступности
    void addSession(const Session& session);            // добавление сеанса
    vector<Session> getSchedule() const;                // получение расписания
    int getNumber() const;                               // получение номера зала
    int getCapacity() const;                             // получение вместимости
    string getStatus() const;                            // получение статуса
    HallController* getController();                     // получение контроллера
};

// Обычный зал
class StandardHall : public Hall {
public:
    StandardHall(int num, int cap);       // конструктор
    void prepareForSession(const Session& session) override;   // подготовка к сеансу
    void cleanupAfterSession() override;                        // уборка после сеанса
};

// IMAX зал (расширенное оборудование, большой экран)
class ImaxHall : public Hall {
public:
    ImaxHall(int num, int cap);           // конструктор
    void prepareForSession(const Session& session) override;   // подготовка с учетом IMAX
    void cleanupAfterSession() override;                        // уборка с учетом особенностей
};

// VIP зал (повышенный комфорт)
class VipHall : public Hall {
public:
    VipHall(int num, int cap);            // конструктор
    void prepareForSession(const Session& session) override;   // подготовка с VIP сервисом
    void cleanupAfterSession() override;                        // завершение обслуживания
};