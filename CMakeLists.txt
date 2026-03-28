cmake_minimum_required(VERSION 3.16)

project(lab2_queue_qt VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    main.cpp
    part1/QueueItem.h
    part1/QueueItem.cpp
    part1/CustomExceptions.h
    part1/CustomExceptions.cpp
    part1/BaseQueue.h
    part1/BaseQueue.cpp
    part1/SortableNumberQueue.h
    part1/SortableNumberQueue.cpp
    part2/TemplateQueue.h
    part2/TemplateQueueExceptions.h
    gui/MainWindow.h
    gui/MainWindow.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(lab2_queue_qt
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    add_executable(lab2_queue_qt
        ${PROJECT_SOURCES}
    )
endif()

target_link_libraries(lab2_queue_qt PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(lab2_queue_qt)
endif()
