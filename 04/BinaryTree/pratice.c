/*
    이진 트리
    하나의 노드에 자식이 최대 2개 이하 존재
    높이 균형 트리, 완전 높이 균형 트리
    이진 트리의 순회
    1) 전위 순회
    2) 중위 순회
    3) 후위 순회

    --전위 순회--
    1. 뿌리 노드부터 시작
    2. 왼쪽 하위 트리 방문
    3.오른쪽 하위 트리 방문
    --중위 순회--
    1. 왼쪽 하위 트리 시작
    2. 뿌리를 거침
    3. 오른쪽 하위 트리를 방문
*/

#include<stdio.h>
#include<stdlib.h>

typedef char ElementType;

typedef struct tagSBTNode
{
    struct tagSBTNode* Left;
    struct tagSBTNode* Right;

    ElementType Data;
} SBTNode;

SBTNode* SBT_CreateNode(ElementType NewData)
{
    SBTNode* NewNode = (SBTNode*)malloc(sizeof(SBTNode));
    NewNode->Left = NULL;
    NewNode->Right = NULL;
    NewNode->Data = NewData;

    return NewNode;
}

void SBT_DestroyNode(SBTNode* Node)
{
    free(Node);
}

//전위 순회를 응용한 이진 트리 출력
void SBT_PreorderPrintTree(SBTNode* Node)
{
    if(Node == NULL) return;

    printf(" %c",Node->Data);
    SBT_PreorderPrintTree(Node->Left);
    SBT_PreorderPrintTree(Node->Right);
}

//중위 순회를 응용한 이진 트리 출력
void SBT_InorderPrintTree(SBTNode* Node)
{
    if (Node == NULL) return;

    SBT_InorderPrintTree(Node->Left);

    printf(" %c",Node->Data);

    SBT_InorderPrintTree(Node->Right);
}

void SBT_PostorderPrintTree( SBTNode* Node )
{
    if ( Node == NULL )
        return;
    
    //  왼쪽 하위 트리 출력 
    SBT_PostorderPrintTree( Node->Left );

    //  오른쪽 하위 트리 출력 
    SBT_PostorderPrintTree( Node->Right );

    //  루트 노드 출력 
    printf( " %c", Node->Data );
}

void SBT_DestroyTree(SBTNode* Node)
{
    if(Node == NULL) return;

    SBT_DestroyTree(Node->Left);
    SBT_DestroyTree(Node->Right);
    SBT_DestroyNode(Node);
}

int main(void)
{
    //  노드 생성 
    SBTNode* A = SBT_CreateNode('A');
    SBTNode* B = SBT_CreateNode('B');
    SBTNode* C = SBT_CreateNode('C');
    SBTNode* D = SBT_CreateNode('D');
    SBTNode* E = SBT_CreateNode('E');
    SBTNode* F = SBT_CreateNode('F');
    SBTNode* G = SBT_CreateNode('G');
    
    //  트리에 노드 추가 
    A->Left  = B;
    B->Left  = C;
    B->Right = D;

    A->Right = E;
    E->Left  = F;
    E->Right = G;
    
    //  트리 출력 
    printf("Preorder ...\n");
    SBT_PreorderPrintTree( A );
    printf("\n\n");

    printf("Inorder ... \n");
    SBT_InorderPrintTree( A );
    printf("\n\n");

    printf("Postorder ... \n");
    SBT_PostorderPrintTree( A );
    printf("\n");

    //  트리 소멸시키기 
    SBT_DestroyTree( A );

    
    return 0;
}