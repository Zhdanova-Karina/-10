#pragma once

#include <string>

using namespace std;

class Movie {
private:
    string title;           // название фильма
    int duration;           // продолжительность в минутах
    string genre;           // жанр (комедия, боевик, драма и т.д.)
    int ageRestriction;     // возрастное ограничение (0, 6, 12, 16, 18)
    string mediaFile;       // путь к файлу с фильмом для воспроизведения

public:
    // Конструктор: создает фильм на основе параметров
    Movie(const string& t, int dur, const string& gen, int age, const string& media);

    string getTitle() const;           // возвращает название фильма
    int getDuration() const;            // возвращает продолжительность
    string getGenre() const;            // возвращает жанр
    int getAgeRestriction() const;      // возвращает возрастное ограничение
    string getMediaFile() const;        // возвращает путь к файлу фильма
};