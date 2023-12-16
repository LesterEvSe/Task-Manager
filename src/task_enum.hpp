#ifndef TASKENUM_HPP
#define TASKENUM_HPP

#include <QString>

enum TaskEnum {
    OVERDUE,
    TODAY,
    ALL_ACTIVE
};

inline QString taskEnumStr(TaskEnum task) {
    switch (task) {
        case OVERDUE:    return "Overdue";
        case TODAY:      return "Today";
        case ALL_ACTIVE: return "All tasks";
        default: return "Unknown";
    }
}

#endif // TASKENUM_HPP
