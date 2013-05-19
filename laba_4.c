#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define string_size 15

typedef struct tree{
    char key_name[string_size];
    char inf_str[string_size];
    struct tree *left;
    struct tree *right;
}tree;

char *MyGets(char *str, size_t strin_size)
{
    fgets(str, strin_size, stdin);
    str[strlen(str) - 1] = '\0';
    return str;
}

void FreeingMemory(tree *tree)
{
    if (!tree) {
        return;
    }
    FreeingMemory(tree->left);
    FreeingMemory(tree->right);
    free(tree);
}

tree* MemoryAllocation(tree *pointer)
{
    if(!(pointer=(tree*)malloc(sizeof(tree)))){
        printf("ERROR!!!There is no free memory!");
        return NULL;
    }
    else return pointer;
}

void InputInform(tree* node)
{
    printf("Enter a string to the node of the tree with the key %s: ",node->key_name);
    MyGets(node->inf_str,string_size);
}

tree *CreateRoot(tree *root) 
{ 
    if (root){ 
        puts("The tree is created");     
        return (root);   
    }   
    root=MemoryAllocation(root);
    printf("Enter the key root of the tree: ");   
    MyGets(root->key_name,string_size);  
    InputInform(root);
    root->left=NULL;
    root->right=NULL;
    return root;
}


tree* Add(tree* root,char*str)
{
    if(root==NULL){
        root=MemoryAllocation(root);
        strcpy(root->key_name,str);
        InputInform(root);
        root->left=root->right=NULL;
    return root;
    }
    if(strcmp(root->key_name,str)==0){
        puts("ERROR! This key has been entered!");
        return root;
    }
    if(strcmp(root->key_name,str)>0){
        root->left=Add(root->left,str);
    }
    else{
        root->right=Add(root->right,str);
    }
    return root;
}

void CreateTree(tree *root)
{
    char st[string_size];
    do{
        puts("Enter the key of the next node of the tree.   (Enter - exit)"); 
        MyGets(st,string_size);   
        if(!*st) return;
        Add(root,st);
    }
    while(1);
}

void Review(tree *root,int level)
{
    if(root){
        Review(root->right,level+5);
    }
    for (int n=0;n<level;++n){
        printf("   ");
    }
    if(root){
        printf("%s\n",root->key_name);
    }
    else printf("\n");
    if(root){
        Review(root->left,level+5);
    }
}

tree* NearestLeaf(tree *current, tree *min, int distance)
{
    static int min_distance;
    if(current->left){
        min=NearestLeaf(current->left,min,distance+1);
    }
    if(current->right){
        min=NearestLeaf(current->right,min,distance+1);
    }
    if((!current->left && !current->right) && (!min_distance || min_distance>=distance)){
        min_distance=distance;
        return current;
    }
    return min;
}

void SearchMaxInf(tree *root, char *key_min)
{
    char max_inf[string_size];
    strcpy(max_inf,root->inf_str);
    while(root){
        if(strlen(root->inf_str)>strlen(max_inf)){
            strcpy(max_inf,root->inf_str);
        }
        if(strlen(root->inf_str)==strlen(max_inf)){
            if(strcmp(root->inf_str,max_inf)>0){
                strcpy(max_inf,root->inf_str);
            }
        }
        if(strcmp(root->key_name,key_min)>0){
            root=root->left;
        }
        else{
            root=root->right;
        }
    }
    printf("Max string on the way to the nearest list: %s\n",max_inf);
}   

void Help(void)
{
    printf
        ("================================================================================\n"
         "MANUAL:\n"
         "Enter the key root of the tree.\n"
         "Enter the key of the next node of the tree.   (Enter - exit).\n"
         "===============================================================================\n"
         "Program finds the closest leaf of the tree and displays the maximum value      \n"
         "of the string on the way to this list.                                          \n"
         "===============================================================================\n");
}

int main(int argc, char *argv[])
{
    if (argc > 1) {
        if (!strcmp(argv[1], "-h"))
            Help();
    }
    int level=0;
    tree *root=NULL,*leaf=NULL;
    root=CreateRoot(root);
    CreateTree(root);
    Review(root, level);
    leaf = NearestLeaf(root, root, level);
    printf("The hearest leaf : %s\n",leaf->key_name);
    SearchMaxInf(root,leaf->key_name);
    FreeingMemory(root);
    return 0;
}