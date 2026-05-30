#include <iostream>
using namespace std;

class BST {
    struct node {
        int info;
        node *left;
        node *right;
    };

    node *root;

public:
    BST() {
        root = NULL;
    }

    void fun_1(int item, node **par, node **loc);

    void insert(int item);
    void del(int item);

    void inorder(node *ptr);
    void display() {
        inorder(root);
        cout << endl;
    }

private:
    void case_a(node *par, node *loc);
    void case_b(node *par, node *loc);
    void case_c(node *par, node *loc);
};

// Fungsi pencarian node

void BST::fun_1(int item, node **par, node **loc)
{
    node *ptr, *ptrsave;

    if (root == NULL){
        *loc = NULL;
        *par = NULL;
        return;
    }

    if (item == root->info){
        *loc = root;
        *par = NULL;
        return;
    }

    if (item < root->info)
        ptr = root->left;
    else
        ptr = root->right;

    ptrsave = root;

    while (ptr != NULL)
    {
        if (item == ptr->info)
        {
            *loc = ptr;
            *par = ptrsave;
            return;
        }

        ptrsave = ptr;

        if (item < ptr->info)
            ptr = ptr->left;
        else
            ptr = ptr->right;
    }

    *loc = NULL;
    *par = ptrsave;
}

// INSERT

void BST::insert(int item)
{
    node *tmp, *parent, *location;

    fun_1(item, &parent, &location);

    if (location != NULL)
    {
        cout << "Item sudah ada: " << item << endl;
        return;
    }

    tmp = new node;
    tmp->info = item;
    tmp->left = NULL;
    tmp->right = NULL;

    if (parent == NULL)
        root = tmp;
    else if (item < parent->info)
        parent->left = tmp;
    else
        parent->right = tmp;
}

// DELETE

void BST::del(int item)
{
    node *parent, *location;

    if (root == NULL)
    {
        cout << "Tree kosong\n";
        return;
    }

    fun_1(item, &parent, &location);

    if (location == NULL)
    {
        cout << "Item tidak ditemukan: " << item << endl;
        return;
    }

    // Case A: node tidak punya anak
    if (location->left == NULL && location->right == NULL)
        case_a(parent, location);

    // Case B: node punya satu anak
    else if (location->left == NULL || location->right == NULL)
        case_b(parent, location);

    // Case C: node punya dua anak
    else
        case_c(parent, location);
}

// Case A : Tidak punya anak

void BST::case_a(node *par, node *loc)
{
    if (par == NULL)
        root = NULL;
    else if (loc == par->left)
        par->left = NULL;
    else
        par->right = NULL;

    delete loc;
}

// Case B : Satu anak

void BST::case_b(node *par, node *loc)
{
    node *child;

    if (loc->left != NULL)
        child = loc->left;
    else
        child = loc->right;

    if (par == NULL)
        root = child;
    else if (loc == par->left)
        par->left = child;
    else
        par->right = child;

    delete loc;
}

// Case C : Dua anak

void BST::case_c(node *par, node *loc)
{
    node *ptr, *ptrsave, *suc, *parsuc;

    ptrsave = loc;
    ptr = loc->right;

    while (ptr->left != NULL)
    {
        ptrsave = ptr;
        ptr = ptr->left;
    }

    suc = ptr;
    parsuc = ptrsave;

    if (suc->left == NULL && suc->right == NULL)
        case_a(parsuc, suc);
    else
        case_b(parsuc, suc);

    if (par == NULL)
        root = suc;
    else if (loc == par->left)
        par->left = suc;
    else
        par->right = suc;

    suc->left = loc->left;
    suc->right = loc->right;

    delete loc;
}

// Inorder Traversal

void BST::inorder(node *ptr)
{
    if (ptr != NULL)
    {
        inorder(ptr->left);
        cout << ptr->info << " ";
        inorder(ptr->right);
    }
}

// MAIN

int main()
{
    BST bst;

    int data[] = {32, 11, 13, 46, 78, 4, 16, 8, 25, 37, 56, 61, 44, 29};

    cout << "INSERTION:\n";

    for (int i = 0; i < 14; i++)
    {
        bst.insert(data[i]);
    }

    cout << "Inorder setelah insertion:\n";
    bst.display();

    cout << "\nDELETION:\n";

    int hapus[] = {8, 46, 32, 5};

    for (int i = 0; i < 4; i++)
    {
        cout << "Delete " << hapus[i] << endl;
        bst.del(hapus[i]);

        cout << "Tree sekarang: ";
        bst.display();
        cout << endl;
    }

    return 0;
}