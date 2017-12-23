#include "function.h"
#include "glodal_types.h"
#include "list.h"


//-----------------------------------------------------------------------------
void init_window (GLFWwindow** window, GLuint WIDTH, GLuint HEIGHT, const char*Window_name)
{
    glfwInit();

    if (!glfwInit()){
            printf ( "Failed to initialize GLFW" );
            exit (0);
        }

    glewExperimental = GL_TRUE;

    if (!glewInit()){
        printf ( "Failed to initialize GLEW" );
        exit (0);
    }

    *window = glfwCreateWindow(WIDTH, HEIGHT, Window_name, NULL, NULL);
    glfwSetWindowPos(*window,0,20);


    if (! (*window))
    {
        glfwTerminate();
        exit (0);
    }

    glfwMakeContextCurrent((*window));
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glClearColor (0.2, 0.2, 0.2, 1);
    glOrtho (0, WIDTH, HEIGHT, 0, 0, 1);    // новий початок координат
    glMatrixMode (GL_MODELVIEW);

}

//-----------------------------------------------------------------------------
punit init_units  (punit Squeares, GLuint WIDTH, GLuint HEIGHT , int *rovs,int *column,
                   int *total_amount, GLfloat *Empty_cell)
{
            // генерація кооординат
    float x = 0;
    float y = 0;

    *rovs = ((HEIGHT - menuline) / (Side + borders));
    *column =   ((WIDTH) / (Side + borders));
    *total_amount = (*column) * (*rovs);

    if (Squeares == NULL)
         Squeares = (unit *) calloc ((*total_amount), sizeof (unit));

    for (int i = 0; i< (*rovs); ++i){
        for (int j = 0; j<(*column); ++j){
            int index = i*(*column) +j;

            Squeares [index].x1 = x;
            Squeares [index].y1 = y;
            Squeares [index].x2 = Squeares [index].x1 + Side;
            Squeares [index].y2 = Squeares [index].y1 + Side;

            Squeares [index].realstate = Empty;
            Squeares [index].nextstate = Empty;
            Squeares [index].color [0] = Empty_cell [0];
            Squeares [index].color [1] = Empty_cell [1];
            Squeares [index].color [2] = Empty_cell [2];

            x += Side + borders;
        }
        y += Side + borders;
        x = 0;
    }
    return Squeares;
}
//-----------------------------------------------------------------------------
pButton init_buttons (pButton Buttons, GLuint WIDTH, GLuint HEIGHT,
                      GLfloat *button_color,  GLfloat *text_color,  int button_sum)
{
        // генерація кооординат кнопок
    float x = 0;
    float y = HEIGHT - menuline;

    int button_width  =   ((WIDTH) / (button_sum));
    int button_border = (WIDTH - (button_width * button_sum ))/button_sum+1;

    Buttons = (Button*) calloc (button_sum, sizeof (Button));

    for (int i = 0; i<button_sum; ++i){

            Buttons[i].x1 = x;
            Buttons[i].y1 = y;
            Buttons[i].x2 = Buttons [i].x1 + button_width;
            Buttons[i].y2 = Buttons [i].y1 + button_width;
            Buttons[i].x_text = ((Buttons[i].x1+Buttons[i].x2)/2)-MinButHeight;
            Buttons[i].y_text = Buttons[i].y1+MinButHeight;

            Buttons[i].color [0] = button_color [0];
            Buttons[i].color [1] = button_color [1];
            Buttons[i].color [2] = button_color [2];

            Buttons[i].text_color [0] = text_color [0];
            Buttons[i].text_color [1] = text_color [1];
            Buttons[i].text_color [2] = text_color [2];

            x += button_width + button_border;
    }

    return Buttons;
}

//----------------------------------------------------------------------------------
pButton init_option (pButton Options_menu, GLuint WIDTH, GLuint HEIGHT,
                     GLfloat *button_color, GLfloat *text_color ,
                      int button_opition)
{
    float x = WIDTH - OptButtonWidth;
    float y = HEIGHT - (button_opition *(borders-1 +menuline));



    Options_menu = (Button*) calloc (button_opition, sizeof (Button));

    for (int i = 0; i<button_opition; ++i){

            Options_menu[i].x1 = x;
            Options_menu[i].y1 = y;
            Options_menu[i].x2 = WIDTH;
            Options_menu[i].y2 = Options_menu[i].y1+menuline;

            Options_menu[i].x_text = Options_menu[i].x1+ PaddingUp;
            Options_menu[i].y_text = Options_menu[i].y1+ PaddingLeft;

            Options_menu[i].color [0] = button_color [0];
            Options_menu[i].color [1] = button_color [1];
            Options_menu[i].color [2] = button_color [2];

            Options_menu[i].text_color [0] = text_color [0];
            Options_menu[i].text_color [1] = text_color [1];
            Options_menu[i].text_color [2] = text_color [2];

            y += menuline+ borders;
    }

    return Options_menu;

}
//------------------------------------------------------------------------------------
void init_saved_games (sList *List)
{


    FILE *pExport;
    sSaveGame *next = NULL;
    char temp;

    pExport = fopen ("/home/inspirion/LIFE/export", "r");
    if (pExport==NULL){
        printf (" init_saved_games export_csv: Error");
    return;
    }

    List->pHead = NULL;
    List->pLast = NULL;
    List->prevois = NULL;
    List->value = 0;

    while (fread (&temp, sizeof(char),1,pExport)) {
        if (temp == Point){

            next     = new_unit();
            List->value += 1;
            next->id     = List->value;
            fread (next->name, sizeof (char), Size, pExport );
            next->position = ftell (pExport);
            append (List, next);

        }
    }

    fclose(pExport );
}

//------------------------------------------------------------------------------------
void init_save_stage (sList *List,  GLfloat *button_color,  GLfloat *text_color,
                      Button init_button, GLuint HEIGHT)
{

    float height_button = init_button.y2-init_button.y1;

     if (List->value * height_button > HEIGHT){
         height_button = MinButHeight;
     }

    float x = init_button.x1 - (((OptButtonWidth))-borders);
    float y = init_button.y1 -  List->value * height_button;
    y = (y<0)? 1: y;

    sSaveGame *pt = NULL;
    pt = List->pHead;


    while (pt != NULL){

            pt->tack.x1 = x;
            pt->tack.x2 = pt->tack.x1 + OptButtonWidth-(borders);
            pt->tack.y1 = y;
            pt->tack.y2 = y+height_button;

            pt->tack.x_text = pt->tack.x1+PaddingUp;
            pt->tack.y_text = pt->tack.y1+PaddingLeft;

            pt->tack.color [0] = button_color [0];
            pt->tack.color [1] = button_color [1];
            pt->tack.color [2] = button_color [2];

            pt->tack.text_color [0] = text_color [0];
            pt->tack.text_color [1] = text_color [1];
            pt->tack.text_color [2] = text_color [2];
            y += menuline+ borders;

            y = pt->tack.y2 + borders;
            pt = pt->next;
    }

}


