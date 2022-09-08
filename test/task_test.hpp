#pragma once

#include <iostream>
#include "task.hpp"

enum class TaskId{redLightOn=0, redLightOff, blueLightOn, blueLightOff, extractorOn, extractorOff, waterOn, waterOff};

struct RedLightOn : public Task<TaskId> {
    RedLightOn(){
        type=TaskId::redLightOn;
    };
    void execute()override{};
};

struct RedLightOff : public Task<TaskId> {
    RedLightOff(){
        type=TaskId::redLightOff;
    };
    void execute()override{};
};

struct BlueLightOn : public Task<TaskId> {
    BlueLightOn(){
        type=TaskId::blueLightOn;
    };
    void execute()override{};
};

struct BlueLightOff : public Task<TaskId> {
    BlueLightOff(){
        type=TaskId::blueLightOff;
    };
    void execute()override{};
};

struct ExtractorOn : public Task<TaskId> {
    ExtractorOn(){
        type=TaskId::extractorOn;
    };
    void execute()override{};
};

struct ExtractorOff : public Task<TaskId> {
    public:
    ExtractorOff(){
        type=TaskId::extractorOff;
    };
    void execute()override{};
};

struct WaterOn : public Task<TaskId> {
    WaterOn(){
        type=TaskId::waterOn;
    };
    void execute() override{};
};

struct WaterOff : public Task<TaskId> {
    WaterOff(){
        type=TaskId::waterOff;
    };
    void execute()override{};
};