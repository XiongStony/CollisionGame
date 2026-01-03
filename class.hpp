#pragma once

#include "head.hpp"

class Cube{
public:
    SDL_Rect rect;
    double v;
    double pos_x;
    double damp,fracrate;
    const double mass;
    double p;

    Cube(int x, int y, int width, int length,
        double v = 0, double damp = 0, double mass = 1, double fracrate = 0
    );

    double update_pv(double p_change);
    double update_p();
    void update_v_mv();
};
