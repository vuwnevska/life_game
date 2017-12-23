#ifndef INIT_DATA_H
#define INIT_DATA_H
#include "glodal_types.h"


void init_window        (GLFWwindow**, GLuint, GLuint, const char*);
punit init_units        (punit, GLuint, GLuint, int *,int *, int *, GLfloat*);
pButton init_buttons    (pButton, GLuint, GLuint, GLfloat *, GLfloat *, int);
pButton init_option     (pButton, GLuint, GLuint, GLfloat *, GLfloat *, int);

void change_generation  (punit, int *, GLfloat *, GLfloat *);
char count_pattern      (punit, int, int, int, int);

void draw_menu          (int,pButton);
void draw_option_menu   (pButton, int);
void draw_unit          (int, punit);
void print_string       (GLuint, char*);

void choose_option      (pButton, eMenuOptionState *, double, double);
void draw_text_menu     (pButton, char**, int);

void define_time        (char* );
void update_colors      (punit, int*, GLfloat*, GLfloat*);
void saved_games        ();
void init_saved_games   (sList*);
void init_save_stage    (sList*, GLfloat*,GLfloat *, Button, GLuint);
void draw_option_list   (sList*);
void SelectBut          ( Button*, float, float, float);
void DrawOptLisText     (sSaveGame*);

void Print_About (GLuint, GLuint);


#endif // INIT_DATA_H

