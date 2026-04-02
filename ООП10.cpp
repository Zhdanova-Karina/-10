#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <sstream>
#include <ctime>
#include <iomanip>
#include "Cinema.h"
#include "Projector.h"
#include "SoundSystem.h"
#include "LightSystem.h"
#include "AirConditioner.h"
#include "DoorLock.h"
#include "Session.h"

#include "ProjectorFactory.h"
#include "EquipmentFactory.h"
#include "ConfigManager.h"
#include "HallTemplate.h"
#include "ScheduleTemplate.h"
#include "SessionPool.h"

using namespace std;

// Функция для получения текущего времени в формате ЧЧ:ММ:СС
string getCurrentTime() {
    auto now = chrono::system_clock::now();
    auto time_t_now = chrono::system_clock::to_time_t(now);
    tm time_info;
    localtime_s(&time_info, &time_t_now);
    stringstream ss;
    ss << put_time(&time_info, "%H:%M:%S");
    return ss.str();
}

void printSeparator(const string& title) {
    cout << "\n" << string(80, '=') << endl;
    cout << "[" << getCurrentTime() << "] " << title << endl;
    cout << string(80, '=') << endl;
}

void printSubsection(const string& title) {
    cout << "\n[" << getCurrentTime() << "] --- " << title << " ---" << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "[" << getCurrentTime() << "] Запуск программы" << endl;

    printSeparator("ЛАБОРАТОРНАЯ РАБОТА 10: ПОРОЖДАЮЩИЕ ПАТТЕРНЫ");

    // ==================== 1. SINGLETON (с резервным копированием) ====================
    printSeparator("1. ПАТТЕРН SINGLETON (ОДИНОЧКА) - ConfigManager");

    printSubsection("Получение первого экземпляра ConfigManager");
    ConfigManager* config1 = ConfigManager::getInstance();
    cout << "[" << getCurrentTime() << "]   Адрес первого экземпляра: " << config1 << endl;

    printSubsection("Отображение конфигурации по умолчанию");
    config1->showAllConfigs();

    printSubsection("Изменение конфигурации (создаётся резервная копия)");
    cout << "[" << getCurrentTime() << "]   Устанавливаем новые значения..." << endl;
    config1->setConfig("cinema_name", "Мегаполис Кино");
    config1->setConfig("default_volume", "75");
    config1->setConfig("default_brightness", "85");

    printSubsection("Получение второго экземпляра ConfigManager");
    ConfigManager* config2 = ConfigManager::getInstance();
    cout << "[" << getCurrentTime() << "]   Адрес второго экземпляра: " << config2 << endl;

    printSubsection("Проверка Singleton (сравнение экземпляров)");
    if (config1 == config2) {
        cout << "[" << getCurrentTime() << "]   ✓ Экземпляры идентичны! Singleton работает корректно." << endl;
        cout << "[" << getCurrentTime() << "]   ✓ Оба указателя ссылаются на один и тот же объект в памяти." << endl;
    }
    else {
        cout << "[" << getCurrentTime() << "]   ✗ Ошибка: Создано несколько экземпляров!" << endl;
    }

    printSubsection("Проверка сохраненных настроек");
    cout << "[" << getCurrentTime() << "]   cinema_name = " << config2->getConfig("cinema_name") << endl;
    cout << "[" << getCurrentTime() << "]   default_volume = " << config2->getConfig("default_volume") << endl;
    cout << "[" << getCurrentTime() << "]   default_brightness = " << config2->getConfig("default_brightness") << endl;

    printSubsection("Список созданных резервных копий");
    config1->listBackups();

    // ==================== 2. FACTORY METHOD ====================
    printSeparator("2. ПАТТЕРН FACTORY METHOD (ФАБРИЧНЫЙ МЕТОД)");

    printSubsection("Создание фабрик для разных типов проекторов");
    cout << "[" << getCurrentTime() << "]   StandardHallFactory - создает обычные проекторы" << endl;
    cout << "[" << getCurrentTime() << "]   VipHallFactory - создает 3D-проекторы для VIP-залов" << endl;
    cout << "[" << getCurrentTime() << "]   ImaxHallFactory - создает IMAX-проекторы" << endl;

    unique_ptr<ProjectorFactory> stdFactory = make_unique<StandardHallFactory>();
    unique_ptr<ProjectorFactory> vipFactory = make_unique<VipHallFactory>();
    unique_ptr<ProjectorFactory> imaxFactory = make_unique<ImaxHallFactory>();

    printSubsection("Создание проектора через StandardHallFactory");
    auto stdProjector = stdFactory->createProjector("proj_std_001");
    cout << "[" << getCurrentTime() << "]   Создан проектор типа: " << stdProjector->getType() << endl;
    stdProjector->turnOn();
    cout << "[" << getCurrentTime() << "]   Статус: " << stdProjector->getStatus() << endl;
    stdProjector->turnOff();

    printSubsection("Создание проектора через VipHallFactory");
    auto vipProjector = vipFactory->createProjector("proj_vip_001");
    cout << "[" << getCurrentTime() << "]   Создан проектор типа: " << vipProjector->getType() << endl;
    vipProjector->turnOn();
    cout << "[" << getCurrentTime() << "]   Статус: " << vipProjector->getStatus() << endl;

    printSubsection("Создание проектора через ImaxHallFactory");
    auto imaxProjector = imaxFactory->createProjector("proj_imax_001");
    cout << "[" << getCurrentTime() << "]   Создан проектор типа: " << imaxProjector->getType() << endl;
    imaxProjector->turnOn();
    cout << "[" << getCurrentTime() << "]   Статус: " << imaxProjector->getStatus() << endl;

    // ==================== 3. ABSTRACT FACTORY ====================
    printSeparator("3. ПАТТЕРН ABSTRACT FACTORY (АБСТРАКТНАЯ ФАБРИКА)");

    printSubsection("Создание фабрик для разных типов залов");
    cout << "[" << getCurrentTime() << "]   StandardFactory - комплект для обычного зала" << endl;
    cout << "[" << getCurrentTime() << "]   VipFactory - комплект для VIP зала" << endl;
    cout << "[" << getCurrentTime() << "]   ImaxFactory - комплект для IMAX зала" << endl;

    unique_ptr<EquipmentFactory> stdEquipFactory = make_unique<StandardFactory>();
    unique_ptr<EquipmentFactory> vipEquipFactory = make_unique<VipFactory>();
    unique_ptr<EquipmentFactory> imaxEquipFactory = make_unique<ImaxFactory>();

    printSubsection("Стандартный комплект оборудования");
    auto stdProj = stdEquipFactory->createProjector("std_proj");
    auto stdSound = stdEquipFactory->createSoundSystem("std_sound");
    auto stdLight = stdEquipFactory->createLightSystem("std_light");
    cout << "[" << getCurrentTime() << "]   Создано оборудование:" << endl;
    cout << "[" << getCurrentTime() << "]     - Проектор: " << stdProj->getType() << endl;
    cout << "[" << getCurrentTime() << "]     - Аудиосистема: " << stdSound->getType() << endl;
    cout << "[" << getCurrentTime() << "]     - Освещение: " << stdLight->getType() << endl;
    stdLight->turnOn();
    stdSound->turnOn();

    printSubsection("VIP комплект оборудования");
    auto vipProj = vipEquipFactory->createProjector("vip_proj");
    auto vipSound = vipEquipFactory->createSoundSystem("vip_sound");
    auto vipLight = vipEquipFactory->createLightSystem("vip_light");
    cout << "[" << getCurrentTime() << "]   Создано оборудование:" << endl;
    cout << "[" << getCurrentTime() << "]     - Проектор: " << vipProj->getType() << endl;
    cout << "[" << getCurrentTime() << "]     - Аудиосистема: " << vipSound->getType() << endl;
    cout << "[" << getCurrentTime() << "]     - Освещение: " << vipLight->getType() << endl;
    vipLight->turnOn();
    vipSound->turnOn();

    printSubsection("IMAX комплект оборудования");
    auto imaxProj = imaxEquipFactory->createProjector("imax_proj");
    auto imaxSound = imaxEquipFactory->createSoundSystem("imax_sound");
    auto imaxLight = imaxEquipFactory->createLightSystem("imax_light");
    cout << "[" << getCurrentTime() << "]   Создано оборудование:" << endl;
    cout << "[" << getCurrentTime() << "]     - Проектор: " << imaxProj->getType() << endl;
    cout << "[" << getCurrentTime() << "]     - Аудиосистема: " << imaxSound->getType() << endl;
    cout << "[" << getCurrentTime() << "]     - Освещение: " << imaxLight->getType() << endl;
    imaxLight->turnOn();
    imaxSound->turnOn();
    // ==================== 4. PROTOTYPE (с разной глубиной клонирования) ====================
    printSeparator("4. ПАТТЕРН PROTOTYPE (ПРОТОТИП)");

    printSubsection("Создание оригинального шаблона зала с сеансами");
    // Используем правильный способ создания HallTemplate
    HallTemplate* originalHall = HallTemplate::createFromTemplate("StandardHall", 1);
    originalHall->addDefaultSession(Session("Аватар", "18:00", 180));
    originalHall->addDefaultSession(Session("Начало", "21:00", 150));
    originalHall->addDefaultSession(Session("Титаник", "15:00", 194));

    cout << "[" << getCurrentTime() << "]   Оригинальный шаблон зала:" << endl;
    cout << "[" << getCurrentTime() << "]     - Номер: " << originalHall->getNumber() << endl;
    cout << "[" << getCurrentTime() << "]     - Вместимость: " << originalHall->getCapacity() << endl;
    cout << "[" << getCurrentTime() << "]     - Сеансов в шаблоне: " << originalHall->getScheduleCount() << endl;

    printSubsection("Глубокое клонирование (копируются все сеансы)");
    HallTemplate* hallDeep = static_cast<HallTemplate*>(originalHall->clone(CloneDepth::DEEP));
    hallDeep->setNumber(2);
    cout << "[" << getCurrentTime() << "]   Клон (глубокий):" << endl;
    cout << "[" << getCurrentTime() << "]     - Номер: " << hallDeep->getNumber() << endl;
    cout << "[" << getCurrentTime() << "]     - Сеансов в шаблоне: " << hallDeep->getScheduleCount() << " (все скопированы)" << endl;

    printSubsection("Поверхностное клонирование (сеансы НЕ копируются)");
    HallTemplate* hallShallow = static_cast<HallTemplate*>(originalHall->clone(CloneDepth::SHALLOW));
    hallShallow->setNumber(3);
    cout << "[" << getCurrentTime() << "]   Клон (поверхностный):" << endl;
    cout << "[" << getCurrentTime() << "]     - Номер: " << hallShallow->getNumber() << endl;
    cout << "[" << getCurrentTime() << "]     - Сеансов в шаблоне: " << hallShallow->getScheduleCount() << " (не скопированы)" << endl;

    printSubsection("Пользовательское клонирование (только первые 2 сеанса)");
    HallTemplate* hallCustom = static_cast<HallTemplate*>(originalHall->clone(CloneDepth::CUSTOM));
    hallCustom->setNumber(4);
    cout << "[" << getCurrentTime() << "]   Клон (пользовательский):" << endl;
    cout << "[" << getCurrentTime() << "]     - Номер: " << hallCustom->getNumber() << endl;
    cout << "[" << getCurrentTime() << "]     - Сеансов в шаблоне: " << hallCustom->getScheduleCount() << " (только первые 2)" << endl;

    printSubsection("Создание реальных залов из шаблонов");
    auto hallOriginal = originalHall->createHall();
    auto hallFromDeep = hallDeep->createHall();
    cout << "[" << getCurrentTime() << "]   Созданы реальные залы:" << endl;
    cout << "[" << getCurrentTime() << "]     - Зал №" << hallOriginal->getNumber() << " (из оригинала)" << endl;
    cout << "[" << getCurrentTime() << "]     - Зал №" << hallFromDeep->getNumber() << " (из глубокого клона)" << endl;

    printSubsection("Клонирование шаблона расписания");
    ScheduleTemplate originalSchedule("weekend_schedule");
    originalSchedule.addSession(Session("Дюна", "19:00", 155));
    originalSchedule.addSession(Session("Оппенгеймер", "20:30", 180));
    originalSchedule.addSession(Session("Барби", "22:00", 114));

    cout << "[" << getCurrentTime() << "]   Оригинальное расписание: " << originalSchedule.getName() << endl;
    cout << "[" << getCurrentTime() << "]     - Количество сеансов: " << originalSchedule.getSessionCount() << endl;

    ScheduleTemplate* clonedSchedule = static_cast<ScheduleTemplate*>(originalSchedule.clone(CloneDepth::DEEP));
    clonedSchedule->setName("weekday_schedule");

    cout << "[" << getCurrentTime() << "]   Клонированное расписание: " << clonedSchedule->getName() << endl;
    cout << "[" << getCurrentTime() << "]     - Количество сеансов: " << clonedSchedule->getSessionCount() << endl;

    delete originalHall;
    delete hallDeep;
    delete hallShallow;
    delete hallCustom;
    delete clonedSchedule;
    // ==================== 5. OBJECT POOL (с таймаутом) ====================
    printSeparator("5. ПАТТЕРН OBJECT POOL (ПУЛ ОБЪЕКТОВ)");

    SessionPool& pool = SessionPool::getInstance();

    printSubsection("Инициализация пула сеансов");
    cout << "[" << getCurrentTime() << "]   Максимальный размер пула: 10 сеансов" << endl;
    cout << "[" << getCurrentTime() << "]   Таймаут ожидания: 5 секунд" << endl;
    cout << "[" << getCurrentTime() << "]   Доступно сеансов: " << pool.getAvailableCount() << endl;
    cout << "[" << getCurrentTime() << "]   Всего создано: " << pool.getTotalSize() << endl;

    printSubsection("Запрос сеансов из пула (создание новых)");

    cout << "\n[" << getCurrentTime() << "]   Запрос сеанса 1:" << endl;
    auto s1 = pool.acquireSession("Матрица", "18:00", 136);
    cout << "[" << getCurrentTime() << "]   ";
    s1->display();

    cout << "\n[" << getCurrentTime() << "]   Запрос сеанса 2:" << endl;
    auto s2 = pool.acquireSession("Титаник", "20:00", 194);
    cout << "[" << getCurrentTime() << "]   ";
    s2->display();

    cout << "\n[" << getCurrentTime() << "]   Запрос сеанса 3:" << endl;
    auto s3 = pool.acquireSession("Гладиатор", "22:00", 155);
    cout << "[" << getCurrentTime() << "]   ";
    s3->display();

    cout << "\n[" << getCurrentTime() << "]   Состояние пула:" << endl;
    cout << "[" << getCurrentTime() << "]     Доступно сеансов: " << pool.getAvailableCount() << endl;
    cout << "[" << getCurrentTime() << "]     Всего создано: " << pool.getTotalSize() << endl;

    printSubsection("Возврат сеансов в пул");

    cout << "\n[" << getCurrentTime() << "]   Возврат сеанса 1:" << endl;
    pool.releaseSession(move(s1));
    cout << "[" << getCurrentTime() << "]   Доступно: " << pool.getAvailableCount() << endl;

    cout << "\n[" << getCurrentTime() << "]   Возврат сеанса 2:" << endl;
    pool.releaseSession(move(s2));
    cout << "[" << getCurrentTime() << "]   Доступно: " << pool.getAvailableCount() << endl;

    printSubsection("Повторное использование сеансов из пула (без таймаута)");

    cout << "\n[" << getCurrentTime() << "]   Запрос сеанса (должен быть взят из пула):" << endl;
    auto s4 = pool.acquireSession("Криминальное чтиво", "19:30", 154);
    cout << "[" << getCurrentTime() << "]   ";
    s4->display();
    cout << "[" << getCurrentTime() << "]   Доступно: " << pool.getAvailableCount() << endl;

    printSubsection("Демонстрация таймаута (запрашиваем сеанс, когда пул пуст)");

    cout << "[" << getCurrentTime() << "]   Запрашиваем сеанс, пул пуст, ожидание 5 секунд..." << endl;
    auto s_timeout = pool.acquireSessionWithTimeout("Таймаут тест", "23:00", 120, 5);
    if (s_timeout) {
        cout << "[" << getCurrentTime() << "] Сеанс получен" << endl;
        pool.releaseSession(move(s_timeout));
    }
    else {
        cout << "[" << getCurrentTime() << "] Таймаут! Сеанс не получен (это нормально для демонстрации)" << endl;
    }

    printSubsection("Возврат оставшихся сеансов");
    pool.releaseSession(move(s3));
    pool.releaseSession(move(s4));

    cout << "\n[" << getCurrentTime() << "]   Итоговое состояние пула:" << endl;
    cout << "[" << getCurrentTime() << "]     Доступно сеансов: " << pool.getAvailableCount() << endl;
    cout << "[" << getCurrentTime() << "]     Всего создано: " << pool.getTotalSize() << endl;

    printSeparator("РАБОТА ПРОГРАММЫ ЗАВЕРШЕНА");
    cout << "[" << getCurrentTime() << "] Программа успешно завершила работу" << endl;

    return 0;
}
