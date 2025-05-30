#ifndef RENDERER_H
#define RENDERER_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <string>
#include <stdexcept>
#include <sstream>

/*TODO:
 * Make it work with .png, something else rather than .bmp
 *
 *
 */

/**
 * Manages SDL window and rendering context.
 * Handles texture loading, sprite drawing, and screen presentation.
 */

class Renderer {
private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    static int objectCount;
public:
    /**
     * Initializes SDL, creates a window and renderer.
     * @param roomWidth Room width in tiles.
     * @param roomHeight Room height in tiles.
     * @param tileSize Size of each tile in pixels.
     */
    Renderer(int roomWidth, int roomHeight, int tileSize);

    /**
     * Default constructor (does not initialize SDL).
     */
    Renderer();

    /**
     * Cleans up SDL renderer and window.
     */
    ~Renderer();

    SDL_Window* getWindow() const;
    SDL_Renderer* getRenderer() const;
    static int getObjectCount();
    SDL_Renderer* getSDLRenderer();

    void setWindow(SDL_Window* newWindow);
    void setRenderer(SDL_Renderer* newRenderer);

    /**
     * Manually initializes the SDL context.
     */
    void init(int roomWidth, int roomHeight, int tileSize);

    /**
     * Loads a BMP image into an SDL texture.
     * @throws std::runtime_error if loading fails.
     */
    SDL_Texture* loadSprite(const std::string& imagePath);

    SDL_Texture* loadSpritePNG(const std::string& path);

    /**
     * Draws the specified texture at the given position and size.
     */
    void drawSprite(SDL_Texture* texture, int x, int y, int width, int height, bool flipHorizontally = false);

    /**
     * Draws the entire screen using repeated tiles.
     */
    void drawRoomTiled(SDL_Texture* tileTexture, int roomWidth, int roomHeight, int tileSize);

    /**
     * Presents the rendered frame to the screen.
     */
    void present();

    /**
    * Clears old sprites. Use before drawing anything new otherwise you might get weird image rendering.
    */
    void clear();

    /**
     * Returns a string summary of renderer state.
     */
    std::string toString() const;
};

#endif
