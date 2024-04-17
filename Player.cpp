//
// Created by benra on 3/15/2024.
//

#include "Player.h"
#include "MatchFuncts.h"
#include <cstdlib>
Player::Player(int screenWidth, int screenHeight) {
    direction = down;
    state = moveable;
    playerFollowCamera = {0};
    playerFollowCamera.target = { float (screenWidth)/ 2 - 25, float(screenHeight) / 2 - 25 };
    playerFollowCamera.offset = (Vector2){ float(screenWidth)/ 2, float (screenHeight) / 2 };
    playerFollowCamera.rotation = 0.0f;
    playerFollowCamera.zoom = 1.0f;

    playerTextureMap = LoadTexture(R"(C:\Users\benra\CLionProjects\untitled2\Assets/Xmove.png)");
    playerTextureMapAttack = LoadTexture(R"(C:\Users\benra\CLionProjects\untitled2\Assets/XAttack.png)");

    playerPositionRounded = {50,50};
    playerSize = {52,52};

    movementDirection = {0,0};

    moveSpeed = 500;
    attackStage = 52;
attackStartTime = 0;
damageFrame = false;
}

Camera2D Player::getPlayerCamera() {
    return playerFollowCamera;
}
Player::~Player()= default;

Player::Direction Player::checkCurrentDirection(float x, float y) {
    Player::Direction d = direction;
    if (x == -1 && y == 0){
        d = left;
    }
    else if (x == 0 && y == 0){
        d = direction;
    }
    else if (x == 1 && y == 0){
        d = right;
    }
    else if (x == 0 && y == -1){
        d = up;
    }
    else if (x == 0 && y == 1){
        d = down;
    }
    else if (x == -1 && y == -1){
        d = upLeft;
    }
    else if (x == -1 && y == 1){
        d = downLeft;
    }
    else if (x == 1 && y == 1){
        d = downRight;
    }
    else if (x == 1 && y == -1){
        d = upRight;
    }
    return d;
}
void Player::update(float deltaTime) {
    Vector2 newMovementDirection = {0, 0};
    const float lerpThreshold = 0.2f;
    const float accelerationFactor = 40.0f;
    const float diagonalFactor = 0.5f;
    if (IsKeyPressed(KEY_LEFT)){
        state = attacking;
    }
    else if (state == moveable){
        if (IsKeyDown(KEY_A)) newMovementDirection.x = -1.0f;
        if (IsKeyDown(KEY_D)) newMovementDirection.x = 1.0f;
        if (IsKeyDown(KEY_W)) newMovementDirection.y = -1.0f;
        if (IsKeyDown(KEY_S)) newMovementDirection.y = 1.0f;
    }
    direction = checkCurrentDirection(newMovementDirection.x,newMovementDirection.y);
    newMovementDirection = MatchFuncts::normalize(newMovementDirection);
    float lerpFactor = accelerationFactor * deltaTime;
    if (movementDirection.x != 0 && movementDirection.y != 0 &&
        (newMovementDirection.x == 0 || newMovementDirection.y == 0)) {
        lerpFactor *= diagonalFactor;
    }
    if (newMovementDirection.x != 0 || newMovementDirection.y != 0) {
        movementDirection = MatchFuncts::Vector2Lerp(movementDirection, newMovementDirection, lerpFactor);
    } else {
        movementDirection = MatchFuncts::Vector2Lerp(movementDirection, {0, 0}, lerpFactor);
    }
    move(movementDirection, deltaTime);
    if (MatchFuncts::Vector2Distance(movementDirection, newMovementDirection) < lerpThreshold) {
        movementDirection = newMovementDirection; // If the difference is small, set directly
    }
    playerFollowCamera.target = MatchFuncts::Vector2Lerp(playerFollowCamera.target, playerPositionRounded, 10 * deltaTime);
    if (MatchFuncts::Vector2Distance(playerFollowCamera.target, playerPositionRounded) < 0.2) {
        playerFollowCamera.target = playerPositionRounded;
    }
}


