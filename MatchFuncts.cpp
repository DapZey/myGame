//
// Created by benra on 3/15/2024.
//

#include "MatchFuncts.h"
#include <cmath>
Vector2 MatchFuncts::normalize(const Vector2 &vec) {
    float mag = magnitude(vec);
    // Check if the magnitude is not zero to avoid division by zero
    if (mag != 0.0f) {
        return {vec.x / mag, vec.y / mag};
    } else {
        // If the magnitude is zero, return a zero vector or handle it as appropriate for your use case
        return {0.0f, 0.0f};
    }
}
float MatchFuncts::magnitude(const Vector2& vec) {
    return std::sqrt(vec.x * vec.x + vec.y * vec.y);
}
Vector2 MatchFuncts::Vector2Lerp(const Vector2& a, const Vector2& b, float t) {
    return {
            a.x + (b.x - a.x) * t,
            a.y + (b.y - a.y) * t
    };
}
float MatchFuncts::Vector2Distance(const Vector2& a, const Vector2& b) {
    float dx = b.x - a.x;
    float dy = b.y - a.y;
    return sqrt(dx * dx + dy * dy);
}