#include "head.hpp"
#include "class.hpp"

void Collide(Cube* a, Cube* b) {
    double n = (a->pos_x < b->pos_x) ? 1.0 : -1.0;

    double v_rel = (a->v - b->v) * n;

    if (v_rel <= 0) return;

    double e = 1.0;
    double J = -(1.0 + e) * v_rel / (1.0 / a->mass + 1.0 / b->mass);

    a->update_pv(J * n);
    b->update_pv(-J * n);
}

bool check_collision(Cube* a, Cube* b){
    if ((a->rect.x + a->rect.w > b->rect.x && a->rect.x < b->rect.x)
        || (b->rect.x + b->rect.w > a->rect.x && a->rect.x > b->rect.x)
    ){
        return true;
    } else return false;
}

void Collide_wall(std::vector<Cube*>::iterator p_cube, int win_w){
    if ((*p_cube)->pos_x + (*p_cube)->rect.w >= win_w ){ //|| (*p_cube)->pos_x <= 0
        (*p_cube)->pos_x = static_cast<double> (win_w - (*p_cube)->rect.w);
        (*p_cube)->v = -(*p_cube)->v;
        (*p_cube)->p = -(*p_cube)->p;
    } else if ((*p_cube)->pos_x <= 0){
        (*p_cube)->pos_x = 0;
        (*p_cube)->v = -(*p_cube)->v;
        (*p_cube)->p = -(*p_cube)->p;
    }
}

void UpdatePosition(std::vector<Cube*> Cubes, SDL_Window* window){
    // Get the size of window
    int win_w = 0, win_h = 0;
    SDL_GetWindowSize(window, &win_w, &win_h);
    for(std::vector<Cube*>::iterator it = Cubes.begin(); it != Cubes.end(); it++){

        (*it)->pos_x += (*it)->v;
        (*it)->rect.x = static_cast<int>(std::round((*it)->pos_x));

        Collide_wall(it, win_w);
    }
}

void UpdateSpeed(std::vector<Cube*> Cubes){
    for(std::vector<Cube*>::iterator it = Cubes.begin(); it != Cubes.end(); it++){
        (*it)->update_v_mv();
    }
    for (std::vector<Cube*>::iterator itx = Cubes.begin(); itx != Cubes.end(); itx++){
        for (std::vector<Cube*>::iterator ity = itx + 1; ity != Cubes.end(); ity++){
            if (check_collision(*itx,*ity))
                Collide(*itx,*ity);
        }
    }
}

void Update(std::vector<Cube*> Cubes, SDL_Window* window){
    UpdatePosition(Cubes, window);
    UpdateSpeed(Cubes);
}

int get_y(int WindowHeight, int GroundHeight, int rectLength){
    int position_y = WindowHeight - GroundHeight - rectLength;
    return position_y;
}