void Player::move(Vector2& direction, float deltaTime) {
    playerPositionRounded.x += direction.x * moveSpeed * deltaTime;
    playerPositionRounded.y += direction.y * moveSpeed * deltaTime;

}
void Player::draw(float time) {
    if (state == attacking){
        Rectangle anim;
        if (direction == left){
            anim = animationManager.InputPlayerAnimation(PlayerAnimationManager::attackLeft,time,"left",2);
        }
        if (direction == right){
            anim = animationManager.InputPlayerAnimation(PlayerAnimationManager::attackRight,time,"right",2);
        }

        if (direction == up){
            anim = animationManager.InputPlayerAnimation(PlayerAnimationManager::attackUp,time,"forward",2);
        }
        if (direction == down){
            anim = animationManager.InputPlayerAnimation(PlayerAnimationManager::attackDown,time,"back",2);
        }
        if (direction == upLeft){
            anim = animationManager.InputPlayerAnimation(PlayerAnimationManager::attackUpLeft,time,"backLeft",2);
        }
        if (direction == downLeft){
            anim = animationManager.InputPlayerAnimation(PlayerAnimationManager::attackDownLeft,time,"frontLeft",2);
        }
        if (direction == upRight){
            anim = animationManager.InputPlayerAnimation(PlayerAnimationManager::attackUpRight,time,"backRight",2);
        }
        if (direction == downRight){
            anim = animationManager.InputPlayerAnimation(PlayerAnimationManager::attackDownRight,time,"frontRight",2);
        }
        attackStage = anim.x;
        if (attackStage == 104 && damageFrame == false){
            damageFrame = true;
            //TODO: handleDamage();
        }
        if (attackStage == 0 && attackStartTime > 0){
            attackStartTime = 0;
            state = moveable;
            damageFrame = false;
        }
        if (attackStage != 0){
            attackStartTime++;
        }
        if (state != moveable){
            DrawTexturePro(playerTextureMapAttack, anim,{playerPositionRounded.x,playerPositionRounded.y,playerSize.x * 4,playerSize.y * 4},{0,0},0,WHITE);
        }
    }
    if (state == moveable){
        Rectangle anim;
        if (IsKeyDown(KEY_A) && !IsKeyDown(KEY_D) && !IsKeyDown(KEY_W) && !IsKeyDown(KEY_S)){
            anim = animationManager.InputPlayerAnimation(PlayerAnimationManager::walkLeft,time,"left",0);
            DrawTexturePro(playerTextureMap, anim,{playerPositionRounded.x,playerPositionRounded.y,playerSize.x * 4,playerSize.y * 4},{0,0},0,WHITE);
        }
        else if (IsKeyDown(KEY_D) && !IsKeyDown(KEY_A) && !IsKeyDown(KEY_W) && !IsKeyDown(KEY_S)){
            anim = animationManager.InputPlayerAnimation(PlayerAnimationManager::walkRight,time,"right",0);
            DrawTexturePro(playerTextureMap, anim,{playerPositionRounded.x,playerPositionRounded.y,playerSize.x * 4,playerSize.y * 4},{0,0},0,WHITE);
        }
        else if (IsKeyDown(KEY_W) && !IsKeyDown(KEY_D) && !IsKeyDown(KEY_A) && !IsKeyDown(KEY_S)){
            anim = animationManager.InputPlayerAnimation(PlayerAnimationManager::walkUp,time,"forward",0);
            DrawTexturePro(playerTextureMap, anim,{playerPositionRounded.x,playerPositionRounded.y,playerSize.x * 4,playerSize.y * 4},{0,0},0,WHITE);
        }
        else if (IsKeyDown(KEY_S) && !IsKeyDown(KEY_D) && !IsKeyDown(KEY_W) && !IsKeyDown(KEY_A)){
            anim = animationManager.InputPlayerAnimation(PlayerAnimationManager::walkDown,time,"back",0);
            DrawTexturePro(playerTextureMap, anim,{playerPositionRounded.x,playerPositionRounded.y,playerSize.x * 4,playerSize.y * 4},{0,0},0,WHITE);
        }

        else if (IsKeyDown(KEY_W) && IsKeyDown(KEY_A) && !IsKeyDown(KEY_D) && !IsKeyDown(KEY_S)){
            anim = animationManager.InputPlayerAnimation(PlayerAnimationManager::walkUpLeft,time,"backLeft",0);
            DrawTexturePro(playerTextureMap, anim,{playerPositionRounded.x,playerPositionRounded.y,playerSize.x * 4,playerSize.y * 4},{0,0},0,WHITE);
        }
        else if (IsKeyDown(KEY_W) && IsKeyDown(KEY_D) && !IsKeyDown(KEY_S) && !IsKeyDown(KEY_A)){
            anim = animationManager.InputPlayerAnimation(PlayerAnimationManager::walkUpRight,time,"backRight",0);
            DrawTexturePro(playerTextureMap, anim,{playerPositionRounded.x,playerPositionRounded.y,playerSize.x * 4,playerSize.y * 4},{0,0},0,WHITE);
        }
        else if (IsKeyDown(KEY_S) && IsKeyDown(KEY_A) && !IsKeyDown(KEY_W) && !IsKeyDown(KEY_D)){
            anim = animationManager.InputPlayerAnimation(PlayerAnimationManager::walkDownLeft,time,"frontLeft",0);
            DrawTexturePro(playerTextureMap, anim,{playerPositionRounded.x,playerPositionRounded.y,playerSize.x * 4,playerSize.y * 4},{0,0},0,WHITE);
        }
        else if (IsKeyDown(KEY_S) && IsKeyDown(KEY_D) && !IsKeyDown(KEY_W) && !IsKeyDown(KEY_A)){
            anim = animationManager.InputPlayerAnimation(PlayerAnimationManager::walkDownRight,time,"frontRight",0);
            DrawTexturePro(playerTextureMap, anim,{playerPositionRounded.x,playerPositionRounded.y,playerSize.x * 4,playerSize.y * 4},{0,0},0,WHITE);
        }
        else {
            if (direction == down){
                anim = animationManager.InputPlayerAnimation(PlayerAnimationManager::idleDown, time, "back",1);
                DrawTexturePro(playerTextureMap, anim,{playerPositionRounded.x,playerPositionRounded.y,playerSize.x * 4,playerSize.y * 4},{0,0},0,WHITE);
            }
            if (direction == left){
                anim = animationManager.InputPlayerAnimation(PlayerAnimationManager::idleLeft, time, "left",1);
                DrawTexturePro(playerTextureMap, anim,{playerPositionRounded.x,playerPositionRounded.y,playerSize.x * 4,playerSize.y * 4},{0,0},0,WHITE);
            }
            if (direction == up){
                anim = animationManager.InputPlayerAnimation(PlayerAnimationManager::idleUp, time, "forward",1);
                DrawTexturePro(playerTextureMap, anim,{playerPositionRounded.x,playerPositionRounded.y,playerSize.x * 4,playerSize.y * 4},{0,0},0,WHITE);
            }
            if (direction == upLeft){
                anim = animationManager.InputPlayerAnimation(PlayerAnimationManager::idleLeft, time, "backLeft",1);
                DrawTexturePro(playerTextureMap, anim,{playerPositionRounded.x,playerPositionRounded.y,playerSize.x * 4,playerSize.y * 4},{0,0},0,WHITE);
            }
            if (direction == upRight){
                anim = animationManager.InputPlayerAnimation(PlayerAnimationManager::idleLeft, time, "backRight",1);
                DrawTexturePro(playerTextureMap, anim,{playerPositionRounded.x,playerPositionRounded.y,playerSize.x * 4,playerSize.y * 4},{0,0},0,WHITE);
            }
            if (direction == right){
                anim = animationManager.InputPlayerAnimation(PlayerAnimationManager::idleLeft, time, "right",1);
                DrawTexturePro(playerTextureMap, anim,{playerPositionRounded.x,playerPositionRounded.y,playerSize.x * 4,playerSize.y * 4},{0,0},0,WHITE);
            }
            if (direction == downLeft){
                anim = animationManager.InputPlayerAnimation(PlayerAnimationManager::idleLeft, time, "frontLeft",1);
                DrawTexturePro(playerTextureMap, anim,{playerPositionRounded.x,playerPositionRounded.y,playerSize.x * 4,playerSize.y * 4},{0,0},0,WHITE);
            }
            if (direction == downRight){
                anim = animationManager.InputPlayerAnimation(PlayerAnimationManager::idleLeft, time, "frontRight",1);
                DrawTexturePro(playerTextureMap, anim,{playerPositionRounded.x,playerPositionRounded.y,playerSize.x * 4,playerSize.y * 4},{0,0},0,WHITE);
            }
        }
    }
}

