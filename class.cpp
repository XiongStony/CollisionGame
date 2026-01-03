#include "class.hpp"

Cube::Cube(int x, int y, int width, int length, double v, double damp, double mass, double fracrate)
    : rect{x,y,width,length}, 
    v{v}, 
    fracrate{fracrate}, 
    mass{mass}, 
    damp{damp}, 
    pos_x(x), 
    p{mass*v} {
        assert(mass > 0);
    }

double Cube::update_pv(double p_change){
    this->p += p_change;
    this->v = this->p/this->mass;
    return this->v;
}

double Cube::update_p(){
    this->p = this->v * this->mass;
    return this->p;
}

void Cube::update_v_mv(){
    if (std::abs(this->v) > this->fracrate)
        this->v = this->v*(1 - this->damp) - this->fracrate*sign(this->v);
    else this->v = 0;
    this->update_p();
}