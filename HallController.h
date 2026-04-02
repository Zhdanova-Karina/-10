#pragma once

#include "IEquipmentController.h"
#include "EquipmentProxy.h"
#include <vector>
#include <memory>
#include <map>
#include <functional>

using namespace std;

// ”правл€ет оборудованием зала и выполнением сценариев
class HallController : public IEquipmentController {
private:
    vector<shared_ptr<EquipmentProxy>> equipmentList;  // список всего оборудовани€ зала (через прокси)
    map<string, vector<pair<int, string>>> scenarios;  // сценарии: им€ -> список (задержка, команда)
    int hallNumber;                                     // номер зала, которым управл€ет контроллер

    void log(const string& message);  // внутреннее логирование действий

public:
    HallController(int hallNum = 0);  // конструктор с указанием номера зала

    // ”правление оборудованием
    void registerEquipment(shared_ptr<Equipment> eq);  // регистрирует новое оборудование
    void executeCommand(const string& command) override;  // выполн€ет команду
    vector<string> getStatuses() override;                 // получает статусы всего оборудовани€
    void turnOnAll() override;                             // включает все оборудование
    void turnOffAll() override;                            // выключает все оборудование
    void emergencyStop() override;                         // аварийна€ остановка

    // –абота со сценари€ми
    void loadScenario(const string& name, const vector<pair<int, string>>& commands);  // загружает сценарий
    void runScenario(const string& name);                                              // запускает сценарий

    // ƒоступ к оборудованию по ID
    shared_ptr<EquipmentProxy> getEquipment(const string& deviceId);
};