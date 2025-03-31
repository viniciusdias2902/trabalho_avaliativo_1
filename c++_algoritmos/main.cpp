#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>

using namespace std;
using namespace std::chrono;

void insertionSort(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 1; i < n; i++)
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void merge(vector<int> &arr, int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;
    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int i = 0; i < n2; i++)
        R[i] = arr[m + 1 + i];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
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

void mergeSort(vector<int> &arr, int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

int main()
{
    ofstream file("results.csv");
    file << "Size,MergeSortTime,InsertionSortTime" << endl;

    for (int size = 0; size <= 100000; size += 50)
    {
        vector<int> arr(size);
        generate(arr.begin(), arr.end(), rand);

        vector<int> arrCopy = arr;

        auto start = high_resolution_clock::now();
        mergeSort(arr, 0, arr.size() - 1);
        auto end = high_resolution_clock::now();
        double mergeDuration = duration_cast<microseconds>(end - start).count() / 1e6;

        start = high_resolution_clock::now();
        insertionSort(arrCopy);
        end = high_resolution_clock::now();
        double insertionDuration = duration_cast<microseconds>(end - start).count() / 1e6;

        file << size << "," << mergeDuration << "," << insertionDuration << endl;
        cout << "Size: " << size << " | MergeSort: " << mergeDuration << " s | InsertionSort: " << insertionDuration << " s" << endl;
    }

    file.close();
    cout << "Results saved to results.csv" << endl;
    return 0;
}
