//
// Created by pc on 27/1/2021.
//

#include "Collision.h"
#include "iostream"


bool Collision::StrictCollideRect(SDL_Rect a, SDL_Rect b) {
    int x = std::max(a.x, b.x);
    int u = std::min(a.x+a.w, b.x+b.w);
    int y = std::max(a.y, b.y);
    int v = std::min(a.y+a.h,b.y+b.h);
    return x<=u && y<=v;
}

bool Collision::PairCollide(std::pair<int, int> a, std::pair<int, int> b) {
    if (a.first <= b.first && b.first <= a.second) return 1;
    if (a.first <= b.second && b.second <= a.second) return 1;
    return 0;
}

bool Collision::CollideByArea(SDL_Rect a, SDL_Rect b) {
    int x = std::max(a.x, b.x);
    int y = std::max(a.y, b.y);
    int u = std::min(a.x + a.w, b.x + b.w);
    int v = std::min(a.y + a.h, b.y + b.h);
    int area = x <= u && y <= v ? (x - u) * (y - v) : 0;
    return area >= a.w * a.h * 20/100;
}
