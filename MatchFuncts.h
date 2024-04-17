//
// Created by benra on 3/15/2024.
//

#ifndef UNTITLED1_MATCHFUNCTS_H
#define UNTITLED1_MATCHFUNCTS_H
#include "raylib.h"

class MatchFuncts {
public:
    static Vector2 normalize(const Vector2& vec);
    static float magnitude(const Vector2& vec);
    static Vector2 Vector2Lerp(const Vector2& a, const Vector2& b, float t);
    static float Vector2Distance(const Vector2& a, const Vector2& b);
};


#endif //UNTITLED1_MATCHFUNCTS_H
