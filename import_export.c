#include "import_export.h"

//-----------------------------------------------------------------------------
void export_csv_struct (punit Squeares, int rovs, int column)
{
    FILE *pExport;
    char sign =' ';

//     delimiters in accordance to CSV format
    char text_delimiter = 0x2C;
    char end_string     = 0x0A;

//    pExport = fopen ("/home/inspirion/Programming/C_CPP/C/Life_field.csv", "w+");
    pExport = fopen ("/home/inspirion/LIFE/Life_field.csv", "w+");
    if (pExport==NULL)
        printf ("LIfe_field_csv: Error" );

            for (int i=0; i< rovs ; ++i){
                for (int j = 0; j<column; ++j){

                fprintf (pExport, "%c%c", sign = (Squeares [i*column+j].realstate == Live )?
                            '*': ' ', text_delimiter);
                }
                fprintf (pExport, "%c", end_string);
            }

    fclose(pExport );
}
//------------------------------------------------------------------------
void count_save (sSaveGame *stage, punit Squeares, int total_amount)
{

    FILE *pExport;
    char temp;


//    pExport = fopen ("/home/inspirion/Programming/C_CPP/C/export", "r");
    pExport = fopen ("/home/inspirion/LIFE/export", "r");
    if (pExport==NULL)
        printf ("export_csv: Error");

    fseek (pExport, stage->position, SEEK_CUR);

            for (int i = 0; i< total_amount ; ++i){
                fread (&temp, sizeof(char),1,pExport);
                Squeares [i].realstate = temp;
            }
    fclose(pExport );
}

//------------------------------------------------------------------------
void export_csv (punit Squeares, int total_amount,
                 char* buffer)
{
    FILE *pExport;
    char point = Point;

    pExport = fopen ("/home/inspirion/LIFE/export", "a+");
    if (pExport==NULL){
        pExport = fopen ("/home/inspirion/LIFE/export", "w+");
        if (pExport==NULL)
            printf ("export_csv: Error");
    }

//         write a # to highlight the start of new array
    fwrite (&point, sizeof (char), 1, pExport );

//         write a name of saving game
    fwrite (buffer, sizeof (char), Size, pExport );

    for (int i=0; i< total_amount ; ++i){
//         write an array of cell
        fwrite (&Squeares [i].realstate , sizeof (char), 1,pExport);
    }

    fclose(pExport );
}

//---------------------------------------------------------------------
void update_colors (punit Squeares, int *amount, GLfloat*Dead_cell, GLfloat*Live_cell)
{
    for (int i=0; i<*amount; ++i){

        switch (Squeares[i].realstate) {

        case Live:{
            Squeares [i].color [0] = Live_cell [0];
            Squeares [i].color [1] = Live_cell [1];
            Squeares [i].color [2] = Live_cell [2];
            break;
        }

        case Dead:{
            Squeares [i].color [0] = Dead_cell [0];
            Squeares [i].color [1] = Dead_cell [1];
            Squeares [i].color [2] = Dead_cell [2];
            break;
        }
        default:
            break;
        }
    }
}



