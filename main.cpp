#include "head.hpp"
#include "class.hpp"

void Update(std::vector<Cube*> cube, SDL_Window* window);
int get_y(int WindowHeight, int GroundHeight, int rectLength);

int main(int argc, char* argv[]){
    std::ios::sync_with_stdio(false); // 关闭与 stdio 的同步（提速）
    SDL_Init(SDL_INIT_EVERYTHING);

    const int WindowWidth = 1200;
    const int WindowHeight = 600;
    int GroundHeight = 200;
    int position_x = 0;
    double damp = 0;

    SDL_Window* window = SDL_CreateWindow(
        "Window",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WindowWidth, WindowHeight,
        SDL_WINDOW_SHOWN
    );

    SDL_Renderer* renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    SDL_Rect ground{0, WindowHeight - GroundHeight, WindowWidth, GroundHeight};

    int guy1Length = 100; int guy1Width = 100;
    int guy1_position_y = get_y(WindowHeight, GroundHeight, guy1Length);
    Cube guy1(position_x, guy1_position_y, guy1Width, guy1Length, 3, damp,1,0.00);

    int guy2Length = 100; int guy2Width = 100;
    int guy2_position_y = get_y(WindowHeight, GroundHeight,guy2Length);
    Cube guy2(400, guy2_position_y, guy2Width, guy2Length, 0, damp,1,0.00);

    int guy3Length = 100; int guy3Width = 100;
    int guy3_position_y = get_y(WindowHeight, GroundHeight,guy3Length);
    Cube guy3(500, guy3_position_y, guy3Width, guy3Length, 0, damp,1,0.00);
    int guy4Length = 100; int guy4Width = 100;
    int guy4_position_y = get_y(WindowHeight, GroundHeight,guy4Length);
    Cube guy4(600, guy4_position_y, guy4Width, guy4Length, 0, damp,1,0.00);

    std::vector<Cube*> Cubes{&guy1, &guy2, &guy3, &guy4};
    bool running = true;
    SDL_Event event;
    // main circle
    for (int loop = 0; running; loop++){

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderFillRect(renderer, &ground);

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &guy1.rect);
        
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        SDL_RenderFillRect(renderer, &guy2.rect);

        SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
        SDL_RenderFillRect(renderer, &guy3.rect);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &guy4.rect);

        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                running = false;
            } else if (event.type == SDL_KEYDOWN){
            
                if (event.key.keysym.sym == SDLK_q){
                    running = false;
                }
            }
        }
        
        SDL_RenderPresent(renderer);
        SDL_Delay(5);
        Update(Cubes, window);
        if (loop%20 == 0){
            std::cout<<"x= "<<guy1.rect.x;
            std::cout<<", pos_x= "<<guy1.pos_x;
            std::cout<<", mass="<<guy1.mass;
            std::cout<<", v= "<<guy1.v<<"\n";
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
