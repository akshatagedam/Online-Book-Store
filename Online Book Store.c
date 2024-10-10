#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book {
    char title[100];
    char author[100];
    int year;
};

struct Node {
    struct Book book;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(struct Book book) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->book = book;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct Node* insert(struct Node* root, struct Book book) {
    if (root == NULL) {
        return createNode(book);
    }

    if (strcmp(book.title, root->book.title) < 0) {
        root->left = insert(root->left, book);
    } else if (strcmp(book.title, root->book.title) > 0) {
        root->right = insert(root->right, book);
    }

    return root;
}

struct Node* search(struct Node* root, const char* title) {
    if (root == NULL || strcmp(title, root->book.title) == 0) {
        return root;
    }

    if (strcmp(title, root->book.title) < 0) {
        return search(root->left, title);
    } else {
        return search(root->right, title);
    }
}

void displayBookInfo(struct Book book) {
    printf("Title: %s\n", book.title);
    printf("Author: %s\n", book.author);
    printf("Year: %d\n", book.year);
}

void inorderTraversal(struct Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        displayBookInfo(root->book);
        inorderTraversal(root->right);
    }
}

int main() {
    struct Node* root = NULL;

    // Sample book data
    struct Book books[] = {
        {"Book1", "Author1", 2020},
        {"Book2", "Author2", 2019},
        {"Book3", "Author3", 2021},
        {"Book4", "Author4", 2018}
    };

    int numBooks = sizeof(books) / sizeof(books[0]);

    for (int i = 0; i < numBooks; i++) {
        root = insert(root, books[i]);
    }

    printf("Welcome to the Online Book Store\n");

    char searchTitle[100];
    printf("Enter the title of the book you want to search: ");
    scanf("%s", searchTitle);

    struct Node* result = search(root, searchTitle);

    if (result != NULL) {
        printf("Book found!\n");
        displayBookInfo(result->book);
    } else {
        printf("Book not found.\n");
    }

    printf("\nBook List:\n");
    inorderTraversal(root);

    return 0;
}
