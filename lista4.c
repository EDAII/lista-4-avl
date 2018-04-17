 #include<stdlib.h>  
 #include<stdio.h>  
 #include <time.h>
 #include<malloc.h>  
 #define HEIGHT 1  

int lastNode[100];
int topo = 0;

 struct node
 {  
   int data;  
   struct node* left;  
   struct node* right;  
   int height;  
 };

 struct node* get_node(int val){  
   struct node* new_node = (struct node*)malloc(sizeof(struct node));  
   new_node->left = NULL;  
   new_node->right = NULL;  
   new_node->data = val;  
   new_node->height = HEIGHT;  
   return new_node;  
 }  
 int get_height(struct node* root){  
   if(!root)  
     return 0;  
   else  
     return root->height;  
 }  
 int get_balance(struct node* root){  
   if(!root)  
     return 0;  
   return (get_height(root->left) - get_height(root->right));  
 }  
 int max(int a, int b){  
   return (a > b) ? a : b;  
 }  
 struct node* left_rotate(struct node* root){  
   struct node* right = root->right;  
   struct node* left = right->left;  
   //perform rotation  
   right->left = root;  
   root->right = left;  
   //update heights of the rotated nodes  
   root->height = max(get_height(root->left), get_height(root->right)) + 1;  
   right->height = max(get_height(right->left), get_height(right->right)) + 1;  
   //return new root  
   return right;  
 }  
 struct node* right_rotate(struct node* root){  
   struct node* left = root->left;  
   struct node* right = left->right;  
   //perform rotation  
   left->right = root;  
   root->left = right;  
   //update heights of the rotated nodes  
   root->height = max(get_height(root->left), get_height(root->right)) + 1;  
   left->height = max(get_height(left->left), get_height(left->right)) + 1;  
   //return new root  
   return left;  
 }  
 struct node* insert(struct node* root, int val){   
    void printTree(struct node* root);
   //normal insertion  
   if(!root){  
     struct node* new_node = get_node(val);  
     return new_node;  
   }  
   if(root->data > val)  
     root->left = insert(root->left, val);  
   else  
     root->right = insert(root->right, val);  
   //update height of root  
   root->height = max(get_height(root->left), get_height(root->right)) + 1;  
   //check for balancing  
   int balance = get_balance(root);  
   //left-left case  
   if(balance > 1 && root->left->data > val){
     printf("Arvore desbalanceada:\n");
     printTree(root);
     printf("Rotacao para a direita\n");  
     root = right_rotate(root);  
   }  
   //right-right case  
   else if(balance < -1 && root->right->data < val){
     printf("Arvore desbalanceada:\n");
     printTree(root);
     printf("Rotacao para a esquerda\n");
     root = left_rotate(root);  
   }  
   //left-right case  
   else if(balance > 1 && root->left->data < val){
     printf("Arvore desbalanceada:\n");
     printTree(root);
     printf("Rotacao esquerda-direta\n");  
     root->left = left_rotate(root->left);  
     root = right_rotate(root);  
   }  
   //right-left case  
   else if(balance < -1 && root->right->data > val){
     printf("Arvore desbalanceada:\n");
     printTree(root);
     printf("Rotacao direta-esquerda\n");  
     root->right = right_rotate(root->right);  
     root = left_rotate(root);  
   }  
   return root;  
 }  
 //utility function used in balancing of node  
 //in deletion operation  
 struct node* balance_tree(struct node* root){  
   struct node* x, *y;  
   int lheight,rheight;  
   lheight = get_height(root->left);  
   rheight = get_height(root->right);  
   if(lheight >= rheight)  
     x = root->left;  
   else  
     x = root->right;  
   lheight = get_height(x->left);  
   rheight = get_height(x->right);  
   if(x == root->left){  
     if(lheight >= rheight){  
       y = x->left;  
     }  
     else  
       y = x->right;  
   }  
   if(x == root->right){  
     if(lheight > rheight){  
       y = x->left;  
     }  
     else  
       y = x->right;  
   }  
   //left-left case  
   if(root->left == x && x->left == y){  
     printf("Rotacao direita\n");
     root = right_rotate(root);  
   }  
   //right-right case  
   else if(x == root->right && x->right == y){ 
     printf("Rotacao esquerda\n"); 
     root = left_rotate(root);  
   }  
   //left-right case  
   else if(x == root->left && y == x->right){  
     printf("Rotacao esquerda-direita\n");
     root->left = left_rotate(root->left);  
     root = right_rotate(root);  
   }  
   //right-left case  
   else if(x == root->right && y == x->left){  
     printf("Rotacao direita-esquerda\n");
     root->right = right_rotate(root->right);  
     root = left_rotate(root);  
   }  
   return root;  
 }  
 //utility function to find inorder successor   
 //of a given node when it has a right child  
 struct node* inorder_succ_right_tree(struct node* root){  
   struct node* temp = root->right;  
   while(temp->left){  
     temp = temp->left;  
   }  
   return temp;  
 }  
 struct node* deletion(struct node* root, int val){
    void printTree(struct node* root);  
   //normal deletion  
   if(!root)  
     return NULL;  
   if(root->data > val){  
     root->left = deletion(root->left, val);  
   }  
   else if(root->data < val){  
     root->right = deletion(root->right, val);  
   }  
   else{  
     struct node* temp;  
     if(root->left == NULL || root->right == NULL){  
       if(root->left)  
         temp = root->left;  
       else if(root->right)  
         temp = root->right;  
       else  
         temp = NULL;  
       root = NULL;  
       free(root);  
       return temp;  
     }  
     else{  
       temp = inorder_succ_right_tree(root);  
       root->data = temp->data;  
       root->right = deletion(root->right,temp->data);  
     }  
   }  
   if(root){  
     //update height  
     root->height = max(get_height(root->left), get_height(root->right)) + 1;  
     int balance = get_balance(root);  
     if(balance > 1 || balance < -1) {
        printf("Arvore desbalanceada:\n");
        printTree(root);
        root = balance_tree(root);  
     }
   }  
   return root;  
 }  
 //function for printing the pre-order of tree  
 void preorder(struct node* root){  
   if(!root){
     return; 
   } 
   printf("%d\t",root->data);  
   preorder(root->left);  
   preorder(root->right);  
 }  
 //function for printing the post-order of tree  
 void postorder(struct node* root){  
   if(!root){
     return; 
   } 
   preorder(root->left);  
   preorder(root->right);
   printf("%d\t",root->data);  
 }  
 //function for printing the in-order of tree  
 void inorder(struct node* root){  
   if(!root){
     return; 
   } 
   inorder(root->left);  
   printf("%d\t",root->data);  
   inorder(root->right);  
 }  

 int showMenu(struct node* root){ 
    void printTree(struct node* root);

    int option;

     printTree(root);

     printf("\nEscolha uma opcao:\n");
     printf("0 - Sair\n");
     printf("1 - Inserir numero randomico\n");
     printf("2 - Remover ultimo numero da pilha\n");
     scanf("%d", &option);
     printf("\n\n");

     return option;
 }
void printTree(struct node* root){
    printf("\n\nArvore atual em ordem:\n");
     inorder(root);
     printf("\nArvore atual pre-ordem:\n");
     preorder(root);
     printf("\nArovre atual pos-ordem:\n");
     postorder(root);
     printf("\n");
}

struct node* insertRandomNumber(struct node* root){
    int x = rand()%100;
    lastNode[topo++] = x;
    printf("Inserindo %d\n", x);
    root = insert(root, x);
}

struct node* removeLastNumber(struct node* root){
    if(topo > 0){
    printf("Removendo %d\n", lastNode[topo-1]);
    root = deletion(root, lastNode[--topo]);
    }
    else{
        printf("Não há nó para remover\n");
    }
}
 //function to test the functionality of code  
 int main(){  
   srand(time(NULL));
   struct node* root = NULL;
   int option;
   
   do{
        option = showMenu(root);
        switch(option){
            case 0:
                break;
            case 1:
                root = insertRandomNumber(root);
                break;
            case 2:
                root = removeLastNumber(root);
                break;
            default:
                printf("Nao existe essa opcao!\n");
        }
   }while(option != 0);
   root = deletion(root,10);  
 }  