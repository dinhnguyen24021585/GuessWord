#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include"headers/def.h"
#include"headers/graphics.h"
using namespace std;

//check key event to quit window
void key_event_to_quit(){
    SDL_Event e;
    while (true){
        if (SDL_PollEvent(&e) && (e.type == SDL_KEYDOWN || e.type == SDL_QUIT)) return;
        SDL_Delay(100);
    }
}

void draw(SDL_Renderer* renderer){
    SDL_SetRenderDrawColor(renderer,0,255,0,0);
    SDL_RenderDrawLine(renderer,100,200,300,400);

    SDL_SetRenderDrawColor(renderer,0,0,255,0);
    SDL_Rect rect;
    rect.x = 50;
    rect.y = 200;
    rect.w = 350;
    rect.h = 400;
    SDL_RenderDrawRect(renderer,&rect);
}

int main(int argc, char* argv[]){
    Graphics graphics;
    graphics.init();

    //draw(graphics.create_render());
    SDL_Texture* bg = graphics.load_texture("Picture2.png");
    graphics.set_pos_to_show_image(bg,0,0);
    graphics.present_scene();

    key_event_to_quit();
    graphics.quit();

    return 0;
}