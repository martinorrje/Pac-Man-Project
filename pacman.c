#include"game.h"
#include"helper_functions.h"

//TODO FIX COLLISIONS WITH THE MAP
void update_pacman(){
    int i, yPoint;
    int canMove = 1;
    //For each case in this switch statement, it is checked whether the next column of four pixels in the direciton of pacman is a wall or not.
    //If it is a wall, then pacman cannot move in that direction
    switch(pacmanDirection){
        case Right: {
            for(i = 0; i < 4; i++){
                if(mapPoints[pacmanY + i][pacmanX + 4]) {
                    canMove = 0;
                    break;
                } 
            } 

            if(canMove){
                pacman_anim_state = !pacman_anim_state;
                clear_entity(pacmanClosed, 12, pacmanX, pacmanY, display_buffer);
                pacmanX = (pacmanX + 1) % 128;
            }
            else{
                pacman_anim_state = 0;
            }

            break;
        } 

        case Left: {
            for(i = 0; i < 4; i++){
                if(mapPoints[pacmanY + i][pacmanX - 1]){
                    canMove = 0;
                    break;
                }     
            } 

            if(canMove){
                pacman_anim_state = !pacman_anim_state;
                clear_entity(pacmanClosed, 12, pacmanX, pacmanY, display_buffer);
                pacmanX--;
                if(pacmanX < -3) pacmanX += 128;
            }
            else{
                pacman_anim_state = 0;
            }
            break;
        }   
            
        case Up: {
            for(i = 0; i < 4; i++){
                if(mapPoints[pacmanY - 1][pacmanX + i]) {
                    canMove = 0;
                    break;
                }
            } 

            if(canMove){
                pacman_anim_state = !pacman_anim_state;
                clear_entity(pacmanClosed, 12, pacmanX, pacmanY, display_buffer);
                pacmanY = (pacmanY - 1) % 32;
            }
            else{
                pacman_anim_state = 0;
            }
            break;
        }
            
        case Down: {
            for(i = 0; i < 4; i++){
                if(mapPoints[pacmanY + 4][pacmanX + i]) {
                    canMove = 0;
                    break;
                }   
            } 

            if(canMove){
                pacman_anim_state = !pacman_anim_state;
                clear_entity(pacmanClosed, 12, pacmanX, pacmanY, display_buffer);
                pacmanY = (pacmanY + 1) % 32;
            }
            else{
                pacman_anim_state = 0;
            }
            break;
        }
    }
}