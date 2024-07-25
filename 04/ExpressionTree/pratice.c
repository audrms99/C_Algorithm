#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char ElementType;

typedef struct tagETNode
{
    struct tagETNode *Left;
    struct tagETNode *Right;

    ElementType *Data;
} ETNode;

//------------------------------------------------------------------

ETNode *ET_CreateNode(ElementType NewData)
{
    ETNode *NewNode = (ETNode *)malloc(sizeof(ETNode));
    NewNode->Left = NULL;
    NewNode->Right = NULL;

    NewNode->Data = &NewData;

    return NewNode;
}

void ET_DestroyNode(ETNode *Node)
{
    free(Node);
}

void ET_DestroyTree(ETNode *Root)
{
    if (Root == NULL)
        return;

    ET_DestroyTree(Root->Left);
    ET_DestroyTree(Root->Right);
    ET_DestroyNode(Root);
}

void ET_PreorderPrintTree(ETNode *Node)
{
    if (Node == NULL)
        return;

    printf(" %s", Node->Data);

    ET_PreorderPrintTree(Node->Left);
    ET_PreorderPrintTree(Node->Right);
}

void ET_InorderPrintTree(ETNode *Node)
{
    if (Node == NULL)
        return;

    printf("(");
    ET_InorderPrintTree(Node->Left);

    printf("%s", Node->Data);

    ET_InorderPrintTree(Node->Right);
    printf(")");
}

void ET_PostorderPrintTree(ETNode *Node)
{
    if (Node == NULL)
        return;

    ET_PostorderPrintTree(Node->Left);
    ET_PostorderPrintTree(Node->Right);
    printf(" %c", Node->Data);
}

void ET_BuildExpressionTree(char *PostfixExpression, ETNode **Node)
{
    // 두자리 이상의 숫자를 입력할 시 공백을 추가하여 구분해야할듯
    // 토큰을 배열로 선언, 공백이 나오면 토큰에 저장하는걸 멈추기
    // 사이사이 공백을 넣어야 할듯 ex) 10 2 * 5 2 - /
    // 카운트도 필요할거 같음 개행문자 넣어줄 때 카운트
    //
    int len = strlen(PostfixExpression);
    int cnt = 0;
    char Token[3];
    char lastStr = PostfixExpression[len - 1];
    memset(Token, 0, sizeof(Token));
    for (int i = 0; i < 3; i++)
    {
        if (PostfixExpression[len - 1 - i] == ' ')
            break;
        Token[i] = PostfixExpression[len - 1 - i];
        cnt++;
    }
    for (int i = 0; i < cnt; i++)
    {
        PostfixExpression[len - 1 - i] = '\0';
    }

    switch (lastStr)
    {
    case '+':
    case '-':
    case '*':
    case '/':
        (*Node) = ET_CreateNode(Token);
        ET_BuildExpressionTree(PostfixExpression, &(*Node)->Right);
        ET_BuildExpressionTree(PostfixExpression, &(*Node)->Left);
        break;

    default:
        (*Node) = ET_CreateNode(Token);
        break;
    }
}

// 이거도 생각해보기
double ET_Evaluate(ETNode *Tree)
{
    char Temp[2];

    double Left = 0;
    double Right = 0;
    double Result = 0;

    if (Tree == NULL)
        return 0;
    switch (*Tree->Data)
    {
    case '+':
    case '-':
    case '*':
    case '/':
        Left = ET_Evaluate(Tree->Left);
        Right = ET_Evaluate(Tree->Right);

        if (Tree->Data == '+')
            Result = Left + Right;
        else if (Tree->Data == '-')
            Result = Left - Right;
        else if (Tree->Data == '*')
            Result = Left * Right;
        else if (Tree->Data == '/')
            Result = Left / Right;
        break;

    default:
        memset(Temp, 0, sizeof(Temp)); // Temp의 메모리를 초기화
        Temp[0] = Tree->Data;
        Result = atof(Temp); // string에 저장된 수를 숫자 값으로 변환
        break;
    }
}

//------------------------------------------------------------------

int main(void)
{
    ETNode *Root = NULL;

    char PostfixExpression[20] = "7 1 * 5 2 - /";
    ET_BuildExpressionTree(PostfixExpression, &Root);

    //  트리 출력
    printf("Preorder ...\n");
    ET_PreorderPrintTree(Root);
    printf("\n\n");

    printf("Inorder ... \n");
    ET_InorderPrintTree(Root);
    printf("\n\n");

    printf("Postorder ... \n");
    ET_PostorderPrintTree(Root);
    printf("\n");

    printf("Evaulation Result : %f \n", ET_Evaluate(Root));

    //  트리 소멸시키기
    ET_DestroyTree(Root);
}