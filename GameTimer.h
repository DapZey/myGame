//
// Created by benra on 3/5/2024.
//
#include <iostream>
#include <chrono>
#ifndef UNTITLED_GAMETIMER_H
#define UNTITLED_GAMETIMER_H


class GameTimer {
private:
    float prev;
    float current;
    int frames;
    int seconds;
    int secondsPrev;
    float deltatime;
public:
    int fps;
    float getCurrentTimeInSeconds();
    float calculateDeltatime(float &prev, float &current);
    void calculateFps(int &seconds, int &secondsPrev, int &frames, float &current, int &fps);
    GameTimer();
    ~GameTimer();
    int GetFrames();
    float run();
};


#endif //UNTITLED_GAMETIMER_H