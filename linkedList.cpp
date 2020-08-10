#include <algorithm>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#define ll long long int
#define ul unsigned long int
#define ull unsigned long long int
#define MIN -9999999
#define INF 9999999
#define MAXN 505
using namespace std;

struct Node
{
    int data;
    struct Node *next;
    Node(int x)
    {
        data = x;
        next = NULL;
    }
};

struct Node *newNode(int data)
{
    struct Node *node = new Node(data);
    node->data = data;
    node->next = NULL;
    return node;
}

void reorderList(Node *head)
{
    // separate list into 2 sub lists
    struct Node *once = head;
    struct Node *second = head != NULL && head->next != NULL ? head->next->next : NULL;

    while (second != NULL)
    {
        once = once->next;
        second = second->next != NULL ? second->next->next : NULL;
    }

    second = once->next;
    once->next = NULL;
    once = head;

    // reverve the second list
    struct Node *prev = NULL;
    struct Node *curr = second;
    struct Node *next = second != NULL ? second->next : NULL;

    while (curr != NULL)
    {
        curr->next = prev;
        prev = curr;
        curr = next;
        if (next != NULL)
            next = next->next;
    }
    second = prev;

    // merge 2 lists
    Node *bridge1 = NULL;
    Node *bridge2 = NULL;
    while (once != NULL && second != NULL)
    {
        bridge1 = once->next;
        once->next = second;
        bridge2 = second->next;
        second->next = bridge1;
        once = bridge1;
        second = bridge2;
    }
}

void printList(struct Node *head)
{
    struct Node *tmp = head;
    while (tmp != NULL)
    {
        cout << tmp->data;
        tmp = tmp->next;
    }
}

void freeList(struct Node *head)
{
    struct Node *tmp;
    while (head != NULL)
    {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

int main()
{
    int t, n, m, i, x;
    cin >> t;
    while (t--)
    {
        struct Node *tmp;
        struct Node *head;
        cin >> n;
        cin >> x;
        head = new Node(x);
        tmp = head;
        for (i = 0; i < n - 1; i++)
        {
            cin >> x;
            tmp->next = new Node(x);
            tmp = tmp->next;
        }
        reorderList(head);
        printList(head);
        freeList(head);
    }
    return 0;
}