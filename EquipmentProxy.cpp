// Файл EquipmentProxy.cpp
#include "EquipmentProxy.h"
#include <iomanip>

using namespace std;

// Конструктор: создает прокси на основе реального оборудования
EquipmentProxy::EquipmentProxy(shared_ptr<Equipment> realEq, const string& id)
    : Equipment(id), realEquipment(realEq) {}

// Возвращает текущее время в формате "ГГГГ-ММ-ДД ЧЧ:ММ:СС"
string EquipmentProxy::getCurrentTime() const {
    time_t now = time(0);        // получаем текущее время
    tm timeinfo;                  // структура для преобразования

    localtime_s(&timeinfo, &now);

    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeinfo);
    return string(buffer);
}

// Проверка доступа (в реальном приложении здесь может быть проверка прав)
bool EquipmentProxy::checkAccess(const string& userName) {
    // В реальном приложении здесь может быть проверка прав
    return true; // для примера всегда разрешаем
}

// Записывает действие в журнал с указанием времени
void EquipmentProxy::logAction(const string& action, bool accessGranted) const {
    string access = accessGranted ? "разрешен" : "запрещен";
    cout << "[" << getCurrentTime() << "] [PROXY " << deviceId << "] "
        << action << " - " << access << endl;
}

// Включение оборудования через прокси
void EquipmentProxy::turnOn() {
    logAction("вызов turnOn()", true);  // запись вызова

    if (checkAccess()) {  // проверка прав доступа
        logAction("разрешение выполнения операции", true);
        realEquipment->turnOn();  // вызов метода реального оборудования
        this->status = realEquipment->getStatus();  // синхронизация статуса
        logAction("операция выполнена", true);
    }
}

// Выключение оборудования через прокси
void EquipmentProxy::turnOff() {
    logAction("вызов turnOff()", true);

    if (checkAccess()) {
        logAction("разрешение выполнения операции", true);
        realEquipment->turnOff();  // вызов метода реального оборудования
        this->status = realEquipment->getStatus();  // синхронизация статуса
        logAction("операция выполнена", true);
    }
}

// Получение статуса оборудования
string EquipmentProxy::getStatus() const {
    logAction("вызов статуса", true);
    return realEquipment->getStatus();  // возвращает реальный статус
}

// Выполнение диагностики оборудования
map<string, string> EquipmentProxy::diagnose() {
    logAction("вызов диагностики", true);
    return realEquipment->diagnose();  // возвращает результат диагностики
}

// Возвращает тип оборудования с указанием, что это прокси
string EquipmentProxy::getType() const {
    return "Proxy(" + realEquipment->getType() + ")";
}