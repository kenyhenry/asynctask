#pragma once

#include <iostream>
#include "task.hpp"

enum class TaskId{redLightOn=0, redLightOff, blueLightOn, blueLightOff, extractorOn, extractorOff, waterOn, waterOff};

struct RedLightOn : public Task<TaskId> {
    RedLightOn(){
        type=TaskId::redLightOn;
    };
};

struct RedLightOff : public Task<TaskId> {
    RedLightOff(){
        type=TaskId::redLightOff;
    };
};

struct BlueLightOn : public Task<TaskId> {
    BlueLightOn(){
        type=TaskId::blueLightOn;
    };
};

struct BlueLightOff : public Task<TaskId> {
    BlueLightOff(){
        type=TaskId::blueLightOff;
    };
};

struct ExtractorOn : public Task<TaskId> {
    ExtractorOn(){
        type=TaskId::extractorOn;
    };
};

struct ExtractorOff : public Task<TaskId> {
    public:
    ExtractorOff(){
        type=TaskId::extractorOff;
    };

};

struct WaterOn : public Task<TaskId> {
    WaterOn(){
        type=TaskId::waterOn;
    };
};

struct WaterOff : public Task<TaskId> {
    WaterOff(){
        type=TaskId::waterOff;
    };
};