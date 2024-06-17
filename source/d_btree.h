/**
    @file   d_btree.h
    @author 박세환 (gommse@gmail.com)
*/
#ifndef DOROTHY_BTREE_H_
#define DOROTHY_BTREE_H_

/*
    이진 트리 검색 순서.
*/
typedef enum D_BTREE_SEARCH_ORDER {
    D_BTREE_SEARCH_PREORDER = 0,
    D_BTREE_SEARCH_INORDER,
    D_BTREE_SEARCH_POSTORDER
} D_BTREE_SEARCH_ORDER;

typedef struct D_BTreeNode {
    Dword key;
    void *data;
    struct D_BTreeNode *left;
    struct D_BTreeNode *right;
} DBTreeNode, *BTree;

BEGIN_DOROTHY_API
    typedef void (*D_BTreeSearchProc)(Dword key, void *data, void *param);

    /**
        @brief  이진 트리를 검색한다.
        @param  [in]    btree   검색할 이진트리 포인터.
        @param  [in]    order   검색 순서.
        @param  [in]    proc    콜백 함수.
        @param  [in]    param   콜백 함수에 전달할 파라미터.
    */
    void    D_SearchBTree(BTree *btree, D_BTREE_SEARCH_ORDER order, D_BTreeSearchProc proc, void *param);

    void*   D_InsertBTree(BTree *btree, Dword key, void *data);
    void    D_ClearBTree(BTree *btree, D_BTreeSearchProc proc);
    void*   D_DeleteBTree(BTree *btree, Dword key);
    void*   D_FindBTree(BTree *btree, Dword key);
    Uint    D_GetBTreeSize(BTree *btree);
END_DOROTHY_API

#endif
