#include "../../include/utilities/MathUtils.h"
#include <SDL3/SDL.h>

// This function checks if two rectangles have at least 1 pixel of matchin area

bool intersects(const SDL_FRect& a, const SDL_FRect& b) {
    return (a.x < b.x + b.w &&
        a.x + a.w > b.x &&
        a.y < b.y + b.h &&
        a.y + a.h > b.y);
}