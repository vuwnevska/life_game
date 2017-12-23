#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "glodal_types.h"
#include "function.h"
#include "list.h"
#include "import_export.h"


char * Menu_name [End_Menu] = {
    "Run",
    "Stop",
    "Random",
    "Step",
    "Clear",
    "Exit",
    "Menu"
};

char * Menu_options [End_Menu_info] = {
    "Pattern",
    "Export",
    "Save",
    "About",
    "Return to game"
};

GLfloat  Empty_cell     [3]=  {0.89, 0.89, 0.89};
GLfloat  Newborn_cell   [3]=  {0.63, 0.9, 0.57};
GLfloat  Live_cell      [3]=  {0.9, 0.3, 0.3};
GLfloat  Dead_cell      [3]=  {0.7, 0.7, 0.7};
GLfloat  Will_die_cell  [3]=  {0.4, 0.3, 0.5};
GLfloat  button_color   [3]=  {0.1, 0.1, 0.1};
GLfloat  text_but_color [3]=  {0.4, 0.7, 0.3};


static punit  Squeares      = NULL;
static pButton Menu_buttons = NULL;
static pButton Options_menu = NULL;

static int    one_step;
int           column;
int           rovs;
int           total_amount;
double        x_mouse_pos;
double        y_mouse_pos;

int    g_scr_width     = 0;
int    g_scr_height    = 0;
float  g_w_ratio       = 0.f;
float  g_h_ratio       = 0.f;

char          buffer[20];

eMenuOptionState gameOption;
sList       List;
eMenustate       Game;
GLFWwindow  *window;
char        *Window_name = "LIFE";
const GLuint WIDTH       = 1200;
const GLuint HEIGHT      = 720;

const int    button_sum      = End_button+1;
const int    button_opition  = End_Menu_info+1;

//----------------FUNCTION-----------------------------------------
void display_screen          (void);
void change_color            (double, double);
void change_game_stage       (double, double);
void resize                  (GLFWwindow*, int, int);

void mouse_callback          (GLFWwindow*, int, int, int);
void mouse_position_callback (GLFWwindow*, double, double);

void key_callback            (GLFWwindow* , int, int, int, int);
void put_random_cell         (punit);

void play_game (void);



