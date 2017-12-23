#ifndef IMPORT_EXPORT_H
#define IMPORT_EXPORT_H
#include "glodal_types.h"


void export_csv_struct (punit, int, int);


void export_csv         (punit, int, char*);
void impotr_csv         (sSaveGame *, punit, int);
void count_save         (sSaveGame*, punit, int);
void count_save_buttons (sSaveGame*, punit, int);


#endif // IMPORT_EXPORT_H

