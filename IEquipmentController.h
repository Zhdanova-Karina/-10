#pragma once

#include <string>
#include <vector>

using namespace std;

// Интерфейс для управления оборудованием зала
// Определяет основные методы, которые должен реализовать контроллер
class IEquipmentController {
public:
    // Виртуальный деструктор
    virtual ~IEquipmentController() = default;

    // Выполняет команду управления оборудованием
    virtual void executeCommand(const string& command) = 0;

    // Получает статусы всего подключенного оборудования
    // @return список строк с информацией о состоянии каждого устройства
    virtual vector<string> getStatuses() = 0;

    // Включает все оборудование
    virtual void turnOnAll() = 0;

    // Выключает все оборудование
    virtual void turnOffAll() = 0;

    // Аварийная остановка (отключает все оборудование)
    virtual void emergencyStop() = 0;
};