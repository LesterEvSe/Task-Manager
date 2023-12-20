cmake_minimum_required(VERSION 3.22)
project(TaskManager)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Gui Widgets Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets Sql)

include_directories(
    src
    forms
)

set(SOURCES
    src/main.cpp
    src/base.cpp
    src/task_item_widget.cpp
    src/task.cpp
    src/database.cpp
    src/addproject.cpp
    src/concreteproject.cpp
    src/settings.cpp
)

# Necessary for moc files
set(HEADERS
    src/base.hpp
    src/task_item_widget.hpp
    src/task.hpp
    src/task_data.hpp
    src/database.hpp
    src/task_enum.hpp
    src/addproject.hpp
    src/concreteproject.hpp
    src/settings.hpp
)

# To display these files in Qt Creator
set(FORMS
    forms/base.ui
    forms/task.ui
    forms/addproject.ui
    forms/concreteproject.ui
    forms/settings.ui
)

set(ALL_SOURCES
    ${SOURCES}
    ${HEADERS}
    ${FORMS}
    resource.qrc
)

# Need for Android build
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(TaskManager
        MANUAL_FINALIZATION
        ${ALL_SOURCES}
    )
else()
    if(ANDROID)
        add_library(TaskManager SHARED ${ALL_SOURCES})
    else()
        add_executable(TaskManager ${ALL_SOURCES})
    endif()
endif()

target_link_libraries(TaskManager PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Sql
)

set_target_properties(TaskManager PROPERTIES AUTOUIC_SEARCH_PATHS forms)

install(TARGETS TaskManager
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(TaskManager)
endif()
