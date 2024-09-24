#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* left;
    struct node* right;
    int ht;
};

struct node* create(int data);
struct node* insert(struct node* root, int data);
struct node* delete(struct node* root, int data);
struct node* search(struct node* root, int key);
struct node* rotate_left(struct node* root);
struct node* rotate_right(struct node* root);
int balance_factor(struct node* root);
int height(struct node* root);
void inorder(struct node* root);
void preorder(struct node* root);
void postorder(struct node* root);

int main() {
    int choice;
    struct node* root = NULL;
    int data;

    do {
        printf("\n\n-----AVL TREE-----");
        printf("\n1.Insert");
        printf("\n2.Delete");
        printf("\n3.Search");
        printf("\n4.Inorder");
        printf("\n5.Preorder");
        printf("\n6.Postorder");
        printf("\n7.EXIT");
        printf("\n\n Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter data: ");
                scanf("%d", &data);
                root = insert(root, data);
                break;
            case 2:
                printf("Enter data: ");
                scanf("%d", &data);
                root = delete(root, data);
                break;
            case 3:
                printf("Enter data: ");
                scanf("%d", &data);
                if (search(root, data) == NULL)
                    printf("\n Node not found");
                else
                    printf("\n Node found");
                break;
            case 4:
                inorder(root);
                printf("\n");
                break;
            case 5:
                preorder(root);
                printf("\n");
                break;
            case 6:
                postorder(root);
                printf("\n");
                break;
            case 7:
                printf("\n\tProgram terminated");
                break;
            default:
                printf("\n\tInvalid Choice\n");
        }
    } while (choice != 7);

    return 0;
}

struct node* create(int data) {
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    if (new_node == NULL) {
        printf("\n Memory can't be allocated\n");
        return NULL;
    }
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->ht = 1;  // Starting height
    return new_node;
}

struct node* rotate_left(struct node* root) {
    struct node* right_child = root->right;
    root->right = right_child->left;
    right_child->left = root;

    root->ht = height(root);
    right_child->ht = height(right_child);
    return right_child;
}

struct node* rotate_right(struct node* root) {
    struct node* left_child = root->left;
    root->left = left_child->right;
    left_child->right = root;

    root->ht = height(root);
    left_child->ht = height(left_child);
    return left_child;
}

int balance_factor(struct node* root) {
    int lh, rh;
    if (root == NULL)
        return 0;
    lh = root->left ? root->left->ht : 0;
    rh = root->right ? root->right->ht : 0;
    return lh - rh;
}

int height(struct node* root) {
    if (root == NULL)
        return 0;
    return root->ht;
}

struct node* insert(struct node* root, int data) {
    if (root == NULL) {
        return create(data);
    }
    if (data > root->data) {
        root->right = insert(root->right, data);
    } else if (data < root->data) {
        root->left = insert(root->left, data);
    }

    root->ht = height(root->left) > height(root->right) ? height(root->left) + 1 : height(root->right) + 1;

    int balance = balance_factor(root);
    if (balance > 1 && data < root->left->data) {
        return rotate_right(root);
    }
    if (balance < -1 && data > root->right->data) {
        return rotate_left(root);
    }
    if (balance > 1 && data > root->left->data) {
        root->left = rotate_left(root->left);
        return rotate_right(root);
    }
    if (balance < -1 && data < root->right->data) {
        root->right = rotate_right(root->right);
        return rotate_left(root);
    }
    return root;
}

struct node* delete(struct node* root, int data) {
    if (root == NULL)
        return NULL;

    if (data > root->data) {
        root->right = delete(root->right, data);
    } else if (data < root->data) {
        root->left = delete(root->left, data);
    } else {
        if (root->left == NULL) {
            struct node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct node* temp = root->left;
            free(root);
            return temp;
        }
        struct node* temp = root->right;
        while (temp->left != NULL) {
            temp = temp->left;
        }
        root->data = temp->data;
        root->right = delete(root->right, temp->data);
    }

    if (root == NULL)
        return NULL;

    root->ht = height(root->left) > height(root->right) ? height(root->left) + 1 : height(root->right) + 1;

    int balance = balance_factor(root);
    if (balance > 1 && balance_factor(root->left) >= 0) {
        return rotate_right(root);
    }
    if (balance > 1 && balance_factor(root->left) < 0) {
        root->left = rotate_left(root->left);
        return rotate_right(root);
    }
    if (balance < -1 && balance_factor(root->right) <= 0) {
        return rotate_left(root);
    }
    if (balance < -1 && balance_factor(root->right) > 0) {
        root->right = rotate_right(root->right);
        return rotate_left(root);
    }
    return root;
}

struct node* search(struct node* root, int key) {
    if (root == NULL || root->data == key)
        return root;
    if (key > root->data)
        return search(root->right, key);
    return search(root->left, key);
}

void inorder(struct node* root) {
    if (root == NULL)
        return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

void preorder(struct node* root) {
    if (root == NULL)
        return;
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

void postorder(struct node* root) {
    if (root == NULL)
        return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}
