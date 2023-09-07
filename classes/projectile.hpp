#ifndef projectile_hpp
#define projectile_hpp

#include <raylib.h>

class Projectile 
{
private:
    Texture2D projectileSprite;
    Rectangle hitbox;

public:
    // constructors
    Projectile();
    Projectile();
};

#endif // projectile_hpp