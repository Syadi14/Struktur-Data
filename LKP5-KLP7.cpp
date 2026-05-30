#include <iostream>

using namespace std;
void insertAfterKey(Node* p, int key, int data){

// Struktur Node Linked List
struct Node {
public:
    int data;
    Node* next;
};

// Membuat node baru dengan data tertentu
Node* newNode(int data) {
    Node* new_node = new Node;
    new_node->data = data;
    new_node->next = nullptr;
    return new_node;
}

// Fungsi untuk menyisipkan node di akhir (rekursif)
Node* insertEnd(Node* head, int data) {

    // Jika list kosong, buat node baru
    if (head == nullptr)
        return newNode(data);

    // Jika belum sampai akhir, lanjut rekursif
    head->next = insertEnd(head->next, data);

    return head;
}

// Fungsi untuk menampilkan isi linked list (rekursif)
void traverse(Node* head) {

    if (head == nullptr)
        return;

    cout << head->data << " ";

    traverse(head->next);
}

// Driver Code
int main() {

    Node* head = nullptr;

    head = insertEnd(head, 6);
    head = insertEnd(head, 8);
    head = insertEnd(head, 10);
    head = insertEnd(head, 12);
    head = insertEnd(head, 14);

    traverse(head);

    return 0;
}
}