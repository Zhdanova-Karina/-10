#include "Hall.h"
#include <iostream>

using namespace std;

// Конструктор зала: инициализирует зал с номером и вместимостью
Hall::Hall(int num, int cap) : number(num), capacity(cap), status("свободен") {
    controller = make_unique<HallController>(num);  // создаем контроллер для этого зала
}

// Проверка, свободен ли зал в указанное время
bool Hall::isAvailable(const string& time) {
    return status == "свободен";
}

// Добавляет сеанс в расписание зала
void Hall::addSession(const Session& session) {
    schedule.push_back(session);        // добавляем в расписание
    status = "занят";                    // меняем статус
    cout << "Зал " << number << ": добавлен сеанс фильма '" << session.movieName << "' в " << session.startTime << endl;
}

// Возвращает список всех сеансов
vector<Session> Hall::getSchedule() const {
    return schedule;
}

// Возвращает номер зала
int Hall::getNumber() const {
    return number;
}

// Возвращает вместимость зала
int Hall::getCapacity() const {
    return capacity;
}

// Возвращает текущий статус зала
string Hall::getStatus() const {
    return status;
}

// Возвращает указатель на контроллер зала
HallController* Hall::getController() {
    return controller.get();
}

// ==================== StandardHall (обычный зал) ====================

StandardHall::StandardHall(int num, int cap) : Hall(num, cap) {}

// Подготовка обычного зала к сеансу
void StandardHall::prepareForSession(const Session& session) {
    cout << "Зал " << number << " (обычный): подготовка к фильму '" << session.movieName << "'" << endl;
    controller->turnOnAll();                          // включаем все оборудование
    controller->executeCommand("LightSystem.dim(25)"); // приглушаем свет на 25%
    controller->executeCommand("SoundSystem.setVolume(70)"); // устанавливаем громкость 70%
}

// Уборка после сеанса в обычном зале
void StandardHall::cleanupAfterSession() {
    cout << "Зал " << number << " (обычный): уборка после сеанса" << endl;
    controller->turnOffAll();     // выключаем все оборудование
    status = "свободен";           // освобождаем зал
}

// ==================== ImaxHall (IMAX зал) ====================

ImaxHall::ImaxHall(int num, int cap) : Hall(num, cap) {}

// Подготовка IMAX зала к сеансу
void ImaxHall::prepareForSession(const Session& session) {
    cout << "Зал " << number << " (IMAX): подготовка к IMAX-фильму '" << session.movieName << "'" << endl;
    controller->turnOnAll();                          // включаем все оборудование
    controller->executeCommand("LightSystem.dim(15)"); // сильное приглушение света (IMAX)
    controller->executeCommand("SoundSystem.setVolume(85)"); // высокая громкость (IMAX)

    // Дополнительная настройка для IMAX
    auto projector = controller->getEquipment("proj_imax");  // получаем IMAX-проектор
    if (projector) {
        cout << "  активируем специальный IMAX-проектор" << endl;  // доп. активация
    }
}

// Уборка после сеанса в IMAX зале
void ImaxHall::cleanupAfterSession() {
    cout << "Зал " << number << " (IMAX): уборка с особым оборудованием" << endl;
    controller->turnOffAll();     // выключаем все оборудование
    status = "свободен";           // освобождаем зал
}

// ==================== VipHall (VIP зал) ====================

VipHall::VipHall(int num, int cap) : Hall(num, cap) {}

// Подготовка VIP зала с дополнительным сервисом
void VipHall::prepareForSession(const Session& session) {
    cout << "Зал " << number << " (VIP): подготовка с дополнительным сервисом" << endl;
    controller->turnOnAll();                          // включаем все оборудование
    controller->executeCommand("LightSystem.dim(30)"); // мягкий свет
    controller->executeCommand("SoundSystem.setVolume(60)"); // комфортная громкость
    cout << "  подача дополнительных напитков" << endl;  // доп. сервис для VIP
}

// Завершение обслуживания после сеанса в VIP зале
void VipHall::cleanupAfterSession() {
    cout << "Зал " << number << " (VIP): завершение обслуживания гостей" << endl;
    controller->turnOffAll();     // выключаем все оборудование
    status = "свободен";           // освобождаем зал
}