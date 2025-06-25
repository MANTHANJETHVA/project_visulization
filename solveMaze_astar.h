#include "creatMaze.h"

int distance( int a , int b ){
        return (int)( abs( a % size - b % size ) + abs( ( ( a - a % size ) / size ) - ( ( b - b % size ) / size ) ) );
}

void adjecantemptywalls(){

        emptywallcnt = 0;
        for( int i = 0 ; i < 4 ; i++ ) emptywalls[i] = 0;

        //north wall
        if(pos >= size && walls[pos][1]){
                emptywalls[emptywallcnt] = -size;
                emptywallcnt++;
        }
        
        //east wall
        if( (pos + 1) % size != 0 && walls[pos + 1][0]){
                emptywalls[emptywallcnt] = 1;
                emptywallcnt++;
        }

        //south wall
        if( pos < size * (size - 1) && walls[pos + size][1] ){
                emptywalls[emptywallcnt] = size;
                emptywallcnt++;
        }
    
        //west wall
        if(pos % size != 0 && walls[pos][0]){
                emptywalls[emptywallcnt] = -1;
                emptywallcnt++;
        }

}

void calculate( int posi ){
        int g = mazewalls[pos][0] + 1;
        int h = distance(posi,goal);
        int f = g + h;

        if( mazewalls[posi][2] > f || mazewalls[posi][2] == 0 ){
                mazewalls[posi][0] = g;
                mazewalls[posi][1] = h;
                mazewalls[posi][2] = f;
                mazewalls[posi][4] = pos;
        }
}

void solveMazeAstar(){

        pos = 0;

        for( int i = 0 ; i < size*size ; i++ ) for( int j = 0 ; j < 5 ; j++ )
                mazewalls[i][j] = 0;
                
        mazewalls[pos][0] = 0;
        mazewalls[pos][1] = distance( pos , goal );
        mazewalls[pos][2] = mazewalls[pos][1];
        mazewalls[pos][3] = 0;

        while( pos != goal ){

                std::this_thread::sleep_for(std::chrono::nanoseconds(delay)); // dealay for making visuals 

                adjecantemptywalls();

                for( int i = 0 ; i < emptywallcnt ; i++ )
                        if( !mazewalls[pos + emptywalls[i]][3] )
                                calculate( pos + emptywalls[i] );

                int minf = size*size , minh = size*size , upcomingcell = start;

                for( int i = 0 ; i < size*size ; i++ ){

                        if( !mazewalls[i][3] && mazewalls[i][2] ){
                                
                                if( minf > mazewalls[i][2] ){
                                        minf = mazewalls[i][2];
                                        minh = mazewalls[i][1];
                                        upcomingcell = i;
                                }
                                else if( minf == mazewalls[i][2] && minh > mazewalls[i][1] ){
                                        minh = mazewalls[i][1];
                                        upcomingcell = i;
                                }

                        }

                }

                pos = upcomingcell;
                mazewalls[pos][3] = 1;

        }

        while( pos != start ){
                std::this_thread::sleep_for(std::chrono::nanoseconds(delay)); // delay for visuals

                path[pos] = -1;
                pos = mazewalls[pos][4];
        }

        path[start] = -1;
        pos = goal;

}