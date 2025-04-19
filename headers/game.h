#ifndef _GAME__H
#define _GAME__H

#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include"graphics.h"
#include"logic.h"
#include<time.h>

using namespace std;

Graphics graphics;

//init
void init_game(SDL_Renderer* _renderer,SDL_Texture* _home_button,SDL_Texture*_replay_button,SDL_Texture* _next_button){
    graphics.renderer = _renderer;
    graphics.home_button = _home_button;
    graphics.replay_button = _replay_button;
    graphics.next_button = _next_button;
}

int* init_scroll_bgr(){
    int* y_postion_of_cloud = new int[5];
    srand(time(0));
    for(int i=0;i<5;i++) y_postion_of_cloud[i] = rand() % 50 + 51;
    return y_postion_of_cloud;
}
//

//endscreen
void end_screen(){
    graphics.print_text("Bất ngờ chưa, cuối game có xé túi mù nè!",0,0,0,0,150,25,25);
    graphics.print_text("Chọn 1 trong 10 túi và chỉ được xé 1 lần thui nha:3",0,0,0,0,100,75,25);
    SDL_SetRenderDrawColor(graphics.renderer,0,0,0,0);
    for(int i=0;i<10;i++){
        graphics.draw_rectangle(300,120+45*i,35,200);
        string num = to_string(i+1);
        graphics.print_text(num.c_str(),0,0,0,0,395,125+45*i,25);
    }
}

void see_you_next_time(){
    SDL_SetRenderDrawColor(graphics.renderer,135,206,235,0);
    SDL_RenderClear(graphics.renderer);
    graphics.print_text("Bạn đã xé được túi 'Zone Nghị Lực'",0,0,0,0,200,250,25);
    graphics.print_text("Chúc bạn may mắn lần sau!",0,0,0,0,250,300,25);
}

void secret(){
    Mix_Chunk* shock = graphics.load_sound("assets/sound/shock.wav");
    graphics.play(shock);
    
    SDL_SetRenderDrawColor(graphics.renderer,135,206,235,0);
    SDL_RenderClear(graphics.renderer);
    graphics.print_text("Síc rịc tới đây:))",0,0,0,0,305,25,25);
    graphics.print_text("Cảm ơn bạn dã dành thời gian để chơi hết game và nhận 1 meme:))",0,0,0,0,25,550,25);
    SDL_Texture* secret = graphics.load_texture("assets/secret.png");
    graphics.set_pos_to_show_image(secret,200,75);
    graphics.present_scene();
    SDL_Delay(1000);
    if (shock) Mix_FreeChunk(shock);
}
//

void text_box(){
    SDL_SetRenderDrawColor(graphics.renderer,135,206,235,0);
    SDL_Rect text_box = {0,423,800,25};
    SDL_RenderFillRect(graphics.renderer,&text_box);
}

//bgr
void render_background(const GuessWord& game){
    SDL_SetRenderDrawColor(graphics.renderer,135,206,235,0);
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.h = window_height;
    rect.w = window_width;
    SDL_RenderFillRect(graphics.renderer,&rect);

}

void scroll_bgr(const GuessWord& game,vector<Scrolling_bgr>&v_bgr, int* _y_pos){
    for(int i=0;i<5;i++){
        v_bgr[i].scroll(1);
        if (v_bgr[i].scrolling_offset >= - v_bgr[i].width) graphics.render_scrolling_bgr(v_bgr[i],_y_pos[i]);
    }
}
//

void render_homepage(const GuessWord& game){
    SDL_SetRenderDrawColor(graphics.renderer,135,206,235,0);
    SDL_RenderClear(graphics.renderer);

    SDL_Texture* logo = graphics.load_texture("assets/logo.png");
    graphics.set_pos_to_show_image(logo,280,0);

    SDL_SetRenderDrawColor(graphics.renderer,0,0,0,0);
    SDL_Rect play_button;
    play_button.x = 300;
    play_button.y = 250;
    play_button.h = 75;
    play_button.w = 200;
    SDL_RenderDrawRect(graphics.renderer,&play_button);
    graphics.print_text("Play",0,0,0,0,350,260,50);

    SDL_DestroyTexture(logo);
}

void render_gameplay(const GuessWord& game,bool &new_lvl){
    if(game.cur_lvl <= maxlvl){
        if (new_lvl) {
            SDL_SetRenderDrawColor(graphics.renderer,135,206,235,0);
            SDL_RenderClear(graphics.renderer);
            text_box();  
            new_lvl=false;
        }
    
        graphics.set_pos_to_show_image(graphics.home_button,30,30);
        graphics.set_pos_to_show_image(graphics.replay_button,window_width-90,30);

        graphics.print_text("Lvl.",0,0,0,0,360,10,25);
        string num_lvl = to_string(game.cur_lvl);
        graphics.print_text(num_lvl.c_str(),0,0,0,0,408,10,25);

        SDL_Texture* img = graphics.load_texture(game.img_path[game.cur_lvl-1].c_str());
        graphics.set_pos_to_show_image(img,100,100);

        SDL_SetRenderDrawColor(graphics.renderer,0,0,0,0);
        graphics.draw_rectangle(310,-1,50,150);
        graphics.draw_rectangle(100,100,300,600);
        SDL_RenderDrawLine(graphics.renderer,200,450,600,450);

        SDL_DestroyTexture(img);
    }
    else {
        new_lvl = false;
        SDL_SetRenderDrawColor(graphics.renderer,135,206,235,0);
        SDL_RenderClear(graphics.renderer);
        graphics.set_pos_to_show_image(graphics.home_button,30,30);
        end_screen();
    }
}


#endif
