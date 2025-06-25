#include "creatMaze.h"

bool move(){
        // north dir
        if( !(abs(rot) % 4) ){
                if( ( pos >= size ) && walls[pos][1] ){
                        pos -= size;
                        pathindex++;
                        path[pos] = pathindex;
                        return true;
                }
        }
        // east dir
        else if( abs(rot) % 4 == 1 ){
                if( ((pos + 1) % size) && walls[pos+1][0] ){
                        pos += 1;
                        pathindex++;
                        path[pos] = pathindex;
                        return true;
                } 
        }
        // south dir
        else if( abs(rot) % 4 == 2 ){
                if( pos < ( size * ( size - 1 ) ) && walls[pos+size][1] ){
                        pos += size;
                        pathindex++;
                        path[pos] = pathindex;
                        return true;
                }
        }
        // west dir
        else{
                if( ( pos % size ) && walls[pos][0] ){
                        pos -= 1;
                        pathindex++;
                        path[pos] = pathindex;
                        return true;
                }
        }
        return  0;
}

void solveMazeRH(){
        path[0] = 1;
        rot = 1;
        while( pos != goal ){
                rot++;
                if( !move() ){
                        rot--;
                        if( !move() ){
                                rot--;
                                if(!move() ){
                                        rot--;
                                        move();
                                }
                        }
                }
                std::this_thread::sleep_for(std::chrono::nanoseconds(delay)); // delay for visuals
        }
}