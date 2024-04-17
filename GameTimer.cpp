//
// Created by benra on 3/5/2024.
//
#include "GameTimer.h"
GameTimer::GameTimer() {
    prev = 0;
    current = 0;
    frames = 0;
    fps= 0;
    seconds = 0;
    secondsPrev = 0;
}
GameTimer::~GameTimer(){
}
float GameTimer::getCurrentTimeInSeconds() {
    static const auto start = std::chrono::high_resolution_clock::now();
    auto now = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - start);
    return float (duration.count()) / 1000.0f;// Convert milliseconds to seconds
}
float GameTimer::calculateDeltatime(float &prev, float &current){
    float delta = current - prev;
    prev = current;
    return delta;
}
float GameTimer::run() {
    frames++;
    current = getCurrentTimeInSeconds();
    calculateFps(seconds, secondsPrev, frames, current, fps);
    float deltaTime = calculateDeltatime(prev, current);
    return deltaTime;
}
void GameTimer::calculateFps(int &seconds, int &secondsPrev, int &frames, float &current, int &fps){
    seconds = current;
    if (seconds > secondsPrev){
        fps = frames;
        secondsPrev = seconds;
        frames = 0;
    }
}