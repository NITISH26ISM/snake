#include <iostream>
#include <cmath>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define world 1000
#define PI 3.1415926
#define cellSize 30
using namespace std;

static int animationPeriod = 50;
static int isAnimate = 0;
static int length = 3;
static int dir = 1;
static int food_x = 100;
static int food_y  = 100;
int snake[2500][2];

void drawFood(){

    	glBegin(GL_POLYGON);
    		glColor3f((rand()%255)/255.0,(rand()%255)/255.0,(rand()%255)/255.0);	glVertex2i(food_x,food_y);glVertex2i(food_x,food_y+cellSize);glVertex2i(food_x+cellSize,food_y+cellSize);glVertex2i(food_x+cellSize,food_y);

    	glEnd();

}



void render( void ){
    glClear(GL_COLOR_BUFFER_BIT);

    drawFood();
    cout<<"x: "<<snake[0][0]<<"   y :"<<snake[0][1]<<"  "<<"food_x: "<<food_x<<"  "<<"food_y"<<food_y<<endl;
    glPointSize(10);
        int ind = 0;
        while( ind<=length-1 ){
            glBegin(GL_POLYGON);
                glColor3f((rand()%255)/255.0,(rand()%255)/255.0,(rand()%255)/255.0);	glVertex2i(snake[ind][0],snake[ind][1]);glVertex2i(snake[ind][0],snake[ind][1]+cellSize);glVertex2i(snake[ind][0]+cellSize,snake[ind][1]+cellSize);glVertex2i(snake[ind][0]+cellSize,snake[ind][1]);
            glEnd();
            ind++;
        }
    glFlush();

}

void moveahead(void){
    switch (dir){
        case 1:
               for( int i = length-1; i > 0; i-- ){  snake[i][0] = snake[i-1][0]; snake[i][1] = snake[i-1][1];  } snake[0][0] =(snake[0][0]+1*cellSize+world)%world;break;
        case 2:
               for( int i = length-1; i > 0; i-- ){  snake[i][0] = snake[i-1][0]; snake[i][1] = snake[i-1][1];  } snake[0][1] =(snake[0][1]-1*cellSize+world)%world;break;
        case 3:
               for( int i = length-1; i > 0; i-- ){  snake[i][0] = snake[i-1][0]; snake[i][1] = snake[i-1][1];  } snake[0][0] =(snake[0][0]-1*cellSize+world)%world;break;
        case 4:
               for( int i = length-1; i > 0; i-- ){  snake[i][0] = snake[i-1][0]; snake[i][1] = snake[i-1][1];  } snake[0][1] =(snake[0][1]+1*cellSize+world)%world;break;
    }
    if( abs(snake[0][0]-food_x)<25 && abs(snake[0][1]-food_y)<25 ){cout<<"fuck breo!!"<<endl;
        length++;
        food_x = rand()%450;
        food_y = rand()%450;
        snake[length][0] = -1;
        snake[length][1] = -1;
        switch (dir){
        case 1:
            snake[length-1][0] = snake[length-2][0]-1*cellSize; snake[length-1][1] = snake[length-2][1];break;
        case 2:
            snake[length-1][1] = snake[length-2][1]+1*cellSize; snake[length-1][0] = snake[length-2][0]; break;
        case 3:
            snake[length-1][0] = snake[length-2][0]+1*cellSize; snake[length-1][1] = snake[length-2][1]; break;
        case 4:
            snake[length-1][1] = snake[length-2][1]-1*cellSize; snake[length-1][0] = snake[length-2][0]; break;
        }
    }
}

void animate(int value){
    if(isAnimate){
        moveahead();
        glutPostRedisplay();
        glutTimerFunc(animationPeriod, animate, 1);
    }

}


void keyInput(unsigned char key , int x, int y){
    switch(key){
    case 27:
        exit(0);
    case ' ':
        if(isAnimate) isAnimate = 0;
        else{
            isAnimate = 1;
            animate(1);
        }
        break;
    }
}


void specialKeyInput(int key , int x , int y ){
    if( key == GLUT_KEY_LEFT ){
        switch (dir){
        case 1:
            dir = 4; break;
        case 2:
            dir = 1; break;
        case 3:
            dir = 2; break;
        case 4:
            dir = 3; break;
        }
    }
    else if( key == GLUT_KEY_RIGHT ){
        switch (dir){
        case 1:
            dir = 2; break;
        case 2:
            dir = 3; break;
        case 3:
            dir = 4; break;
        case 4:
            dir = 1; break;
        }
    }
    glutPostRedisplay();
}


void setup(void){
	glClearColor(0.0,0.0,0.0,0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,1000,0.0,1000);
}


void printInteraction(void){
	cout<<"Interaciton:"<<endl;
	cout<<"hey welcome here!!"<<endl;
	cout<<"use space bar or pause the game {-_-} ___ "<<endl;
	cout<<"use arrow keys to control your snake (_;p) "<<endl;
}


int main( int argc , char **argv ){
    snake[0][0] = 25*cellSize;
    snake[0][1] = 25*cellSize;
    snake[1][0] = 24*cellSize;
    snake[1][1] = 25*cellSize;
    snake[2][0] = 23*cellSize;
    snake[2][1] = 25*cellSize;
    snake[3][0] = -1;
    snake[3][1] = -1;

    srand(time(NULL));
    printInteraction();
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_SINGLE | GLUT_RGBA );
    glutInitWindowSize( 500, 500 );
    glutInitWindowPosition( 100 , 100 );
    glutCreateWindow("snake play!!");
    setup();
    glutDisplayFunc(render);
    //glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    glutSpecialFunc(specialKeyInput);

    glutMainLoop();
}
