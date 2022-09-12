//nos da arvore
typedef struct node {
    int key;
    struct node* parent;
    struct node* left;
    struct node* right;
}node;

//fila
typedef struct list {
    node* queue;
    struct list* next;
}list;

//arvore
typedef struct tree {
    node* root;
}tree;

int maximum(node* u);
int minimum(node* u);
int insert(tree* T, int key);
void removefirst(list** head);
void insertlast(list** head,  node* u);
void print_in_order(node* u);
void print_pre_order(node* u);
void print_post_order(node* u);
void print_breadth(node* u);
void remove_t(tree* T, int key);
void search(node* u, int key);
void destroy_tree( node* u);
void replace(tree* T, node* u, node* v);