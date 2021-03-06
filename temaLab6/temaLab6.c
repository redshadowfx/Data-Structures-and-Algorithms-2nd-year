#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct medicine{
    char* name;
    float price;
    unsigned int quantity;
    char recievedDate[15];
    char expireDate[15];
}Medicine;

///Tree node
typedef struct tNode{
    Medicine value;
    struct tNode* right;
    struct tNode* left;
}TNode;

TNode* treeRoot = NULL;

void CreateTree();
char Same(const Medicine* a, const Medicine* b);
int Add(const Medicine* m);
void Update(const Medicine* m);
void Delete(const Medicine* m);
void Print(TNode* currentNode);
void UpdateNode(const char* name);
TNode* ReadNode();

int main()
{
    CreateTree();

    Print(treeRoot);
    char medicine[100];
    fprintf(stdout, "Ce medicament trebuie updatat? ");
    fscanf(stdin,"%s",medicine);
    UpdateNode(medicine);
    Print(treeRoot);
    return 0;
}

char Same(const Medicine* a, const Medicine* b){
    if(a==NULL || b==NULL)
        return 0;
    if(strcmp(a->name,b->name)==0) return 1;
    else return 0;
}

void CreateTree(){
    int n;
    fprintf(stdout,"cate medicamente: ");
    fscanf(stdin,"%d", &n);

    TNode* currentNode;
    int i;
    for(i = 0; i < n; i++){
        TNode* nodeRead = ReadNode();
        Add(nodeRead);
    }
}

int Add(const Medicine* m){
    if(treeRoot == NULL){
        treeRoot = m;
        return 1;
    }
    else{
        char go = 1;
        TNode* currentNode = treeRoot;
        while(go){
            ///strcmp(a,b)
            /// > 0 => a > b
            /// < 0 => a < b
            if(strcmp(currentNode->value.name,m->name) < 0){
                if(currentNode->right == NULL)
                {
                    go = 0;
                    currentNode->right = m;
                }
                else
                    currentNode = currentNode->right;
            }
            else if(strcmp(currentNode->value.name,m->name) > 0){
                if(currentNode->left == NULL)
                {
                    go = 0;
                    currentNode->left = m;
                }
                else
                    currentNode = currentNode->left;
            }
            else {
                free(m);
                return -1;
            }
        }

    }
    return 1;
}

TNode* ReadNode(){
    TNode* temp = malloc(sizeof(TNode));
    ///alocam numele(este alocat dinaminc)
    fprintf(stdout,"\nintroduceti numele: ");
    char name[256];
    fflush(stdin);
    gets(name);
    temp->value.name = malloc(strlen(name)+1);
    strcpy(temp->value.name,name);
    ///restul membrilor ii citim direct
    fprintf(stdout,"introduceti pretul: ");
    fscanf(stdin,"%f",&temp->value.price);
    fprintf(stdout,"introduceti cantitatea: ");
    fscanf(stdin,"%u",&temp->value.quantity);
    fprintf(stdout,"introduceti data primirii: ");
    fscanf(stdin,"%s",temp->value.recievedDate);
    fprintf(stdout,"introduceti data expirarii: ");
    fscanf(stdin,"%s",temp->value.expireDate);
    temp->left=NULL;
    temp->right=NULL;
    return temp;
}
void Print(TNode* currentNode){
    if(currentNode != NULL){
        Print(currentNode->left);
        fprintf(stdout,"numele: %s\npretul: %f\ncantitatea: %u\ndata primirii: %s\ndata expirarii: %s\n\n",
        currentNode->value.name,currentNode->value.price,currentNode->value.quantity,
        currentNode->value.recievedDate,currentNode->value.expireDate);
        Print(currentNode->right);
    }
}

void UpdateNode(const char* name){
    if(treeRoot == NULL){
        return;
    }
    else{
        char go = 1;
        TNode* currentNode = treeRoot;
        while(go){
            if(strcmp(currentNode->value.name,name) == 0){
                float price;
                unsigned int quantity;
                char expireDate[15];
                char recievedDate[15];

                fprintf(stdout,"Update Price: ");
                fscanf(stdin,"%f",&price);
                fprintf(stdout,"Update Quantity: ");
                fscanf(stdin,"%u",&quantity);
                fprintf(stdout,"Update Recieved Date: ");
                fscanf(stdin,"%s",recievedDate);
                fprintf(stdout,"Update Expire Date: ");
                fscanf(stdin, "%s", expireDate);
                currentNode->value.price=price;
                currentNode->value.quantity=quantity;
                strcpy(currentNode->value.expireDate,expireDate);
                strcpy(currentNode->value.recievedDate,recievedDate);
                go = 0;
            }
            else if(strcmp(currentNode->value.name,name) < 0){
                currentNode = currentNode->right;
            }
            else if(strcmp(currentNode->value.name,name) > 0){
                currentNode = currentNode->left;
            }
        }

    }
}
