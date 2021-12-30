#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <time.h>

//단어배열크기
#define MAX_WORD_SIZE 20
//줄표시
int line = 1;
int top = 0;
char top_word[MAX_WORD_SIZE];
char prep[4][MAX_WORD_SIZE] = { {"about\0"}, {"above\0"} ,{"to\0"} , {"a\0"} };

typedef struct _Word
{
    char word[MAX_WORD_SIZE];
    int count;
}Word;

typedef struct _Line
{
    int num;
    struct Line* next;
}Line;

typedef struct _Node
{
    Word key;
    Line* line;
    struct Node* left, * right;
}Node;
//비었으면 1
int Is_Empty(Node* node)
{
    return (node == NULL);
}
int Is_Full()
{
    return ((Node*)malloc(sizeof(Node)) == NULL);
}

Node* new_node(Word* item)
{
    Node* temp = (Node*)malloc(sizeof(Node));
    strcpy(temp->key.word, item->word);
    temp->left = temp->right = NULL;
    temp->key.count = 1;
    Line* linetemp = (Line*)malloc(sizeof(Line));
    linetemp->num = line;
    linetemp->next = NULL;
    temp->line = linetemp;
    return temp;
}

Node* Insert_Node(Node* node, Word* item)
{
    //트리가 공백일 때
    if (Is_Empty(node)) return new_node(item);
    //순환적으로 트리를 내려간다
    if (Compare(*item, node->key) == 0)
    {
        if (node->line->num == line)
        {
            node->key.count++;
        }
        else
        {
            node->key.count++;
            Line* temp = (Line*)malloc(sizeof(Line));
            temp->num = line;
            temp->next = node->line;
            node->line = temp;
        }
    }
    else if (Compare(*item, node->key) < 0)
        node->left = Insert_Node(node->left, item);
    else if (Compare(*item, node->key) > 0)
        node->right = Insert_Node(node->right, item);
    //루트 포인터 반환
    return node;
}

int Compare(Word e1, Word e2)
{
    //e1 < e2 : -1
    //e1 == e2 : 0
    //e1 > e2 : 1
    return strcmp(e1.word, e2.word);
}

//파일 읽기
Node* Read_Text(Node* node)
{
    clock_t start, end;
    double time;
    start = clock();
    FILE* fp = fopen("Test3.txt", "r");
    if (fp == NULL)
        printf("파일 열기 오류\n");
    while (1)
    {
        //파일 끝까지 읽었는지 확인
        if (feof(fp) != 0)
            break;
        char strarr[1000] = {'\0'};
        fgets(strarr, sizeof(strarr), fp);
        char* ptr = strtok(strarr, " ");
        while (ptr != NULL)
        {
            int prepT1 = 0;
            char strtemp[100] = { '\0' };
            Word* e = (Word*)malloc(sizeof(Word));
            strcpy(strtemp, ptr);
            int len = strlen(strtemp);
            for (int i = 0; i < len; i++)
            {
                if (strtemp[i] >= 65 && strtemp[i] <= 90)
                {
                    strtemp[i] = strtemp[i] + 32;
                }
                //문자아닌 구두점 제거
                if ((strtemp[i] >= 33 && strtemp[i] <= 47 && strtemp != 39) 
                    || (strtemp[i] >= 58 && strtemp[i] <= 64) ||
                    (strtemp[i] >= 91 && strtemp[i] <= 95) ||
                    (strtemp[i] >= 123 && strtemp[i] <= 126 || strtemp[i] == '\n'))
                    strtemp[i] = NULL;
            }
            int templen = strlen(strtemp);
            for (int j = 0; j < 4; j++)
            {
                int prepT2 = 0;
                for (int i = 0; i < templen; i++)
                {
                    if (strtemp[i] == prep[j][i])
                        prepT2++;
                }
                if (prepT2 == templen)
                {
                    prepT1 = 1;
                    break;
                }
            }
            if (prepT1 ==1)
            {
                ptr = strtok(NULL, " ");
                continue;
            }
            else
            {
                strcpy(e->word, strtemp);
                node = Insert_Node(node, e);
            }
            
            free(e);
            ptr = strtok(NULL, " ");
        }
        line++;
    }
    fclose(fp);
    end = clock();
    time = (double)(end - start)/CLOCKS_PER_SEC;
    printf("%f\n", time);
    return node;
}

