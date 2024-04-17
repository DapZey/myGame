//
// Created by benra on 3/16/2024.
//

#include "PlayerAnimationManager.h"
PlayerAnimationManager::PlayerAnimationManager() {
    currentState = idleDown;
    animationStartTime = 0;
    currentAnimationTime = 0;
    animationCoordinateMap["forward"] = 4;
    animationCoordinateMap["frontLeft"] = 7;
    animationCoordinateMap["right"] = 2;
    animationCoordinateMap["backLeft"] = 5;
    animationCoordinateMap["back"] = 0;
    animationCoordinateMap["backRight"] = 3;
    animationCoordinateMap["left"] = 6;
    animationCoordinateMap["frontRight"] = 1;
}
Rectangle PlayerAnimationManager::InputPlayerAnimation(PlayerAnimationManager::AnimationState state, float time,
                                                       std::string animCode, int type) {
    int multiplyer = animationCoordinateMap[animCode];
    previousState = currentState;
    currentState = state;
    if (currentState != previousState){
        animationStartTime = time;
    }
    currentAnimationTime = (time - animationStartTime) ;
    float x = 0;
    if (type == 0){
        x = static_cast<float>(animBlockSpacing + (animBlockSpacing * (int(currentAnimationTime) % 4)));
    }
    else if (type ==1){
        x = float (animStartX * multiplyer);
    }
    else if (type == 2){
        x= static_cast<float>(animStartX + (animBlockSpacing * (int(currentAnimationTime) %4)));
    }
    return {x,static_cast<float>(animStartY + (animBlockSpacing*multiplyer)),52,52};
}
PlayerAnimationManager::~PlayerAnimationManager(){

}