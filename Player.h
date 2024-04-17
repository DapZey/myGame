//
// Created by benra on 3/15/2024.
//

#ifndef UNTITLED1_PLAYER_H
#define UNTITLED1_PLAYER_H
#include "raylib.h"
#include "PlayerAnimationManager.h"
class Player {
public:
    enum Direction{
        up,down,left,right,upRight,upLeft,downRight,downLeft
    };
    enum State{
        moveable, attacking
    };
    State state;
    float attackStage;
    float attackStartTime;
    Direction direction;
    bool damageFrame;
    Vector2 GetPlayerPos();
    Camera2D getPlayerCamera();
    Direction checkCurrentDirection(float x, float y);
    void update(float deltaTime);
    void draw(float time);
    Player(int screenWidth, int screenHeight);
    ~Player();
    void move(Vector2& direction, float deltaTime);
    Texture2D playerTextureMap;
    Texture2D playerTextureMapAttack;
    Vector2 playerPositionRounded;
private:
    PlayerAnimationManager animationManager;
    Camera2D playerFollowCamera;
    Vector2 playerSize;
    Vector2 movementDirection;
    float moveSpeed;
};


#endif //UNTITLED1_PLAYER_H