//----------------MAIN-----------------------------------------
int main(int argc, char **argv)
{

    init_window (&window, WIDTH, HEIGHT, Window_name);

    Options_menu = init_option (Options_menu, WIDTH, HEIGHT, button_color, text_but_color,
                                button_opition);

    Squeares = init_units (Squeares, WIDTH, HEIGHT, &rovs, &column, &total_amount,
                           Empty_cell);

    Menu_buttons = init_buttons (Menu_buttons, WIDTH, HEIGHT, button_color,text_but_color,
                                 End_Menu);

    init_saved_games (&List);
    init_save_stage (&List, button_color, text_but_color, Options_menu[Pattern], HEIGHT);

    Game       = Default;
    gameOption = End_Menu_info;
    glfwSetWindowPos(window,0,15);

    glutInit( & argc, argv );

    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        switch (Game) {
                case Default:{
                    display_screen ();
                    break;
                }
                case Run:{
                    change_generation (Squeares, &total_amount, Live_cell, Dead_cell);
                    play_game   ();
                    display_screen ();
                    usleep (90000);
                    break;
                }
                case Stop:{
                    display_screen ();
                    break;
                }
                case Random:{
                    Squeares = init_units (Squeares, WIDTH, HEIGHT,
                                           &rovs, &column, &total_amount,
                                           Empty_cell);
                    put_random_cell (Squeares);
                    display_screen ();
                    Game = Default;
                    break;
                }

                case Step:{
                    if (one_step == 1){
                        change_generation (Squeares, &total_amount, Live_cell, Dead_cell);
                        play_game   ();
                        display_screen ();
                        one_step = 0;
                    }
                    display_screen ();
                    break;
                }

                case Clear:{
                    Squeares = init_units (Squeares, WIDTH, HEIGHT, &rovs, &column,
                                           &total_amount, Empty_cell);
                    display_screen ();
                    Game = Default;
                    break;
                }

                case Menu:{
                display_screen ();
                draw_option_menu (Options_menu, button_opition);
                draw_text_menu (Options_menu, Menu_options, End_Menu_info);

                    switch (gameOption) {
                        case Pattern :{
                        if (List.value != 0){
                            draw_option_list (&List);

                            if (List.current != NULL){

                                Squeares = init_units (Squeares, WIDTH, HEIGHT,&rovs,
                                                       &column, &total_amount,Empty_cell );
                                count_save (List.current, Squeares, total_amount);
                                update_colors (Squeares, &total_amount, Dead_cell,Live_cell);

                                if (show_choosen ( &List, x_mouse_pos / g_w_ratio,
                                                 y_mouse_pos / g_h_ratio)){
//                                    remember previos for bring it in initail color
                                    List.prevois = List.current;
                                }

                            }
                        }
                           break;
                        }
                        case Export_menu: {
                        export_csv_struct (Squeares, rovs, column);
                           break;
                        }
                        case Save: {
                        define_time (buffer);
                        export_csv (Squeares, total_amount, buffer);

//                        recount list of seving games
                        init_saved_games (&List);
                        init_save_stage (&List, button_color, text_but_color,
                                         Options_menu[Pattern],  HEIGHT);
                        Game = Menu;
                        gameOption = End_Menu_info;
                           break;
                        }
                        case About: {
                        Print_About (HEIGHT, WIDTH);

                           break;
                        }
                        case Return: {
                        Game = Default;
                        gameOption = End_Menu_info;
                           break;
                        }
                    case End_Menu_info: {
                       break;
                        }
                      }

                    break;
                }
                case End_game:{
                 glfwSetWindowShouldClose(window, GL_TRUE);
                    break;
                }
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
        usleep (10);
    }
    glfwTerminate();
    return 0;
}
//-----------------------------------------------------------------------------
void resize  ( GLFWwindow* window, int w, int h)
{

    glfwGetFramebufferSize(window, &g_scr_width, &g_scr_height);
    glViewport(0, 0, g_scr_width, g_scr_height);
    g_w_ratio = (float)g_scr_width  / (float) WIDTH;
    g_h_ratio = (float)g_scr_height / (float) HEIGHT;

}
//-----------------------------------------------------------------------------
void change_color ( double x, double y)
{

        for (int i = 0;  i< total_amount; ++i){
            if (Squeares[i].x1 <= x && x <= Squeares[i].x2){
                if (Squeares[i].y1 <= y && y <= Squeares[i].y2){
                    if (Squeares [i].realstate == Empty
                        || Squeares [i].realstate == Dead){
                        Squeares [i].realstate = Live;
                        Squeares [i].color [0] = Live_cell [0];
                        Squeares [i].color [1] = Live_cell [1];
                        Squeares [i].color [2] = Live_cell [2];
                    }
                    else {
                        Squeares [i].realstate = Empty;
                        Squeares [i].color [0] = Empty_cell [0];
                        Squeares [i].color [1] = Empty_cell [1];
                        Squeares [i].color [2] = Empty_cell [2];
                    }
                }
            }
        }

}
//-----------------------------------------------------------------------------
void change_game_stage (double x, double y)
{

    if (Menu_buttons[Run_button].x1 <= x && x <= Menu_buttons[Run_button].x2)
        if (Menu_buttons[Run_button].y1 <= y && y <= Menu_buttons[Run_button].y2){
            Game = Run;
            gameOption = End_Menu_info;
            return;
        }

    if (Menu_buttons[Stop_button].x1 <= x && x <= Menu_buttons[Stop_button].x2)
        if (Menu_buttons[Stop_button].y1 <= y && y <= Menu_buttons[Stop_button].y2){
            Game = Default;
            gameOption = End_Menu_info;
            return;
        }

    if (Menu_buttons[Random_button].x1 <= x && x <= Menu_buttons[Random_button].x2)
        if (Menu_buttons[Random_button].y1 <= y && y <= Menu_buttons[Random_button].y2){
            Game = Random;
            gameOption = End_Menu_info;
            return;
        }

    if (Menu_buttons[Step_button].x1 <= x && x <= Menu_buttons[Step_button].x2)
        if (Menu_buttons[Step_button].y1 <= y && y <= Menu_buttons[Step_button].y2){
            Game = Step;
            gameOption = End_Menu_info;
            one_step = 1;
            return;
        }

    if (Menu_buttons[Menu_button].x1 <= x && x <= Menu_buttons[Menu_button].x2)
        if (Menu_buttons[Menu_button].y1 <= y && y <= Menu_buttons[Menu_button].y2){
            Game = Menu;
            gameOption = End_Menu_info;
            return;
        }

    if (Menu_buttons[Clear_button].x1 <= x && x <= Menu_buttons[Clear_button].x2)
        if (Menu_buttons[Clear_button].y1 <= y && y <= Menu_buttons[Clear_button].y2){
            Game = Clear;
            gameOption = End_Menu_info;
            return;
        }

    if (gameOption != Pattern)
    if (Menu_buttons[End_button].x1 <= x && x <= Menu_buttons[End_button].x2)
        if (Menu_buttons[End_button].y1 <= y && y <= Menu_buttons[End_button].y2){
            Game = End_game;
            gameOption = End_Menu_info;
            return;
        }
}
//-----------------------------------------------------------------------------
void mouse_position_callback (GLFWwindow* window, double x, double y)
{

    x_mouse_pos = x;
    y_mouse_pos = y;
}

