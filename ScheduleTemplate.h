// ScheduleTemplate.h
#pragma once
#include "Session.h"
#include "Cloneable.h"
#include <vector>
#include <string>

using namespace std;

// === НАСТРОЙКИ: Шаблоны расписаний ===
struct ScheduleTemplateData {
    string name;
    string workStart;
    string workEnd;
    int sessionIntervalMinutes;
    int breakDurationMinutes;
    int maxSessionsPerDay;
};

vector<ScheduleTemplateData> scheduleTemplates = {
    {"weekday", "10:00", "23:00", 30, 15, 8},
    {"weekend", "09:00", "02:00", 20, 10, 12}
};

class ScheduleTemplate : public Cloneable {
private:
    string templateName;
    string workStart;
    string workEnd;
    int sessionIntervalMinutes;
    int breakDurationMinutes;
    int maxSessionsPerDay;
    vector<Session> sessions;

public:
    ScheduleTemplate(const string& name) : templateName(name) {
        for (const auto& tmpl : scheduleTemplates) {
            if (tmpl.name == name) {
                workStart = tmpl.workStart;
                workEnd = tmpl.workEnd;
                sessionIntervalMinutes = tmpl.sessionIntervalMinutes;
                breakDurationMinutes = tmpl.breakDurationMinutes;
                maxSessionsPerDay = tmpl.maxSessionsPerDay;
                break;
            }
        }
    }

    // Конструктор копирования (глубокое копирование)
    ScheduleTemplate(const ScheduleTemplate& other)
        : templateName(other.templateName), workStart(other.workStart), workEnd(other.workEnd),
        sessionIntervalMinutes(other.sessionIntervalMinutes), breakDurationMinutes(other.breakDurationMinutes),
        maxSessionsPerDay(other.maxSessionsPerDay) {
        // Глубокое копирование сеансов
        for (const auto& session : other.sessions) {
            sessions.push_back(session);
        }
    }

    // Клонирование с выбором глубины
    void* clone(CloneDepth depth = CloneDepth::DEEP) const override {
        switch (depth) {
        case CloneDepth::SHALLOW:
            cout << "  [ScheduleTemplate] Поверхностное копирование" << endl;
            return new ScheduleTemplate(*this);

        case CloneDepth::DEEP:
            cout << "  [ScheduleTemplate] Глубокое копирование" << endl;
            return new ScheduleTemplate(*this);

        case CloneDepth::CUSTOM:
            cout << "  [ScheduleTemplate] Пользовательское копирование" << endl;
            ScheduleTemplate* custom = new ScheduleTemplate(*this);
            custom->setName(templateName + "_copy");
            return custom;
        }
        return nullptr;
    }

    void addSession(const Session& session) { sessions.push_back(session); }
    string getName() const { return templateName; }
    void setName(const string& name) { templateName = name; }
    int getSessionCount() const { return sessions.size(); }
    string getWorkStart() const { return workStart; }
    string getWorkEnd() const { return workEnd; }
    int getSessionInterval() const { return sessionIntervalMinutes; }
    int getBreakDuration() const { return breakDurationMinutes; }
};