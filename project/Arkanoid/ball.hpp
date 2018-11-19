#ifndef BALL_HPP
#define BALL_HPP

#include <SDL2/SDL.h>
#include <iostream>

/***********************
 * BALL CLASS
 * 
 * Contains all the logic and display for the ball
 *
*/
typedef struct{ int x,y; } Speed;
class Ball{
//attributes
public:


private:
    SDL_Rect rect;
    SDL_Rect sprite_pos;
    Speed speed;
    bool ded = false;

//member functions
public:
    Ball(){
        rect = { 0,0,0,0 };
        sprite_pos = { 0,64,24,24 };
        speed.x = 0;
        speed.y = 0;
    }

    void init(int _pos_x, int _pos_y, int _speed_x, int _speed_y){
        rect.x = _pos_x;
        rect.y = _pos_y;
        speed.x = _speed_x;
        speed.y = _speed_y;
    }

    /************************
    *
    * GETTERS / SETTERS
    * 
    */

    SDL_Rect get_rect(){
        return rect;
    }

    void set_rect(SDL_Rect _rect){
        rect = _rect;
    }
    //****

    SDL_Rect get_sprite_pos(){
        return sprite_pos;
    }

    void set_sprite_pos(SDL_Rect _sprite_pos){
        sprite_pos = _sprite_pos;
    }
    //****

    Speed get_speed(){
        return speed;
    }

    void set_speed(Speed _speed){
        speed.x = _speed.x;
        speed.y = _speed.y;
    }

   //************************


    /*
    * UPDATE FUNCTION
    * 
    * Called at each frame to update the ball status
    * 
    * Params : the window, the craft, the lvl
    * 
    * TO DO: change the craft collision for the object implementation
    * 
    */
    void update(SDL_Surface* _win_surf, int tmp_craft_x/*, CRAFT, LVL*/){
        //moving
        rect.x += speed.x;
        rect.y += speed.y;

        // left_right collision
        if ((rect.x < 1) || (rect.x > (_win_surf->w - 25)))
            speed.x *= -1;
        if ((rect.y < 1) || (rect.y > (_win_surf->h - 25)))
            speed.y *= -1;

        // bottom collision -> ded
        if (rect.y >(_win_surf->h - 25))
            ded = true;

        // craft collision
        if ((rect.x > tmp_craft_x) && (rect.x < tmp_craft_x+128) && (rect.y > _win_surf->h - 32 -20))
        {
            speed.y *= -1;
            ded = false;
        }

        //change color if ded
        if(ded)
            sprite_pos.y = 64; //RED
        else
            sprite_pos.y = 96; //GREEN
    }
    
    /*
    * DRAW FUNCTION
    * 
    * Called at each frame to draw the ball
    * 
    */
    void draw(SDL_Surface* _sprite_sheet, SDL_Surface* _win_surf){
        SDL_BlitSurface(_sprite_sheet, &sprite_pos, _win_surf, &rect);
    }

};

#endif //BALL_HPP