//-----------------------------------------------------------------------------
void mouse_callback (GLFWwindow* window, int but, int act, int mode)
{

    glfwGetCursorPos(window, &x_mouse_pos, &y_mouse_pos);
    double ix = ((float)x_mouse_pos / g_w_ratio);
    double iy = ((float)y_mouse_pos / g_h_ratio);

//    if mouse button push check all the buttons on screen

    if (act ==1){

        if(Game == Menu){
            choose_option      (Options_menu, &gameOption, ix, iy);
            find_list_position (&List, ix, iy);
            change_game_stage  (ix, iy);
            return;
        }

        else {
            change_color      (ix, iy);
            change_game_stage (ix, iy);
        return;
        }
    }
}


//-----------------------------------------------------------------------------
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_DELETE && action == GLFW_PRESS && gameOption == Pattern){
            ReWriteFile (&List, List.current);

//        if deleted some  elemen, and its not last element in list counted the list from beginig
        if (List.pHead != NULL){
            delete_stage (&List, List.current);
            init_saved_games (&List);
            init_save_stage (&List, button_color, text_but_color,
                             Options_menu[Pattern], HEIGHT);
        }
    }

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}
//-----------------------------------------------------------------------------
void display_screen ()
{
    glfwSetWindowSizeCallback (window, resize);
    glfwSetKeyCallback (window, key_callback );
    glfwSetMouseButtonCallback (window, mouse_callback);

    for(int i =0; i<total_amount; ++i)
        draw_unit (i, Squeares);

    draw_option_menu  ( Menu_buttons, End_Menu+1);
    draw_text_menu    (Menu_buttons, Menu_name, End_Menu);
}
//-----------------------------------------------------------------------------
void play_game (void)
{

    unsigned char amount = 0;
    unsigned int  index = 0;

    for (int i = 0; i < rovs; i++){
        for (int j=0; j < column; j++){

           amount = count_pattern (Squeares,i,j, column, rovs);
           index = i*column +j;

            switch (Squeares [index].realstate) {
            case Live:{
                if (amount == Birth || amount == StillAlive)
                    break;
                else{
                    Squeares[index].nextstate = Will_die;
                    Squeares [index].color [0] = Will_die_cell [0];
                    Squeares [index].color [1] = Will_die_cell [1];
                    Squeares [index].color [2] = Will_die_cell [2];}
                break;
            }
            case Empty:
            case Dead :{
                if (amount == Birth){
                    Squeares [index].nextstate = Newborn;
                    Squeares [index].color [0] = Newborn_cell [0];
                    Squeares [index].color [1] = Newborn_cell [1];
                    Squeares [index].color [2] = Newborn_cell [2];
                }
                break;
            }
            default:
                break;
            }
        }
    }
}
//---------------------------------------------------------------------------------
void put_random_cell (punit Array)
{
    int amount = 0;
    int index  = 0;
    int size = rovs*column;

    srand (time(0));
    amount = rand() % size;

    while (amount) {
        index = rand() %size;
        if (Array[index].realstate == Empty){
            Array[index].realstate = Live;
            Array[index].color[0] = Live_cell[0];
            Array[index].color[1] = Live_cell[1];
            Array[index].color[2] = Live_cell[2];
            amount--;
        }
    }
}

