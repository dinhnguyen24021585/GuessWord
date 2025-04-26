#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include <windows.h>
#include"def.h"
#include"graphics.h"
#include"logic.h"
#include"game.h"
using namespace std;

int main(int argc, char* argv[]){
    Graphics graphics;
    graphics.init_graphics();
    init_game(graphics.renderer,graphics.home_button,graphics.replay_button,graphics.next_button);

    GuessWord game;
    game.init_logic();

    vector<Scrolling_bgr>v_bgr;
    for(int i=0;i<5;i++)
    {
        Scrolling_bgr bgr;
        bgr.set_texture(graphics.load_texture("assets/bgr/Picture1.png"));
        bgr.scrolling_offset =  i * bgr.width;
        v_bgr.push_back(bgr);
    }
    int* _y_pos = new int [5];
    _y_pos = init_scroll_bgr();

    render_background(game);
    render_homepage(game);

    string text_input; 
    SDL_StartTextInput();

    SDL_Event e;
    int x,y;
    bool quit = false;
    bool playing = false;
    bool new_lvl = false;
    bool blind_box = false;

    int space_cnt = 0;

    srand(time(0));
    int lucky_num = rand() % 10 + 1;
    
    Mix_Chunk* ans_true = graphics.load_sound("assets/sound/true.wav");
    Mix_Chunk* ans_false = graphics.load_sound("assets/sound/false.wav");

    while(!quit){cout<<lucky_num;
        if (playing && !new_lvl ){
            if (game.cur_lvl <= maxlvl){
                SDL_Texture* sun = graphics.load_texture("assets/bgr/sun.png");
                graphics.render_texture(sun,-75,-75);
                SDL_DestroyTexture(sun);
            }
            scroll_bgr(game,v_bgr,_y_pos);
            render_gameplay(game,new_lvl);
        }
        else if (!playing)  render_homepage(game);
        graphics.present_scene();
        SDL_GetMouseState(&x,&y);
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                quit = true;
                break;
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN){
                cerr<<x<<" "<<y<<'\n';
                if (!playing && x>=300 && y>=250 && x<=500 && y<=325){
                    new_lvl = true;
                    render_gameplay(game,new_lvl);
                    playing = 1;
                }   
                if (playing && x>=30 && y>=30 && x<=90 && y<=85){
                    render_homepage(game);
                    playing = 0;
                }
                if (playing && x>=700 && y>=30 && x<=770 && y<=85){
                    text_box();
                    text_input = "";
                }
                if (playing && new_lvl && x>=595 && y>=540 && x<=800 && y<=600){
                    render_gameplay(game,new_lvl);
                    text_box();
                    if (game.cur_lvl == maxlvl + 1) blind_box = true;
                    text_input = "";
                }
                if (blind_box && x>=300 && x<=500){
                    for (int i=0;i<10;i++){
                        if(y>=120+45*i && y<=155+45*i){
                            if(lucky_num == i+1) secret();
                            else see_you_next_time();
                            new_lvl = true;
                            blind_box = false;
                        }
                    }
                }
            
            }
            else if ((e.type == SDL_TEXTINPUT || e.type == SDL_KEYDOWN) && playing){
                if (e.key.keysym.scancode == SDL_SCANCODE_RETURN)  
                {
                    if (!new_lvl){
                        if (game.check(text_input)){
                            graphics.print_text(text_input.c_str(),0,255,0,0,400 - ((29 * (text_input.size() - space_cnt) + 4 * space_cnt) / 4),423,25);
                            graphics.print_text("Đáp án đúng:",0,255,0,0,400-(29*9 + 4*2)/4,453,25);
                            graphics.print_text(game.lvl_ans_vn[game.cur_lvl-1].c_str(),0,255,0,0,400-(29 * (game.lvl_ans_vn[game.cur_lvl-1].size() - game.space_cnt[game.cur_lvl-1]) + 4 * game.space_cnt[game.cur_lvl-1])/4,478,25);
                            game.cur_lvl++;
                            graphics.play(ans_true);
                            new_lvl = true;
                            graphics.set_pos_to_show_image(graphics.next_button,595,540);
                            text_input = "";
                        }
                        else {
                            graphics.print_text("Đáp án sai",255,0,0,0,400-(29*8 + 4*2)/4,453,25);
                            new_lvl = true;
                            graphics.present_scene();
                            graphics.play(ans_false);
                            SDL_Delay(2000);
                            render_gameplay(game,new_lvl);
                            text_box();
                            text_input = "";  
                            space_cnt = 0;
                            
                        }
                    }
                }
                if (e.key.keysym.scancode != SDL_SCANCODE_BACKSPACE){
                    if ((isalpha(*e.text.text) || isdigit(*e.text.text) || *e.text.text == ' ') && text_input.size() < game.lvl_ans[game.cur_lvl-1].size()){
                        if (*e.text.text == ' ') space_cnt++;
                        text_input += e.text.text;
                    }
                }
                else if (e.key.keysym.scancode == SDL_SCANCODE_BACKSPACE) {
                    text_box();
                    if (*text_input.rbegin() == ' ') space_cnt--;
                    if (text_input.size()) text_input.erase(text_input.end()-1);
                }
                if (!new_lvl){
                    if (text_input.size() && text_input.size() <= game.lvl_ans[game.cur_lvl-1].size()) 
                    {
                        text_box();
                        graphics.print_text(text_input.c_str(),0,0,0,0,400 - ((29 * (text_input.size() - space_cnt) + 4 * space_cnt) / 4),423,25);
                    }
                    else graphics.print_text(" ",0,0,0,0,225,423,25);
                }
                else space_cnt = 0;
            }

          
        }
    //graphics.present_scene();
    SDL_Delay(1);
    }

    if (ans_true) Mix_FreeChunk(ans_true);
    if (ans_false) Mix_FreeChunk(ans_false);
    graphics.quit();

    return 0;
}
