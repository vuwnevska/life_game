#include "glodal_types.h"
#include "list.h"
#include "function.h"

//--------------------------------------------------------------------------------
void change_generation (punit Squeares, int *total_amount, GLfloat *Live_cell, GLfloat *Dead_cell)
{
    for (int i = 0; i< *total_amount; i++){

        switch (Squeares[i].nextstate) {
        case Newborn:{
            Squeares[i].realstate = Live;
            Squeares[i].color [0] = Live_cell [0];
            Squeares[i].color [1] = Live_cell [1];
            Squeares[i].color [2] = Live_cell [2];

            break;
        }
        case Will_die:{
            Squeares[i].realstate = Dead;
            Squeares[i].color [0] = Dead_cell [0];
            Squeares[i].color [1] = Dead_cell [1];
            Squeares[i].color [2] = Dead_cell [2];
            break;
        }

        default:
            break;
        }
        Squeares[i].nextstate = Empty;
    }
}

void SelectBut ( Button *Item, float r, float g, float b)
{
    Item->color [0] = r;
    Item->color [1] = g;
    Item->color [2] = b;
}

//--------------------------------------------------------------------------------
char count_pattern (punit Squeares,  int i, int j, int column, int rovs)
{

    unit cell = {0};
    int count = 0;
    int index = 0;

               //-----------------upper Cell------------------------
       if (i>0){
              if (j>0){
                  index = (i*column+j)-column - 1;
                  cell.realstate = Squeares[index].realstate;
                  if (cell.realstate == Live)
                        count++;
                }

              index = (i*column+j)-column;
              cell.realstate = Squeares[index].realstate;
                   if (cell.realstate == Live)
                       count++;

               if (j<column-1){
                   index = (i*column+j)-column + 1;
                   cell.realstate = Squeares[index].realstate;
                   if (cell.realstate == Live)
                       count++;
                 }
         }

               //-----------------on same line---------------------------
       if (j!=0){
           index = (i * column + j) - 1;
           cell.realstate = Squeares[index].realstate;
           if (cell.realstate == Live)
               count++;

       }
       index = (i * column + j) + 1;
            cell.realstate =Squeares[index].realstate;
        if (cell.realstate == Live){
            count++;
        }

               //----------------under Cell-------------------------------
        if (i < rovs-1){
             if (j!=0){
                 index = (i * column+j)+ column - 1;
                 cell.realstate =Squeares[index].realstate;
                 if (cell.realstate == Live)
                     count++;
             }

             index = (i * column + j)+ column;
            cell.realstate =Squeares[index].realstate;
            if (cell.realstate == Live)
                count++;

            if (j<column-1){
                index = (i * column + j)+ column + 1;
                cell.realstate =Squeares[index].realstate;
                if (cell.realstate == Live)
                count++;
              }
        }
        return count;
}

//--------------------------------------------------------------------------------
void draw_unit (int i, punit Item)
{
    glColor3fv ( Item[i].color);

    glRectf (Item[i].x1,
             Item[i].y1,
             Item[i].x2,
             Item[i].y2
             );
}
//-----------------------------------------------------------------------------
void draw_option_list   (sList* List)
{
     sSaveGame *pt = List->pHead;

     while (pt != NULL){

         glColor3fv ( pt->tack.color);

         glRectf (pt->tack.x1,
                  pt->tack.y1,
                  pt->tack.x2,
                  pt->tack.y2
                  );
         DrawOptLisText(pt);
         pt = pt->next;
     }
}

