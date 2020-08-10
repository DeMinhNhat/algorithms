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
#define ii pair<int, int>
#define ll long long int
#define ul unsigned long int
#define ull unsigned long long int
#define MIN -999999999
#define MAX 999999999
#define MAXN 101
using namespace std;
void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

void merge(int arr[], int l, int m, int r)
{
    int n1 = m + 1;
    int n2 = r + 1;
    int L[n1], R[n2];

    int i = l, j = m + 1, k;
    while (i < n1)
    {
        L[i] = arr[i];
        i++;
    }
    while (j < n2)
    {
        R[j] = arr[j];
        j++;
    }
    i = l, j = m + 1, k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] < R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r)
{

    if (l < r)
    {
        // avoid overflow of sum of l +r
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

int partialSort(int arr[], int low, int high)
{
    int pivot = arr[low];
    int i = high;
    int zwitch = i + 1;

    while (i > low)
    {
        if (arr[i] > pivot)
        {
            zwitch--;
            swap(arr[i], arr[zwitch]);
        }
        i--;
    }
    swap(arr[zwitch - 1], arr[low]);
    return zwitch - 1;
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pivot = partialSort(arr, low, high);
        quickSort(arr, low, pivot - 1);
        quickSort(arr, pivot + 1, high);
    }
}

void heapify(int arr[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[left] < arr[largest])
        largest = left;
    if (right < n && arr[right] < arr[largest])
        largest = right;
    if (largest != i)
    {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--)
    {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

bool deleteHeap(int arr[], int n, int i)
{
    if (i >= n)
        return false;
    swap(arr[i], arr[n - 1]);
    heapSort(arr, n - 1);
    return true;
}

int main()
{
    int arr[] = {4, 3, 5, 7, 4, 2, 45, 3, 32};
    int len = sizeof(arr) / sizeof(arr[0]);

    mergeSort(arr, 0, len);
    quickSort(arr, 0, len - 1);
    heapSort(arr, len);
    // deleteHeap(arr, len, 1);

    for (int i = 0; i < len; i++)
        cout << arr[i] << " ";
    return 0;
}
