/**
    @file   d_list.h
    @author 박세환 (gommse@gmail.com)
*/
#ifndef DOROTHY_LIST_H_
#define DOROTHY_LIST_H_

typedef struct D_ListNode {
    Uint key;
    void *data;
    struct D_ListNode *prev, *next;
} DListNode;

typedef struct D_List {
    Uint32 count;
    DListNode *h, *t;
} DList;

BEGIN_DOROTHY_API
    void    D_PushFrontList(DList *list, Uint key, void *data);
    void    D_PushBackList(DList *list, Uint key, void *data);

    void*   D_SetListData(DList *list, Uint key, void *data);
    void*   D_GetListData(DList *list, Uint key);

    void    D_DelListData(DList *list, Uint key);

    DListNode*  D_InsertListData(DList *list, DListNode *node, Uint key, void *data);
/*
    ListNode*   D_InsertPrevList(List *list, ListNode *next, Word key, void *data);
    ListNode*   D_InsertNextList(List *list, ListNode *prev, Word key, void *data);
*/
    DListNode*  D_BeginListNode(DList *list);
    DListNode*  D_EndListNode(DList *list);
    DListNode*  D_FindListNode(DList *list, Uint key);
    DListNode*  D_DelListNode(DList *list, DListNode *node);

    void    D_ClearList(DList *list);
END_DOROTHY_API

#endif
