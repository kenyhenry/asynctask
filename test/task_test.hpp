#pragma once

#include <iostream>
#include "task.hpp"

enum class TaskId{redLightOn=0, redLightOff, blueLightOn, blueLightOff, extractorOn, extractorOff, waterOn, waterOff};

struct RedLightOn{
    static constexpr TaskId type = TaskId::redLightOn;
    int x;
};

struct RedLightOff{
    static constexpr TaskId type=TaskId::redLightOff;
    int x;
};

struct BlueLightOn{
    static constexpr TaskId type=TaskId::blueLightOn;
    int x;
};

struct BlueLightOff{
    static constexpr TaskId type=TaskId::blueLightOff;
    int x;
};

struct ExtractorOn{
    static constexpr TaskId type=TaskId::extractorOn;
    int x;
};

struct ExtractorOff{
    static constexpr TaskId type=TaskId::extractorOff;
    int x;
};

struct WaterOn{
    static constexpr TaskId type=TaskId::waterOn;
    int x;
};

struct WaterOff{
    const TaskId type=TaskId::waterOff;
    int x;
};