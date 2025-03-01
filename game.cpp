#include<iostream>
#include<SDL.h>
#include<SDL_image.h>

using namespace std;

//Window setup
const int window_height = 1000;
const int window_width = 1000;
const char* title = "Guess Word";

//error message
void error_message(const string message, const string error){
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_INFO,"%s: %s",message, error);
    SDL_Quit();
}

//check error
SDL_Window* initSDL(int height, int width, const char* window_title){
    //check media
    if(SDL_Init(SDL_INIT_EVERYTHING)) error_message("SDL_Init",SDL_GetError()); //0 = 0 errors, 1 = has error(s)

    //if media didn't get error, create window
    SDL_Window* window = SDL_CreateWindow(window_title,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,SDL_WINDOW_SHOWN);

    //check window error
    if (window == nullptr) error_message("Can't open window - Error:",SDL_GetError());

    //check image error
    if(!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG)) error_message("Image error: ",SDL_GetError());

    return window;
}

//create renderer
SDL_Renderer* create_render(SDL_Window* window){
    SDL_Renderer* renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) error_message("Renderer error: ",SDL_GetError());

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"linear");
    SDL_RenderSetLogicalSize(renderer,window_width,window_height);

    return renderer;
}

//load inmage
SDL_Texture *load_texture(const char *filename, SDL_Renderer *renderer){
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_INFO,"Loading %s",filename);
        SDL_Texture *texture = IMG_LoadTexture(renderer,filename);
        if(texture == NULL)
                SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_INFO,"Load image failed %s",IMG_GetError());
        return texture;
}

void quit(SDL_Renderer* renderer,SDL_Window* window){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    IMG_Quit();
}

//check key event to quit window
void key_event_to_quit(){
    SDL_Event e;
    while (true){
        if (SDL_PollEvent(&e) && (e.type == SDL_KEYDOWN || e.type == SDL_QUIT)) return;
        SDL_Delay(1000);
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
    SDL_Window* window = initSDL(window_height,window_width,title);
    SDL_Renderer* renderer = create_render(window);

    SDL_Texture* texture = load_texture("test.jpg",renderer);
    SDL_RenderCopy(renderer,texture,NULL,NULL);

    draw(renderer);

    SDL_RenderPresent(renderer);

    key_event_to_quit();
    quit(renderer,window);

    return 0;
}