Node* Search(Node* node, Word* item)
{
    while (node != NULL)
    {
        if (Is_Empty(node))
        {
            printf("단어가 없습니다.\n");
            return NULL;
        }
        if (Compare(node->key, *item) == 0)
        {
            printf("%-15s | %-7d | ", node->key.word, node->key.count);
            Line* temp = (Line*)malloc(sizeof(Line));
            temp = node->line;
            while ((temp) != NULL)
            {
                printf("%3d ", temp->num);
                temp = temp->next;
            }
            return 0;
        }
        else if (Compare(*item, node->key) < 0) return Search(node->left, item);
        else return (node->right, item);//(Compare(*item, node->key) > 0) 
    }
    printf("단어가 없습니다.\n");
    return 0;//탐색 실패 했을 때 NULL반환
}

void Frequency(Node* node)
{
    if (node != NULL)
    {
        Frequency(node->left);
        if (top < node->key.count)
        {
            top = node->key.count;
            strcpy(top_word, node->key.word);
        }
        Frequency(node->right);
    }
}

//출력
void Display(Node* node)
{
    if (node != NULL)
    {
        Display(node->left);
        printf("%-15s | %-7d | ", node->key.word, node->key.count);
        Line* temp = (Line*)malloc(sizeof(Line));
        temp = node->line;
        while ((temp) != NULL)
        {
            printf("%3d ", temp->num);
            temp = temp->next;
        }
        printf("\n");
        Display(node->right);
        free(temp);
    }
    
}

void Write_Text(FILE *fp, Node* node)
{ 
    if (node != NULL)
    {
        Write_Text(fp, node->left);
        fprintf(fp, "%-15s | %-7d | ", node->key.word, node->key.count);
        Line* Ltemp = (Line*)malloc(sizeof(Line));
        Ltemp = node->line;
        while ((Ltemp) != NULL)
        {
            fprintf(fp, "%3d ", Ltemp->num);
            Ltemp = Ltemp->next;
        }
        fprintf(fp, "\n");
        Write_Text(fp, node->right);
    }
}

void main()
{
    int select = -1;
    char String[MAX_WORD_SIZE];
    //트리정의
    Node* node = NULL;


    node = Read_Text(node);
    while (select != 0)
    {
        printf("1)출력 2)탐색 3)빈도높은단어 4)파일에 저장 0)종료\n");
        scanf_s(" %d", &select);
        getchar();
        switch (select)
        {
        case 1:
            printf("===============================================\n");
            printf("words           | count   | line numbers\n");
            printf("-----------------------------------------------\n");
            Display(node);
            printf("===============================================\n");
            break;
        case 2:
            printf("탐색할 단어 입력 : ");
            Word* e = (Word*)malloc(sizeof(Word));
            gets_s(e->word, sizeof(e->word));
            printf("===============================================\n");
            printf("words           | count   | line numbers\n");
            printf("-----------------------------------------------\n");
            Search(node, e);
            printf("\n");
            printf("===============================================\n");
            free(e);
            break;
        case 3:
            printf("가장 빈도 높은 단어 : ");
            Frequency(node);
            printf("%s - %d번\n", top_word, top);
            break;
        case 4:
            printf("파일 쓰기 ");
            FILE* fp = fopen("Index.txt", "a");
            Node* Ntemp = (Node*)malloc(sizeof(Node));
            Ntemp = node;
            fprintf(fp, "===============================================\n");
            fprintf(fp, "words           | count   | line numbers\n");
            fprintf(fp, "-----------------------------------------------\n");
            Write_Text(fp, Ntemp);
            fclose(fp);
            printf("완료\n");
            break;
        case 0:
            printf("프로그램을 종료합니다.");
            break;
        default:
            break;
        }
    }
}