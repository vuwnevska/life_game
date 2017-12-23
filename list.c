#include "list.h"
#include "function.h"


//------------------------------------------------------------------------------------
void find_list_position (sList *List, double x, double y)
{

    sSaveGame *pt = List->pHead;

    while (pt != NULL){
        if (pt->tack.x1 <= x && x <= pt->tack.x2)
            if (pt->tack.y1 <= y && y <= pt->tack.y2){
                List->current = pt;
                return;
            }

        pt = pt->next;
    }
}
//------------------------------------------------------------------------------------
sSaveGame *new_unit ()
{

    sSaveGame *temp = (sSaveGame*) malloc (sizeof(sSaveGame));
    temp->id = 0;
    temp->next = NULL;
    temp->prev = NULL;
    return temp;
}
//------------------------------------------------------------------------------------
void append (sList *List, sSaveGame *item)
{
    if (List->pHead == NULL){

        List->pHead  = item;
        item->next   = List->pLast;
        List->pLast  = item;
    }

    else {
        List->pLast->next = item;
        item->prev        = List->pLast;
        List->pLast       = item;
    }
}
//------------------------------------------------------------------------------------
int show_choosen (sList *List, float x, float y)
{

    sSaveGame *pt = List->pHead;

    if (List->current != List->prevois && List->prevois != NULL){
        SelectBut (&(List->prevois->tack), 0.1, 0.1, 0.1);
    }

    while (pt != NULL){
        if (pt->tack.x1 <= x && x <= pt->tack.x2)
            if (pt->tack.y1 <= y && y <= pt->tack.y2){

                SelectBut (&(pt->tack), 0.3, 0.3, 0.3);
                List->current = pt;

                return 1;
            }
        pt = pt->next;
    }
    return 0;
}
//------------------------------------------------------------------------------------

void delete_stage (sList *List,  sSaveGame* current)
{

    if (current == List->pHead){
        List->pHead = current->next;
        current->next->prev = current->prev;
    }
    else if (current == List->pLast){
        List->pLast = current->prev;
        current->prev->next = current->next;
    }
    else{
    current->prev->next = current->next;
    current->next->prev = current->prev;
    }

    free (current);
}

//------------------------------------------------------------------------------------
void ReWriteFile  (sList *List,  sSaveGame* current)
{
    FILE *pExportRead;
    FILE *pExportWrite;
    char tmp;


    sSaveGame *pt = List->pHead;
    int amount = 0;

    pExportRead = fopen ("/home/inspirion/LIFE/export", "r+");
    if (pExportRead == NULL){
        printf (" ReWriteFile export pExportRead: Error");
    return;
    }

//    open new temporary file
    pExportWrite = fopen ("/home/inspirion/LIFE/export_tmp", "w+");
    if (pExportRead == NULL){
        printf (" ReWriteFile export pExportWrite: Error");
    return;
    }


//    if delete last stage
    if (current == List->pHead && List->value == 1){

        fclose (pExportRead);
        fclose (pExportWrite);
        List->value = 0;
        List->pHead = NULL;
        free (current);
        remove ("/home/inspirion/LIFE/export");
        remove ("/home/inspirion/LIFE/export_tmp");
        return;
    }
    amount = List->pHead->next->position - List->pHead->position;

    while (pt != NULL){

        if (pt != current){

            for (int i=0; i< amount; ++i){
            fread (&tmp, sizeof (char), 1, pExportRead);
            fwrite (&tmp, sizeof (char), 1, pExportWrite);
            }
        }
        else{
            if (current == List->pLast)
                break;
        fseek (pExportRead, current->next->position-Size-1, SEEK_SET);
        pt = pt->next;
        }
        pt = pt->next;
    }
//    writing the last stage
    if (current != List->pLast){
        for (int i=0; i< amount; ++i){
        fread (&tmp, sizeof (char), 1, pExportRead);
        fwrite (&tmp, sizeof (char), 1, pExportWrite);
        }
    }

    fclose (pExportRead);
    fclose (pExportWrite);

//    delete old file and rename new file as old
    remove ("/home/inspirion/LIFE/export");
    rename ("/home/inspirion/LIFE/export_tmp",
            "/home/inspirion/LIFE/export");


}
