#pragma once

#include <iostream>
#include "task.hpp"

enum class TaskId{redLightOn, redLightOff, blueLightOn, blueLightOff, extractorOn, extractorOff, waterOn, waterOff};

class RedLightOn : public Task<TaskId> {
    public:
    int x;
    std::string str;

    public:
    RedLightOn() : x(1), str("redLightOn"){
        type=TaskId::redLightOn;
    };
};

struct RedLightOff : public Task<TaskId> {
    public:
    int y;
    double d;
    std::string str;

    public:
    RedLightOff() : y(2), d(42.42), str("redLightOff"){
        type=TaskId::redLightOff;
    };

};

struct BlueLightOn : public Task<TaskId> {
    public:
    int y;
    std::string str;

    public:
    BlueLightOn() : y(3), str("blueLightOn"){
        type=TaskId::blueLightOn;
    };

};

struct BlueLightOff : public Task<TaskId> {
    public:
    int y;
    std::string str;

    public:
    BlueLightOff() : y(4), str("blueLightOff"){
        type=TaskId::blueLightOff;
    };

};

struct ExtractorOn : public Task<TaskId> {
    public:
    int y;
    std::string str;

    public:
    ExtractorOn() : y(5), str("extractorOn"){
        type=TaskId::extractorOn;
    };

};

struct ExtractorOff : public Task<TaskId> {
    public:
    double z;
    std::string str;

    public:
    ExtractorOff() : z(42.43), str("extractorOff"){
        type=TaskId::extractorOff;
    };

};

struct WaterOn : public Task<TaskId> {
    public:
    int y;
    std::string str;

    public:
    WaterOn() : y(7), str("waterOn"){
        type=TaskId::waterOn;
    };

};

struct WaterOff : public Task<TaskId> {
    public:
    int y;
    std::string str;

    public:
    WaterOff() : y(8), str("waterOff"){
        type=TaskId::waterOff;
    };

};