//-----------------------------------------------------------------------------
void draw_option_menu   ( pButton Item, int amount)
{
    for (int i =0; i < amount-1; ++i){
    glColor3fv ( Item[i].color);
    glRectf (Item[i].x1,
             Item[i].y1,
             Item[i].x2,
             Item[i].y2
             );
    }

}
//-----------------------------------------------------------------------------
void draw_text_menu (pButton Menu_buttons, char** Menu_name, int count)
{

   glColor3fv(Menu_buttons->text_color);

   for (int i =0; i<count; ++i){
       glRasterPos2f (Menu_buttons[i].x_text, Menu_buttons[i].y_text);
       int j=0;
       while (Menu_name [i][j] != '\0') {
           glutBitmapCharacter (GLUT_BITMAP_TIMES_ROMAN_24, Menu_name [i][j]);
           j++;
       }

   }
}
//-----------------------------------------------------------------------------
void DrawOptLisText   (sSaveGame *pt)
{

         glColor3fv(pt->tack.text_color);
             glRasterPos2f (pt->tack.x_text, pt->tack.y_text);
             for (int i=0; i< Size; ++i){
             glutBitmapCharacter (GLUT_BITMAP_HELVETICA_18, pt->name[i]);
     }
}
//-----------------------------------------------------------------------------
void choose_option (pButton Options_menu, eMenuOptionState *gameOption, double x, double y)
{

    if (Options_menu[Pattern].x1 <= x && x <= Options_menu[Pattern].x2)
        if (Options_menu[Pattern].y1 <= y && y <= Options_menu[Pattern].y2){
            *gameOption = Pattern;
            return;
        }

    if (Options_menu[Export_menu].x1 <= x && x <= Options_menu[Export_menu].x2)
        if (Options_menu[Export_menu].y1 <= y && y <= Options_menu[Export_menu].y2){
            *gameOption = Export_menu;
            return;
        }

    if (Options_menu[Save].x1 <= x && x <= Options_menu[Save].x2)
        if (Options_menu[Save].y1 <= y && y <= Options_menu[Save].y2){
            *gameOption = Save;
            return;
        }

    if (Options_menu[About].x1 <= x && x <= Options_menu[About].x2)
        if (Options_menu[About].y1 <= y && y <= Options_menu[About].y2){
            *gameOption = About;
            return;
        }

    if (Options_menu[Return].x1 <= x && x <= Options_menu[Return].x2)
        if (Options_menu[Return].y1 <= y && y <= Options_menu[Return].y2){
            *gameOption = Return;
            return;
        }
}

//------------------------------------------------------------------------
void define_time (char* buffer)
{

    time_t rawtime;
    struct tm * timeinfo;
    time( &rawtime );
    timeinfo = localtime( &rawtime );
    strftime (buffer,Size,"%X_%x",timeinfo);
}
//---------------------------------------------------------------------
void Print_About (GLuint Height, GLuint Width)
{

    sSaveGame new_win;
    int i = 0;
    int j = 0;

    char * Text[] = {
        " ",
        "The Game of Life is a cellular-automaton,  developed by John Conway in 1970.",
        "The game is played on an  grid of square cells, and its evolution is only determined by its initial state.",
        "The rules of the game are simple, and describe the evolution of the grid:",
        "   Birth: a cell that is dead at time t will be alive at time t + 1 if exactly 3 of its eight neighbors were alive at time t.",
        "   Death: a cell can die by:",
        "   Overcrowding: if a cell is alive at time t + 1 and 4 or more of its neighbors",
        "are also alive at time t, the cell will be dead at time t + 1",
        "   Exposure: If a live cell at time t has only 1 live neighbor or no live neighbors, it will be dead at time t + 1.",
        "   Survival: a cell survives from time t to time t + 1 if and only if 2 or 3 of its neighbors are alive at time t."
        " ",
        " ",
        "         MENU OPTION",
        " ",
        "  Run - option starts counting of the next cell stages according to the rules.",
        "  Step - counts only one next life stage of the cells",
        "  Stop - stops processing of life – death change.",
        "  Clear - brings all cells into the  initial stage.",

        "  Exit - ends the program (also keyboard Esc ).",
        "  Menu - opens additional services.",
        "  Save - allows to save the state of all cells, and add it  to the  overall list in Pattern. The name of the saved stage will consist of ",
        "current data time. To delete the record you need to choose appropriate game stage and press Delete on your keyboard",
        "  Export - allows to  save a current stage of the  field in CSV format, all live cells in the moment will be marked  as asterisks.",
        "  Return  to game - back to the  main window."
    };

    new_win.tack.x1= Width - (Width - menuline);
    new_win.tack.y1= 10;
    new_win.tack.x2= Width - menuline;
    new_win.tack.y2 = Height - (menuline*2);


    new_win.tack.x_text = new_win.tack.x1;
    new_win.tack.y_text = new_win.tack.y1;

    new_win.tack.color[0] = 1.0;
    new_win.tack.color[1] = 1.0;
    new_win.tack.color[2] = 1.0;


    draw_option_menu   ( &new_win.tack, 2);

    glColor3f(0.3, 0.5, 0.3);
    while (i != 23){

        new_win.tack.y_text += MinButHeight;

        glRasterPos2f (new_win.tack.x_text,
                       new_win.tack.y_text);
        while (Text[i][j] != '\0'){
        glutBitmapCharacter (GLUT_BITMAP_HELVETICA_18, Text[i][j]);
        ++j;
        }
        j=0;
        ++i;
    }

}
