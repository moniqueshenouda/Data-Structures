#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct BSTnode
{
    char word[128];
    struct BSTnode *left, *right;
};

struct BSTnode *root = NULL;
int c=0,i=0;
char dict[3000][50],dict2[3000][50];

struct BSTnode * createNode(char *word)
{
    struct BSTnode *newnode;
    newnode = (struct BSTnode *)malloc(sizeof(struct BSTnode));
    strcpy(newnode->word, word);
    newnode->left = newnode->right = NULL;

    return newnode;
}
struct BSTnode* minValue(struct BSTnode* node)
{
    struct BSTnode* n = node;
    while(n->left!=NULL)
        n=n->left;
    return n;
}
struct BSTnode* maxValue(struct BSTnode* node)
{
    struct BSTnode* n = node;
    while(n->right!=NULL)
        n=n->right;
    return n;
}
struct BSTnode* inOrderPredecessor(struct BSTnode* r, struct BSTnode* x)
{
    if( x->left != NULL )
        return maxValue(x->left);

    struct BSTnode *predecessor = NULL;

    while (r != NULL)
    {
        if (strcasecmp(x->word,r->word)>0)
        {
            predecessor = r;
            r = r->right;
        }
        else if (strcasecmp(x->word,r->word)<0)
            r = r->left;
        else
           break;
    }
    return predecessor;
}

struct BSTnode* inOrderSuccessor(struct BSTnode* r, struct BSTnode* x)
{
    if( x->right != NULL )
        return minValue(x->right);

    struct BSTnode *successor = NULL;

    while (r != NULL)
    {
        if (strcasecmp(x->word,r->word)<0)
        {
            successor = r;
            r = r->left;
        }
        else if (strcasecmp(x->word,r->word)>0)
            r = r->right;
        else
            break;
    }

    return successor;
}
struct BSTnode* sortedArrayToBST(int start, int end)
{
    if (start > end)
      return NULL;
    int mid = start + (end - start) / 2;

    struct BSTnode* r = createNode(dict2[mid]);

    printf("%s\n",r->word);
    printf("%s\n",r->left->word);
    printf("%s\n",r->right->word);

    r->left =  sortedArrayToBST(start, mid-1);

    r->right = sortedArrayToBST(mid+1, end);

    return r;
}

void deleteNode(char *str)
{
    struct BSTnode *parent = NULL, *current = NULL, *temp = NULL;
    int flag = 0, res = 0;
    if (!root)
    {
        printf("BST is not present!!\n");
        return;
    }
    current = root;
    while (1)
    {
        res = strcasecmp(current->word, str);
        if (res == 0)
            break;
        flag = res;
        parent = current;
        current = (res > 0) ? current->left : current->right;
        if (current == NULL)
            return;
    }
    /* deleting leaf node */
    if (current->right == NULL)
    {
        if (current == root && current->left == NULL)
        {
            free(current);
            root = NULL;
            return;
        }
        else if (current == root)
        {
            root = current->left;
            free (current);
            return;
        }

        flag > 0 ? (parent->left = current->left) :
        (parent->right = current->left);
    }
    else
    {
        /* delete node with single child */
        temp = current->right;
        if (!temp->left)
        {
            temp->left = current->left;
            if (current == root)
            {
                root = temp;
                free(current);
                return;
            }
            flag > 0 ? (parent->left = temp) :
            (parent->right = temp);
        }
        else
        {
            /* delete node with two children */
            struct BSTnode *successor = NULL;
            while (1)
            {
                successor = temp->left;
                if (!successor->left)
                    break;
                temp = successor;
            }
            temp->left = successor->right;
            successor->left = current->left;
            successor->right = current->right;
            if (current == root)
            {
                root = successor;
                free(current);
                return;
            }
            (flag > 0) ? (parent->left = successor) :
            (parent->right = successor);
        }
    }
    free (current);
    return;
}

struct BSTnode* findElement(char *str)
{
    struct BSTnode *temp = NULL;

    int flag = 0, res = 0;
    if (root == NULL)
    {
        printf("Binary Search Tree is out of station!!\n");
        return NULL;
    }
    temp = root;
    while (temp)
    {
        if ((res = strcasecmp(temp->word, str)) == 0)
        {
            printf("Word   : %s", str);
            flag = 1;
            break;
        }
        temp = (res > 0) ? temp->left : temp->right;
    }
    if (!flag)
    {
        printf("\nSearch Element not found in Binary Search Tree\n");

        getClose(str);

        temp=NULL;
    }
    return temp;
}

void inorderTraversal(struct BSTnode *myNode)
{


    if (myNode)
    {

        inorderTraversal(myNode->left);
        strcpy(dict[i],myNode->word);
        i++;
        c++;
        inorderTraversal(myNode->right);

    }

    return;
}

char* findClosest(char* word)
{
    inorderTraversal(root);
    int j,b,a;
    i=0;
    char* req=NULL;
    for(j=0; j<2999; j++)
    {
        b=strcasecmp(word,dict[j]);
        a=strcasecmp(word,dict[j+1]);
        if(b!=a)
            req=dict[j+1];
    }

    return req;
};


void getClose(char* word)
{
    char reach[100];
    int i;
    struct BSTnode* temp=NULL,*success=NULL,*pred=NULL;
    strcpy(reach,findClosest(word));
    temp=findElement(reach);
    success=inOrderSuccessor(root,temp);
    pred=inOrderPredecessor(root,temp);
    printf("Did you mean :\nClosest Word:%sSuccessor:%sPredecessor:%s",reach,success->word,pred->word);

}
int main()
{
    int ch;
    int c=0;
    char str[128];
    static const char filename[] = "ED.txt";
    FILE *file = fopen ( filename, "r" );
    if ( file != NULL )
    {
        char line [ 128 ];
        while ( fgets ( line, sizeof line, file ) != NULL )
        {
            strcpy(dict2[c],line);
            c++;

        }
        fclose ( file );
    }
    else
    {
        perror ( filename );
    }

    int z;
    for (z=0;z<2999;z++)
        printf("%s",dict2[z]);
    sortedArrayToBST(0,2999);
    printf("%s",root->word);
    while (1)
    {

        printf("\n1. Deletion\n");
        printf("2. Searching\n3. Traversal\n");
        printf("4. Exit\nEnter your choice:");
        scanf("%d", &ch);
        getchar();


        switch (ch)
        {

        case 1:
            printf("Enter the word to delete:");
            fgets(str, 100, stdin);
            deleteNode(str);
            break;
        case 2:
            printf("Enter the search word:");
            fgets(str, 100, stdin);
            struct BSTnode* here;
            here= findElement(str);

            break;
        case 3:
            printf("Enter the word:");
            fgets(str, 100, stdin);
            findClosest(str);
            break;
        case 4:
            exit(0);
        default:
            printf("You have entered wrong option\n");
            break;
        }
    }
    return 0;
}
