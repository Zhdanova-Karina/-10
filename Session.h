// Session.h
#pragma once
#include <string>
#include <iostream>
#include <vector>

using namespace std;

// Класс, представляющий один сеанс
class Session {
private:
    string movieName;      // название фильма
    string startTime;      // время начала
    int duration;          // продолжительность в минутах
    int hallNumber;        // номер зала
    double price;          // цена билета
    int availableSeats;    // количество свободных мест

public:
    // Конструкторы
    Session();
    Session(const string& movie, const string& time, int dur);
    Session(const string& movie, const string& time, int dur, int hall, double p, int seats);
    Session(const Session& other);

    // Оператор присваивания
    Session& operator=(const Session& other);

    // Деструктор
    ~Session() = default;

    // Геттеры
    string getMovieName() const;
    string getStartTime() const;
    int getDuration() const;
    int getHallNumber() const;
    double getPrice() const;
    int getAvailableSeats() const;

    // Сеттеры
    void setMovieName(const string& name);
    void setStartTime(const string& time);
    void setDuration(int dur);
    void setHallNumber(int hall);
    void setPrice(double p);
    void setAvailableSeats(int seats);

    // Бронирование места
    bool bookSeat();
    void returnSeat();

    // Вывод информации
    void display() const;
};