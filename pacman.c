#include"game.h"
#include"helper_functions.h"

//Eats food located at position (x,y)
void eat_food(int x, int y){
    int i, j;
    for(i = y-1; i <= y + 1; i++){
        for(j = x - 1; j <= x + 1; j++){
            mapPoints[i][j] = 0;
            clear_buffer_pixel(j, i, display_buffer);
        }
    }
    score++;
}

//TODO: add frightened mode when super food is eaten
void eat_superfood(int x, int y){
    int i, j;
    if(x == 25){
        for(i = 1; i <= 4; i++){
            for(j = 25; j <= 28; j++){
                mapPoints[i][j] = 0;
                clear_buffer_pixel(j, i, display_buffer);
            }
        }
        score += 10;
    }
    else if(x == 102){
        for(i = 1; i <= 4; i++){
            for(j = 99; j <= 102; j++){
                mapPoints[i][j] = 0;
                clear_buffer_pixel(j, i, display_buffer);
            }
        }
        score += 10;
    }
    else if(y == 17 || x == 7){
        for(i = 17; i <= 20; i++){
            for(j = 4; j <= 7; j++){
                mapPoints[i][j] = 0;
                clear_buffer_pixel(j, i, display_buffer);
            }
        }
        score += 10;
    }
    else if(x == 92 || x == 95){
        for(i = 18; i <= 21; i++){
            for(j = 92; j <= 95; j++){
                mapPoints[i][j] = 0;
                clear_buffer_pixel(j, i, display_buffer);
            }
        }
        score += 10;
    }
    else if(x == 30 || y == 15){
        for(i = 12; i <= 15; i++){
            for(j = 27; j <= 30; j++){
                mapPoints[i][j] = 0;
                clear_buffer_pixel(j, i, display_buffer); 
            }
        }
        score += 10;
    }
}

void update_pacman(){
    int i, yPoint;
    int canMove = 1;
    //For each case in this switch statement, it is checked whether the next column of four pixels in the direciton of pacman is a wall or not.
    //If it is a wall, then pacman cannot move in that direction
    switch(pacmanDirection){
        case Right: {
            for(i = 0; i < 4; i++){
                if(mapPoints[pacmanY + i][pacmanX + 4] == 1) {
                    canMove = 0;
                    break;
                } 
                else if(mapPoints[pacmanY + i][pacmanX + 4] == 2){
                    eat_food(pacmanX+4, pacmanY+i);
                }
                else if(mapPoints[pacmanY + i][pacmanX + 4] == 3){
                    eat_superfood(pacmanX+4, pacmanY+i);
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
                if(mapPoints[pacmanY + i][pacmanX - 1] == 1){
                    canMove = 0;
                    break;
                }     
                else if(mapPoints[pacmanY+i][pacmanX-1] == 2){
                    eat_food(pacmanX-1, pacmanY+i);
                }
                else if(mapPoints[pacmanY+i][pacmanX-1] == 3){
                    eat_superfood(pacmanX-1, pacmanY+i);
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
                if(mapPoints[pacmanY - 1][pacmanX + i] == 1) {
                    canMove = 0;
                    break;
                }
                else if(mapPoints[pacmanY-1][pacmanX+i] == 2){
                    eat_food(pacmanX+i, pacmanY-1);
                }
                else if(mapPoints[pacmanY-1][pacmanX+i] == 3){
                    eat_superfood(pacmanX+i, pacmanY-1);
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
                if(mapPoints[pacmanY + 4][pacmanX + i] == 1) {
                    canMove = 0;
                    break;
                }   
                else if(mapPoints[pacmanY+4][pacmanX+i] == 2){
                    eat_food(pacmanX+i, pacmanY+4);
                }
                else if(mapPoints[pacmanY+4][pacmanX+i] == 3){
                    eat_superfood(pacmanX+i, pacmanY+4);
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