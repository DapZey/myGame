//
// Created by benra on 3/16/2024.
//

#ifndef UNTITLED2_PLAYERANIMATIONMANAGER_H
#define UNTITLED2_PLAYERANIMATIONMANAGER_H
#include "raylib.h"
#include <unordered_map>
#include <string>
class PlayerAnimationManager {
public:
    enum AnimationState{
        walkLeft,
        walkRight,
        walkUp,
        walkDown,
        walkUpLeft,
        walkUpRight,
        walkDownLeft,
        walkDownRight,
        idleLeft,
        idleRight,
        idleUp,
        idleDown,
        idleUpLeft,
        idleUpRight,
        idleDownLeft,
        idleDownRight,
        attackLeft,
        attackRight,
        attackUp,
        attackDown,
        attackUpLeft,
        attackUpRight,
        attackDownLeft,
        attackDownRight
    };
    PlayerAnimationManager();
    ~PlayerAnimationManager();
    Rectangle InputPlayerAnimation(AnimationState state, float time, std::string animCode,int type);
private:
    const int animStartX = 0;
    const int animStartY = 0;
    const int animBlockSpacing = 52;
    AnimationState currentState;
    AnimationState previousState;
    float animationStartTime;
    float currentAnimationTime;
    std::unordered_map<std::string, int> animationCoordinateMap;
};


#endif //UNTITLED2_PLAYERANIMATIONMANAGER_H
