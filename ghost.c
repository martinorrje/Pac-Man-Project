#include"game.h"

void update_ghost(struct Ghost* ghost){
    //Each of these four variables below denote the distance from ghost's current position to pacman's position, calculated using pythagora's theorem
    float rightDist, leftDist, upDist, downDist;
    int canMove;
    int i;

    if(ghost->dir != Left && ghost->pos.x < 123){
        canMove = 1;
        for(i = 0; i < 4; i++){
            if(mapPoints[ghost->pos.y + i][ghost->pos.x + 5] == 1) {
                canMove = 0;
                break;
            } 
        } 
        if(canMove){
            rightDist = square_root((float)power(ghost->target.x - (ghost->pos.x + 1), 2) + (float)power(ghost->target.y - ghost->pos.y, 2));
        }
        else{
            rightDist = 10000;
        }
    }
    else rightDist = 10000;
        
    if(ghost->dir != Right && ghost->pos.x > 0){
        canMove = 1;
         for(i = 0; i < 4; i++){
            if(mapPoints[ghost->pos.y + i][ghost->pos.x - 1] == 1) {
                canMove = 0;
                break;
            } 
        } 
        if(canMove){
            leftDist = square_root((float)power(ghost->target.x - (ghost->pos.x - 1), 2) + (float)power(ghost->target.y - ghost->pos.y, 2));
        }
        else{
            leftDist = 10000;
        }
    }
    else leftDist = 10000;

    if(ghost->dir != Down){
        canMove = 1;
        for(i = 0; i < 5; i++){
            if(mapPoints[ghost->pos.y - 1][ghost->pos.x + i] == 1) {
                canMove = 0;
                break;
            } 
        } 
        if(canMove){
            upDist = square_root((float)power(ghost->target.x - ghost->pos.x, 2) + (float)power(ghost->target.y - (ghost->pos.y - 1), 2));
        }
        else{
            upDist = 10000;
        }
    }
    else upDist = 10000;

    if(ghost->dir != Up){
        canMove = 1;
        for(i = 0; i < 5; i++){
            if(mapPoints[ghost->pos.y + 4][ghost->pos.x + i] == 1) {
                canMove = 0;
                break;
            } 
        } 
        if(canMove){
            downDist = square_root((float)power(ghost->target.x - ghost->pos.x, 2) + (float)power(ghost->target.y - (ghost->pos.y + 1), 2));
        }
        else{
            downDist = 10000;
        }
    }
    else downDist = 10000;

    if(upDist == 10000 && downDist == 10000 && rightDist == 10000 && leftDist == 10000){        //Ghost is stuck in corner, turn around (this never happens after I fixed bug)
        switch(ghost->dir){
            case Up:
                ghost->dir = Down;
                ghost->pos.y++;
                break;
            case Down:
                ghost->dir = Up;
                ghost->pos.y--;
                break;
            case Right:
                ghost->dir = Left;
                ghost->pos.x--;
                break;
            case Left:
                ghost->dir = Right;
                ghost->pos.x++;
                break;
        }
        return;
    }

    if(upDist <= rightDist && upDist <= leftDist && upDist <= downDist){
        ghost->dir = Up;
        ghost->pos.y--;
        if(0){
            game_over = 1;
        }
    }
    else if (downDist <= upDist && downDist <= leftDist && downDist <= rightDist){
        ghost->dir = Down;
        ghost->pos.y++;
        if(0){
            game_over = 1;
        }
    }
    else if(rightDist <= leftDist && rightDist <= upDist && rightDist <= downDist){
        ghost->dir = Right;
        ghost->pos.x++;
        if(0){
            game_over = 1;
        }
    }
    else{
        ghost->dir = Left;
        ghost->pos.x--;
        if(0){
            game_over = 1;
        }
    }

    //Collision detection
    if (ghost->pos.x - pacmanX <= 2 && pacmanX - ghost->pos.x <= 2 && ghost->pos.y - pacmanY <= 2 && pacmanY - ghost->pos.y <= 2){
        if(frightenedMode){
            score += 100;
            ghost->pos.x = 62;
            ghost->pos.y = 1;
        }else{
            game_over=1;
        }
    }
}