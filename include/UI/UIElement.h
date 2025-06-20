#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

/*
* This is used to create small UI elements, which can be used to make a proper UI
*
*/

/*TODO:
* Refactor it so it can derive classes for more different UI elements
* I think it's a good idea to remove the dependency from player and enemy and find a different approach
* Some UI should be clickable so that should also be made
* 
*/



class UIElement {
private:
    SDL_FRect rect;
    SDL_Texture* texture = nullptr;
    SDL_Renderer* renderer;

    std::string displayInfo;
    TTF_Font* font;
    SDL_Color textColor;

public:
    UIElement(SDL_Renderer* ren, float x, float y, float w, float h);
    ~UIElement();


    /*
    * This method updates the UI element's position
    */
    void update(float x, float y, int hp);

    /*
    * This method renders the current position of the UI
    */
    void render();

private:
    void cleanUp();
};