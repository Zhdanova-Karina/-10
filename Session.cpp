// Session.cpp
#include "Session.h"
#include <iostream>

using namespace std;

// Конструктор по умолчанию
Session::Session()
    : movieName(""), startTime(""), duration(0), hallNumber(0), price(0.0), availableSeats(0) {}

// Конструктор с базовыми параметрами
Session::Session(const string& movie, const string& time, int dur)
    : movieName(movie), startTime(time), duration(dur), hallNumber(0), price(0.0), availableSeats(0) {}

// Полный конструктор
Session::Session(const string& movie, const string& time, int dur, int hall, double p, int seats)
    : movieName(movie), startTime(time), duration(dur), hallNumber(hall), price(p), availableSeats(seats) {}

// Конструктор копирования
Session::Session(const Session& other)
    : movieName(other.movieName),
    startTime(other.startTime),
    duration(other.duration),
    hallNumber(other.hallNumber),
    price(other.price),
    availableSeats(other.availableSeats) {}

// Оператор присваивания
Session& Session::operator=(const Session& other) {
    if (this != &other) {
        movieName = other.movieName;
        startTime = other.startTime;
        duration = other.duration;
        hallNumber = other.hallNumber;
        price = other.price;
        availableSeats = other.availableSeats;
    }
    return *this;
}

// Геттеры
string Session::getMovieName() const { return movieName; }
string Session::getStartTime() const { return startTime; }
int Session::getDuration() const { return duration; }
int Session::getHallNumber() const { return hallNumber; }
double Session::getPrice() const { return price; }
int Session::getAvailableSeats() const { return availableSeats; }

// Сеттеры
void Session::setMovieName(const string& name) { movieName = name; }
void Session::setStartTime(const string& time) { startTime = time; }
void Session::setDuration(int dur) { duration = dur; }
void Session::setHallNumber(int hall) { hallNumber = hall; }
void Session::setPrice(double p) { price = p; }
void Session::setAvailableSeats(int seats) { availableSeats = seats; }

// Бронирование места
bool Session::bookSeat() {
    if (availableSeats > 0) {
        availableSeats--;
        return true;
    }
    return false;
}

// Возврат места
void Session::returnSeat() {
    availableSeats++;
}

// Вывод информации о сеансе
void Session::display() const {
    cout << "Фильм: " << movieName
        << ", Время: " << startTime
        << ", Длительность: " << duration << " мин."
        << ", Зал: " << hallNumber
        << ", Цена: " << price << " руб."
        << ", Свободных мест: " << availableSeats << endl;
}