// SessionPool.h
#pragma once
#include "Session.h"
#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <iostream>
#include <thread>

using namespace std;

class SessionPool {
private:
    // === НАСТРОЙКИ: Параметры пула ===
    int initialSize = 0;        // Начальный размер
    int maxSize = 10;           // Максимальный размер
    bool allowExpansion = true; // Возможность расширения
    int timeoutSeconds = 5;    // Таймаут ожидания (секунды)

    queue<unique_ptr<Session>> availableSessions;
    int poolSize;
    mutex poolMutex;
    condition_variable cv;

    SessionPool() : poolSize(initialSize) {
        for (int i = 0; i < initialSize; i++) {
            availableSessions.push(make_unique<Session>());
        }
        cout << "[SessionPool] Создан: maxSize=" << maxSize
            << ", timeout=" << timeoutSeconds << "с"
            << ", expansion=" << (allowExpansion ? "да" : "нет") << endl;
    }

public:
    static SessionPool& getInstance() {
        static SessionPool instance;
        return instance;
    }

    // Получение сеанса с таймаутом
    unique_ptr<Session> acquireSession(const string& movie, const string& time, int duration) {
        unique_lock<mutex> lock(poolMutex);

        cout << "[SessionPool] Ожидание сеанса (таймаут " << timeoutSeconds << " сек)..." << endl;

        // Ожидание с таймаутом
        if (availableSessions.empty()) {
            auto start = chrono::steady_clock::now();

            bool gotSession = cv.wait_for(lock, chrono::seconds(timeoutSeconds), [this] {
                return !availableSessions.empty();
                });

            auto end = chrono::steady_clock::now();
            auto elapsed = chrono::duration_cast<chrono::seconds>(end - start).count();

            if (!gotSession) {
                cout << "[SessionPool] ⏰ Таймаут! Ожидание " << elapsed << " сек, объект не получен" << endl;

                // Если разрешено расширение, создаём новый объект
                if (allowExpansion && poolSize < maxSize) {
                    poolSize++;
                    cout << "[SessionPool] ✅ Создан новый сеанс (расширение пула, всего: " << poolSize << ")" << endl;
                    return make_unique<Session>(movie, time, duration);
                }

                cout << "[SessionPool] ❌ Невозможно получить сеанс (пул заполнен, расширение запрещено)" << endl;
                return nullptr;
            }

            cout << "[SessionPool] ✅ Получен сеанс после ожидания " << elapsed << " сек" << endl;
        }

        auto session = move(availableSessions.front());
        availableSessions.pop();
        session->setMovieName(movie);
        session->setStartTime(time);
        session->setDuration(duration);

        cout << "[SessionPool] Выдан сеанс (доступно: " << availableSessions.size() << ")" << endl;
        return session;
    }

    // Получение сеанса без ожидания (мгновенно)
    unique_ptr<Session> tryAcquireSession(const string& movie, const string& time, int duration) {
        lock_guard<mutex> lock(poolMutex);

        if (availableSessions.empty()) {
            cout << "[SessionPool] ❌ Нет свободных сеансов" << endl;
            return nullptr;
        }

        auto session = move(availableSessions.front());
        availableSessions.pop();
        session->setMovieName(movie);
        session->setStartTime(time);
        session->setDuration(duration);

        cout << "[SessionPool] Выдан сеанс (доступно: " << availableSessions.size() << ")" << endl;
        return session;
    }

    // Получение сеанса с пользовательским таймаутом
    unique_ptr<Session> acquireSessionWithTimeout(const string& movie, const string& time, int duration, int customTimeout) {
        unique_lock<mutex> lock(poolMutex);

        cout << "[SessionPool] Ожидание сеанса (пользовательский таймаут " << customTimeout << " сек)..." << endl;

        if (availableSessions.empty()) {
            auto start = chrono::steady_clock::now();

            bool gotSession = cv.wait_for(lock, chrono::seconds(customTimeout), [this] {
                return !availableSessions.empty();
                });

            auto end = chrono::steady_clock::now();
            auto elapsed = chrono::duration_cast<chrono::seconds>(end - start).count();

            if (!gotSession) {
                cout << "[SessionPool] ⏰ Таймаут! Ожидание " << elapsed << " сек" << endl;
                return nullptr;
            }
        }

        auto session = move(availableSessions.front());
        availableSessions.pop();
        session->setMovieName(movie);
        session->setStartTime(time);
        session->setDuration(duration);

        return session;
    }

    void releaseSession(unique_ptr<Session> session) {
        lock_guard<mutex> lock(poolMutex);
        if (availableSessions.size() < static_cast<size_t>(maxSize)) {
            availableSessions.push(move(session));
            cout << "[SessionPool] Сеанс возвращен (доступно: " << availableSessions.size() << ")" << endl;
            cv.notify_one();
        }
        else {
            cout << "[SessionPool] Пул заполнен, сеанс удален" << endl;
        }
    }

    int getAvailableCount() {
        lock_guard<mutex> lock(poolMutex);
        return availableSessions.size();
    }

    int getTotalSize() {
        lock_guard<mutex> lock(poolMutex);
        return poolSize;
    }

    void setMaxSize(int size) {
        lock_guard<mutex> lock(poolMutex);
        maxSize = size;
        cout << "[SessionPool] Максимальный размер пула изменён на " << maxSize << endl;
    }

    void setTimeout(int seconds) {
        timeoutSeconds = seconds;
        cout << "[SessionPool] Таймаут изменён на " << timeoutSeconds << " сек" << endl;
    }
};