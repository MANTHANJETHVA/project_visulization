#include <GLFW/glfw3.h>
#include "creatMaze.h"
#include "solveMaze.h"
#include "solveMaze_astar.h"

int draw(){
        GLFWwindow* window;

        /* Initialize the library */
        if (!glfwInit())
                return -1;

        /* Create a windowed mode window and its OpenGL context */
        window = glfwCreateWindow(1200,1200, "Maze Solver", NULL, NULL);
        if (!window){
                glfwTerminate();
                return -1;
        }

        /* Make the window's context current */
        glfwMakeContextCurrent(window);

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window)){
                /* Render here */
                glClear(GL_COLOR_BUFFER_BIT);
                float gridSize = size;
                int maxPathIndex = 0;

                for(int j = 0; j < size; j++) for (int i = 0; i < size; i++){
                        // j is y
                        // i is x
                        int position = i + j * size;
                        int cpathIndex = path[i + size * j];

                        if(cpathIndex > maxPathIndex) maxPathIndex = cpathIndex;
                        if(position == pos) glColor3f(0, 1, 0);
                        else if(position == start) glColor3f(1, 0, 0);
                        else  if(cpathIndex == -1) glColor3f(1, 1, 0.4);
                        else if(mazeBlocks[position][3] != 0) glColor3f(0.7, 1, 0.7);
                        else if(mazeBlocks[position][2] != 0) glColor3f(0.6, 0.6, 1);
                        else if(cpathIndex > 0) glColor3f(1, 0.6, 0.6);
                        else glColor3f(1, 1, 1);

                        glBegin(GL_QUADS);

                        glVertex2f(-1 + (2 * i) / gridSize, 1 - (2 * j) / gridSize);
                        glVertex2f(-1 + (2 * i) / gridSize + 2 / gridSize, 1 - (2 * j) / gridSize);
                        glVertex2f(-1 + (2 * i) / gridSize + 2 / gridSize, 1 - ((2 * j) / gridSize) - 2 / gridSize);
                        glVertex2f(-1 + (2 * i) / gridSize, 1 - ((2 * j) / gridSize) - 2 / gridSize);

                        glEnd();

                        glColor3f(0, 0, 0);

                        //vertical walls
                        if (walls[i + j * size][0] == 0){
                                for(int l = 1; l < lineWidth; l++){
                                        glBegin(GL_LINES);
                                        glVertex2f(-1 + (2 * i) / gridSize + 0.001 * l, 1 - (2 * j) / gridSize);
                                        glVertex2f(-1 + (2 * i) / gridSize + 0.001 * l, 1 - ((2 * j) / gridSize) - 2 / gridSize);
                                        glEnd();
                                }   
                        }
                
                        //horizontal walls
                        if(walls[i + j * size][1] == 0){
                                for (int l = 1; l < lineWidth; l++){
                                        glBegin(GL_LINES);
                                        glVertex2f(-1 + (2 * i) / gridSize, 1 - (2 * j) / gridSize + 0.001 * l);
                                        glVertex2f(-1 + (2 * i) / gridSize + 2 / gridSize, 1 - (2 * j) / gridSize + 0.001 * l);
                                        glEnd();
                                }   
                        }
                }

                /* Swap front and back buffers */
                glfwSwapBuffers(window);

                /* Poll for and process events */
                glfwPollEvents();
        }

        glfwTerminate();

        return 0;
}

int main(void){
        srand(time(NULL));

        // for graphics GLFW 
        std::thread drawMaze(draw);

        // create maze through DFS
        createMaze();

        // diff methods of solving the maze
        solveMazeRH();
        solveMazeAstar();

        drawMaze.join();

        return 0;
}