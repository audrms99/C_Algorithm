/*
    뿌리 - 가장 위에 있는 노드
    가지 - 뿌리와 잎 사이에 있는 노드
    잎 - 맨 끝에 있는 노드
    형제, 부모, 자식 등 여러가지 용어 있다.

    노드 표현 방법 1)N-link
                2)왼쪽 자식 - 오른쪽 형제

    1) N-link
        노드의 차수가 N개라면  N개가 각각 자식 노드를 가리키는 노드를 구성하는 방법.

    LCRS(왼쪽 자식 - 오른쪽 형제)
*/

// N-link -> LCRS(왼쪽 자식 - 오른쪽 형제)로 구현
#include<stdio.h>
#include<stdlib.h>

typedef char ElementType;

typedef struct tagLCRSNode
{
    struct tagLCRSNode * LeftChild;
    struct tagLCRSNode * RightSibling;

    ElementType Data;
}LCRSNode;

//노드 생성
LCRSNode* LCRS_CreateNode(ElementType NewData)
{
    LCRSNode* NewNode = (LCRSNode*)malloc(sizeof(LCRSNode));
    NewNode->LeftChild = NULL;
    NewNode->RightSibling = NULL;
    NewNode->Data = NewData;

    return NewNode;
}

//노드 소멸
void LCRS_DestroyNode(LCRSNode* Node)
{
    free(Node);
}

void LCRS_DestroyTree( LCRSNode* Root )
{
    if ( Root->RightSibling != NULL )
        LCRS_DestroyTree( Root->RightSibling );

    if ( Root->LeftChild != NULL )
        LCRS_DestroyTree( Root->LeftChild );

    Root->LeftChild = NULL;
    Root->RightSibling = NULL;

    LCRS_DestroyNode( Root );
}

//노드 추가
void LCRS_AddChildNode(LCRSNode* Parent, LCRSNode *Child)
{
    if(Parent->LeftChild == NULL) Parent->LeftChild = Child;
    else
    {
        LCRSNode* TempNode = Parent->LeftChild;
        while(TempNode->RightSibling != NULL)
        {   //형제노드 탐색
            TempNode = TempNode->RightSibling;
        }
        TempNode->RightSibling = Child;
    }
}

//print
void LCRS_PrintTree(LCRSNode* Node, int Depth)
{
    //들여쓰기
    int i = 0;
    for(i = 0; i <Depth - 1; i++) printf("   ");

    if (Depth > 0) printf("+--");

    printf("%c\n", Node->Data);

    if(Node->LeftChild != NULL) LCRS_PrintTree(Node->LeftChild,Depth+1);
    if(Node->RightSibling != NULL) LCRS_PrintTree(Node->RightSibling,Depth);
}

//특정 레벨의 모든 노드를 출력하는 함수 구현
void printNodesAtLevel(LCRSNode* Root, int Level)
{
    if(Root == NULL) return;

    if (Level == 0) printf("%c\n", Root->Data);
    else
    {   
        printNodesAtLevel(Root->LeftChild, Level - 1);
    }
    //부모 기준 자식들도 확인을 해줘야 한다.
    printNodesAtLevel(Root->RightSibling, Level);
    
}

void LCRS_PrintNodesAtLevel(LCRSNode* Root, int level)
{
    printNodesAtLevel(Root, level);
    printf("\n");
}

//트리 길이 출력
void PrintTreeLength(LCRSNode* Root)
{
    LCRSNode* TempNode = Root;

    int cnt = 0;
    
    while(TempNode != NULL)
    {
        TempNode = TempNode->LeftChild;
        cnt++;
    }

    printf("뿌리 미포함:%d\n뿌리 포함해서:%d\n",cnt,cnt + 1);
}


int main(void)
{
    LCRSNode* Root = LCRS_CreateNode('H');

    LCRSNode* A = LCRS_CreateNode('A');
    LCRSNode* B = LCRS_CreateNode('B');
    LCRSNode* C = LCRS_CreateNode('C');
    LCRSNode* D = LCRS_CreateNode('D');
    LCRSNode* E = LCRS_CreateNode('E');
    LCRSNode* F = LCRS_CreateNode('F');
    LCRSNode* G = LCRS_CreateNode('G');
    LCRSNode* L = LCRS_CreateNode('L');

    LCRS_AddChildNode(Root,A);
        LCRS_AddChildNode(A,B);
        LCRS_AddChildNode(A,C);
        LCRS_AddChildNode(A,D);
            LCRS_AddChildNode(D,E);
            LCRS_AddChildNode(D,F);
    LCRS_AddChildNode(Root,G);
    LCRS_AddChildNode(Root,L);

    LCRS_PrintTree(Root,0);

    printf("\n");
    //LCRS_PrintNodesAtLevel(Root, 1);
    printNodesAtLevel(Root,3);
    PrintTreeLength(Root);
    LCRS_DestroyTree(Root);

    return 0;
}


