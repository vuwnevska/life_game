#ifndef LIST_H
#define LIST_H
#include "glodal_types.h"


void find_list_position (sList*, double, double);
int show_choosen        (sList*, float, float);
void append             (sList *List, sSaveGame *item);
sSaveGame *new_unit     ();
void delete_stage       (sList*, sSaveGame*);
void ReWriteFile        (sList*, sSaveGame*);



#endif // LIST_H

