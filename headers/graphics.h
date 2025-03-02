#ifndef _GRAPHICS__H
#define _GRAPHICS__H

#include<SDL.h>
#include<SDL_image.h>
#include"def.h"
struct Graphics{
        SDL_Window* window;
        SDL_Renderer* renderer;

        //error message
        void error_message(const char* message, const char* error){
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_INFO,"%s: %s",message, error);
            SDL_Quit();
        }

        //check error
        void init(){
            //check media
            if(SDL_Init(SDL_INIT_EVERYTHING)) error_message("SDL_Init",SDL_GetError()); //0 = 0 errors, 1 = has error(s)

            //if media didn't get error, create window
            window = SDL_CreateWindow(title,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,window_width,window_height,SDL_WINDOW_SHOWN);

            //check window error
            if (window == nullptr) error_message("Can't open window - Error:",SDL_GetError());

            renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (renderer == nullptr) error_message("Renderer error: ",SDL_GetError());

            SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"linear");
            SDL_RenderSetLogicalSize(renderer,window_width,window_height);

            //check image error
            if(!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)) error_message("Image error: ",SDL_GetError());

            //return window;
        }

        //create renderer
        // SDL_Renderer* create_render(){
            
        // }

        //load image
        SDL_Texture *load_texture(const char *filename){
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_INFO,"Loading %s",filename);
            SDL_Texture *texture = IMG_LoadTexture(renderer,filename);
            if(texture == NULL)
                    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_INFO,"Load image failed %s",IMG_GetError());
            return texture;
        }

       
        void set_pos_to_show_image(SDL_Texture* texture,int _x,int _y){
            SDL_Rect pos;
            pos.x = _x;
            pos.y = _y;
            SDL_QueryTexture(texture,NULL,NULL,&pos.w,&pos.h);
            SDL_RenderCopy(renderer,texture,NULL,&pos);
        }
        
        void prepare_scene(SDL_Texture* background){
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer,background,NULL,NULL);
        }

        void present_scene(){
            SDL_RenderPresent(renderer);
        }

        void quit(){
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_Quit();
            IMG_Quit();
        }

};

#endif