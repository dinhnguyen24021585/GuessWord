#ifndef _GRAPHICS__H
#define _GRAPHICS__H

#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include <windows.h>
#include"def.h"
#include"logic.h"
#include<time.h>
struct Scrolling_bgr{
    SDL_Texture* texture;
    int width,height;
    int scrolling_offset = 0;

    void set_texture(SDL_Texture* _texture){
        texture = _texture;
        SDL_QueryTexture(texture,NULL,NULL,&width,&height);
    }

    void scroll(int dist){
        scrolling_offset -= dist;
        if(scrolling_offset < -width) {
            scrolling_offset = window_width;
        }
    }
};

struct Graphics{
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Texture* home_button,*replay_button,*next_button;
        GuessWord game;
        
        //error message
        void error_message(const char* message, const char* error){
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_INFO,"%s: %s",message, error);
            SDL_Quit();
        }

        //check error
        void init_SDL(){
            //check media
            if(SDL_Init(SDL_INIT_EVERYTHING)) error_message("SDL_Init",SDL_GetError()); //0 = 0 errors, 1 = has error(s)

            //if media didn't get error, create window
            window = SDL_CreateWindow(title,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,window_width,window_height,SDL_WINDOW_SHOWN);

            //check window error
            if (window == nullptr) error_message("Can't open window - Error:",SDL_GetError());

            //create default renderer
            renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (renderer == nullptr) error_message("Renderer error: ",SDL_GetError());

            SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"linear");
            SDL_RenderSetLogicalSize(renderer,window_width,window_height);

            //check image error
            if(!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)) error_message("Image error: ",SDL_GetError());

            if(TTF_Init() == -1)  error_message("Initiailize font failed: ",TTF_GetError());

            //check audio
            if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ){
                    error_message("SDL_mixer could not initialize! SDL_mixer Error: %s\n",Mix_GetError());
            }

        }

        void init_graphics(){
            init_SDL();
            home_button = load_texture("assets/button/home.png");
            replay_button = load_texture("assets/button/replay.png");
            next_button = load_texture("assets/button/next.png");
        }

        //create custom renderer
        SDL_Renderer* create_renderer(){
            SDL_Renderer* _renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (_renderer == nullptr) error_message("Renderer error: ",SDL_GetError());
            return _renderer;
        }

        //insert font       
        TTF_Font* load_font(const char* path, int size){
            TTF_Font* font = TTF_OpenFont(path,size);
            if (!font) error_message("Load font failed ",TTF_GetError());
            return font;
        }

        //show text
        SDL_Texture* show_text(TTF_Font* text_font,const char* text,SDL_Color text_color){
            //load surface for text
            SDL_Surface* surface = TTF_RenderUTF8_Blended(text_font,text,text_color); //alternative choice for Vietnamese instead of TTF_RenderSolidText
            if(!surface) error_message("Text surface load error ",TTF_GetError());

            //load texture for text -> show text
            SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer,surface);
            if (!text_texture) error_message("Text texture load error ",SDL_GetError());

            SDL_FreeSurface(surface);
            return text_texture;
        }

        //extension func for print text
        void print_text (const char* text,Uint8 red,Uint8 green,Uint8 blue,Uint8 alpha,int _x,int _y,int size){
            TTF_Font* font = load_font("assets/TNH-Xuong.ttf",size);
            SDL_Color color = {red,green,blue,alpha};
            SDL_Texture* _text = show_text(font,text,color);
            set_pos_to_show_image(_text,_x,_y);
        }

        void draw_rectangle(int _x,int _y,int _h,int _w){
            SDL_Rect rect = {_x,_y,_w,_h};
            SDL_RenderDrawRect(renderer,&rect);
        }
        
        //load image
        SDL_Texture *load_texture(const char *filename){
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_INFO,"Loading %s",filename);
            SDL_Texture *texture = IMG_LoadTexture(renderer,filename);
            if(texture == NULL)
                    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_INFO,"Load image failed %s",IMG_GetError());
            return texture;
        }

        void render_texture(SDL_Texture* texture,int x,int y){
            SDL_Rect rect;
            rect.x = x;
            rect.y = y;
            SDL_QueryTexture(texture,NULL,NULL,&rect.w,&rect.h);
            SDL_RenderCopy(renderer,texture,NULL,&rect);
        }

        void set_pos_to_show_image(SDL_Texture* texture,int _x,int _y){
            
            SDL_Rect pos;
            pos.x = _x;
            pos.y = _y;
            SDL_QueryTexture(texture,NULL,NULL,&pos.w,&pos.h);
            SDL_RenderCopy(renderer,texture,NULL,&pos);
        }

        void render_scrolling_bgr(Scrolling_bgr bgr, int y_pos){
            render_texture(bgr.texture,bgr.scrolling_offset,y_pos);
        }

        Mix_Chunk* load_sound(const char* path){
            Mix_Chunk *gEffect = Mix_LoadWAV(path);
            if (gEffect == nullptr) {
                error_message("Could not load music! SDL_mixer Error: %s", Mix_GetError());
            }
            return gEffect;
        }

        void play(Mix_Chunk* gChunk) {
            if (gChunk != nullptr) {
                Mix_PlayChannel( -1, gChunk, 0 );
            }
        }


        void prepare_scene(SDL_Texture* background){
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer,background,NULL,NULL);
        }

        void present_scene(){
            SDL_RenderPresent(renderer);
        }

        void quit(){
            Mix_Quit();
            TTF_Quit();
            SDL_DestroyTexture(home_button);
            SDL_DestroyTexture(replay_button);
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_Quit();
            IMG_Quit();
        }

};



#endif
