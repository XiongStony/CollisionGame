#pragma once

#include <iostream>

#include<vector>
//#include<unordered_map>
#include<SDL2/SDL.h>
// #include<Eigen/Dense>
#include<cmath>
#include<cassert>

template <typename T>
T sign(T digit){
    if (digit == 0)
        return 0;
    else
        return digit>0 ? 1 : -1;
}
