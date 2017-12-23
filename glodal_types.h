#ifndef GLODAL_TYPES
#define GLODAL_TYPES
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <X11/Intrinsic.h>    /* Display, Window */
#include <GL/glx.h>           /* GLXContext */

#define OptButtonWidth 180  // width of menu buttons
#define MinButHeight 25     // height of menu buttons
#define Size        18      // name's lenght of save game
#define Point       35      // delimiter in file with save game
#define PaddingUp   5       // pading of text in buttons
#define PaddingLeft 20      // pading of text in buttons
#define borders     1       // border beside cell and buttons
#define menuline    35      // height of bottom menu line
#define Side        10      // side of cells
#define StillAlive  2
#define Birth       3


typedef enum
{
    Empty = 0,
    Newborn,
    Live ,
    Dead,
    Will_die,
    End_Field
} elifestate;

typedef enum
{
    Default,
    Run  ,
    Stop,
    Random,
    Step ,
    Clear,
    Menu,
    End_game
} eMenustate;

typedef enum
{
    Run_button  ,
    Stop_button,
    Random_button ,
    Step_button  ,
    Clear_button ,
    End_button,
    Menu_button ,
    End_Menu
} eMenuButState;

typedef enum
{
    Pattern,
    Export_menu,
    Save,
    About,
    Return,
    End_Menu_info
} eMenuOptionState;


typedef struct square {
    GLfloat color [3];
    GLfloat x1 ;
    GLfloat y1 ;
    GLfloat x2 ;
    GLfloat y2 ;
    char realstate ;
    char nextstate ;
} unit, *punit;

typedef struct but {
    GLfloat color [3];
    GLfloat text_color [3];
    GLfloat x1 ;
    GLfloat y1 ;
    GLfloat x2 ;
    GLfloat y2 ;
    GLfloat x_text ;
    GLfloat y_text ;
} Button, *pButton;

typedef struct games {
    int    id;
    unsigned char  name [Size];
    struct games *next;
    struct games *prev;
    Button tack;
    long long position;
}sSaveGame;

typedef struct {
    sSaveGame *pHead;
    sSaveGame *pLast;
    sSaveGame *current;
    sSaveGame *prevois;
    int value;
} sList;


#endif // GLODAL_TYPES

