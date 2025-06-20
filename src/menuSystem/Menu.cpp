#include "../../include/menuSystem/Menu.h"
#include "../../include/SaveManager.h"

Menu::Menu(SDL_Renderer* ren, bool pause, SaveManager *sm)
    : renderer(ren), isPauseMenu(pause), saveManager(sm), running(true), inMenu(true), font(nullptr) {

    textColor.r = 255;
    textColor.g = 255;
    textColor.b = 255;

    hoverColor.r = 255;
    hoverColor.g = 255;
    hoverColor.b = 255;
    hoverColor.a = 100;

    if (SDL_Init(SDL_INIT_VIDEO) == 0 || TTF_Init() == 0) {
        std::cerr << "SDL or TTF Init Failed: " << SDL_GetError() << std::endl;
    }

    font = TTF_OpenFont("assets/font.ttf", 48);
    if (!font) {
        std::cerr << "Failed to load font.\n";
    }
    returnValue = -1;

    rebuildButtons();
}

Menu::~Menu() {
    cleanUp();
}

void Menu::cleanUp() {
    for (int i = 0; i < buttons.size(); ++i) {
        if (buttons[i].texture != nullptr) {
            SDL_DestroyTexture(buttons[i].texture);
            buttons[i].texture = nullptr;
        }
    }
    if (font) {
        TTF_CloseFont(font);
    }
}


int Menu::run() {

    running = true;
    inMenu = true;

    rebuildButtons();

    while (running) {
        
        handleEvents();

        updateButtons();

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        for (int i = 0; i < buttons.size(); ++i) {
            renderButton(buttons[i]);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    // return 1 if back to game or 0 if quit
    // return 2 to upgrade attack, 3 to upgrade max health
    return returnValue; 
}

void Menu::handleEvents() {

    SDL_Event e;
    while (SDL_PollEvent(&e)) {

        if (e.type == SDL_EVENT_QUIT) // if the user clicks the X button on the window
            running = false;
        

        float mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN && inMenu) {
            for (int i = 0; i < buttons.size(); ++i) {
                if (isMouseOver(buttons[i].rect, mouseX, mouseY)) {
                    if (buttons[i].label == "Start Game") {
                        std::cout << "Starting Game...\n";
                        inMenu = false;
                        running = false;
                        returnValue = 1;
                    } else if (buttons[i].label == "Resume") {
                        std::cout << "Resuming...\n";
                        inMenu = false;
                        running = false;
                        returnValue = 1;
                    } else if (buttons[i].label == "Options") {
                        std::cout << "Opening Options...\n";
                    } else if (buttons[i].label == "Quit") {
                        std::cout << "Quitting...\n";
                        running = false;
                        returnValue = 0;
                    } else if (buttons[i].label == "Load") {
                        std::cout << "Loading...\n";
                        saveManager->run(SaveManager::Operation::Load);
                    } else if (buttons[i].label == "Save") {
                        saveManager->run(SaveManager::Operation::Save);
                        std::cout << "Saving...\n";
                    } else if (buttons[i].label == "Upgrade attack") {
                        //std::cout << "Increasing attack\n";
                        running = false;
                        returnValue = 2;
                    } else if (buttons[i].label == "Upgrade health") {
                        //std::cout << "Increasing max health\n";
                        running = false;
                        returnValue = 3;
                    }
                }
            }
        }
    }
}

bool Menu::isMouseOver(SDL_FRect rect, int x, int y) {
    return (x >= rect.x && x <= rect.x + rect.w &&
            y >= rect.y && y <= rect.y + rect.h);
}

void Menu::renderButton(Button& button) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderFillRect(renderer, &button.rect);

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, button.label.c_str(),  button.label.size(), textColor);
    if (!textSurface) return;

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    int textW = textSurface->w;
    int textH = textSurface->h;
    SDL_DestroySurface(textSurface);

    SDL_FRect dstFRect;
    dstFRect.w = textW;
    dstFRect.h = textH;
    dstFRect.x = button.rect.x + (button.rect.w - textW) / 2;
    dstFRect.y = button.rect.y + (button.rect.h - textH) / 2;

    SDL_RenderTexture(renderer, textTexture, nullptr, &dstFRect);

    if (button.isHovered) {
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, hoverColor.r, hoverColor.g, hoverColor.b, hoverColor.a);
        SDL_RenderFillRect(renderer, &dstFRect);
    }

    if (button.texture) {
        SDL_DestroyTexture(button.texture);
    }
    button.texture = textTexture;
}


void Menu::updateButtons() {
    float mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    for (int i = 0; i < buttons.size(); ++i) {
        buttons[i].isHovered = isMouseOver(buttons[i].rect, mouseX, mouseY);
    }
}

void Menu::rebuildButtons() {
    // Implemented in the PauseMenu and StartMenu classes
}
