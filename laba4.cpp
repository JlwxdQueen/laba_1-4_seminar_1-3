#include <iostream>
#include <cstring> // ��������� ����������� cstring.h
#include <ctime>
#include <locale.h>

using namespace std;

// ������� ��� ������ ���� ��������� �������
void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// ���������� ���������
void bubbleSort(int arr[], const int n)
{
    for (int i = 0; i < n - 1; ++i)
        for (int j = 0; j < n - i - 1; ++j)
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
}

// ��������� ����������
void shakerSort(int arr[], const int n)
{
    int left = 0, right = n - 1;
    while (left < right)
    {
        // ������ ����� �������
        for (int i = left; i < right; ++i)
            if (arr[i] > arr[i + 1])
                swap(&arr[i], &arr[i + 1]);
        right--;

        // ������ ������ ������
        for (int i = right; i > left; --i)
            if (arr[i - 1] > arr[i])
                swap(&arr[i - 1], &arr[i]);
        left++;
    }
}

// ���������� ���������
void combSort(int arr[], const int n)
{
    float shrinkFactor = 1.247330950103979;
    int gap = n;
    bool swapped = true;

    while (gap > 1 || swapped)
    {
        if (gap > 1)
            gap /= shrinkFactor;

        swapped = false;
        for (int i = 0; gap + i < n; ++i)
        {
            if (arr[i] > arr[i + gap])
            {
                swap(&arr[i], &arr[i + gap]);
                swapped = true;
            }
        }
    }
}

// ���������� ���������
void insertionSort(int arr[], const int n)
{
    for (int i = 1; i < n; ++i)
    {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j -= 1;
        }
        arr[j + 1] = key;
    }
}

// ������� ���� ��������������� ������ �������
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // ������� ��������� �������
    int L[100], R[100];

    // �������� ������ � ��������� �������
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // ���������� ��������� ������� ������� � ��������
    i = 0; // ������ ������� ����������
    j = 0; // ������ ������� ����������
    k = l; // ������ ������������� ����������
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

    // �������� ���������� �������� L[], ���� ��� ����
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    // �������� ���������� �������� R[], ���� ��� ����
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// ���������� ��������
void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;

        // ��������� ������ � ������ ��������
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

// ���������� �������
void selectionSort(int arr[], const int n)
{
    for (int i = 0; i < n - 1; ++i)
    {
        int min_idx = i;
        for (int j = i + 1; j < n; ++j)
            if (arr[j] < arr[min_idx])
                min_idx = j;
        swap(&arr[min_idx], &arr[i]);
    }
}

// ���������� ���������
void countingSort(int arr[], const int n, int maxValue)
{
    int count[100]; // ������ ��� �������� ���������� ������� �����
    memset(count, 0, sizeof(count));

    // ������������ ���������� ������� �����
    for (int i = 0; i < n; ++i)
        count[arr[i]]++;

    // ����������� ������ count ���, ����� �� �������� �������
    for (int i = 1; i <= maxValue; ++i)
        count[i] += count[i - 1];

    // ������ ����� ��������������� ������
    int output[100];
    for (int i = n - 1; i >= 0; --i)
    {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    // �������� ��������������� �������� ������� � �������� ������
    for (int i = 0; i < n; ++i)
        arr[i] = output[i];
}

// ���������� ������� � ����� ������� ����������
int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; ++j)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// ������� ����������
void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// ���������� ���� (������������ � ������������� ����������)
void heapify(int arr[], const int n, int i)
{
    int largest = i; // �������������� ���������� ������� ��� ������
    int left = 2 * i + 1; // ����� �������� �������
    int right = 2 * i + 2; // ������ �������� �������

    // ���� ����� �������� ������� ������ �����
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // ���� ������ �������� ������� ������, ��� ����� ������� ������� �� ������ ������
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // ���� ����� ������� ������� �� ������
    if (largest != i)
    {
        swap(&arr[i], &arr[largest]);

        // ���������� ��������������� ���������� ���������
        heapify(arr, n, largest);
    }
}

// ������������� ����������
void heapSort(int arr[], const int n)
{
    // ��������� ���� (������������������ ������)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // ���� �� ������ ��������� �������� �� ����
    for (int i = n - 1; i >= 0; i--)
    {
        // ���������� ������� ������ � �����
        swap(&arr[0], &arr[i]);

        // �������� ��������� heapify �� ����������� ����
        heapify(arr, i, 0);
    }
}

// �������� ����� (�������� ������ �� ��������������� �������)
int binarySearch(int arr[], const int n, int x)
{
    int low = 0, high = n - 1;
    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (arr[mid] == x)
            return mid;

        if (arr[mid] < x)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1; // ������� �� ������
}

// ����� � ������ (BFS)
bool BFS(int arr[], const int n, int x)
{
    for (int i = 0; i < n; ++i)
        if (arr[i] == x)
            return true;
    return false;
}

// ����� � ������� (DFS) ��� �������� ��������� (�������)
bool DFS(int arr[], const int n, int x)
{
    for (int i = 0; i < n; ++i)
        if (arr[i] == x)
            return true;
    return false;
}

int main()
{
    setlocale(LC_ALL, "rus");
    srand(time(NULL)); // ������������� ���������� ��������� �����

    const int N = 10; // ������ �������
    int arr[N];

    printf("massiv:\n");
    for (int i = 0; i < N; ++i)
    {
        arr[i] = rand() % 100; // ��������� ��������� ����� �� 0 �� 99
        printf("%d ", arr[i]);
    }
    printf("\n\n");

    // ��������� ������ ������� ���������
    bubbleSort(arr, N);       // ���������� ���������
    printf("������������ ����������� �����������: ");
    for (int i = 0; i < N; ++i)
        printf("%d ", arr[i]);
    printf("\n");

    shakerSort(arr, N);       // ��������� ����������
    printf("������������ ��������� �����������: ");
    for (int i = 0; i < N; ++i)
        printf("%d ", arr[i]);
    printf("\n");

    combSort(arr, N);         // ���������� ���������
    printf("������������ ����������� ���������: ");
    for (int i = 0; i < N; ++i)
        printf("%d ", arr[i]);
    printf("\n");

    insertionSort(arr, N);    // ���������� ���������
    printf("������������ ����������� ���������: ");
    for (int i = 0; i < N; ++i)
        printf("%d ", arr[i]);
    printf("\n");

    mergeSort(arr, 0, N - 1); // ���������� ��������
    printf("������������ ����������� �������: ");
    for (int i = 0; i < N; ++i)
        printf("%d ", arr[i]);
    printf("\n");

    selectionSort(arr, N);    // ���������� �������
    printf("������������ ����������� �������: ");
    for (int i = 0; i < N; ++i)
        printf("%d ", arr[i]);
    printf("\n");

    countingSort(arr, N, 99); // ���������� ����������
    printf("������������ ����������� ����������: ");
    for (int i = 0; i < N; ++i)
        printf("%d ", arr[i]);
    printf("\n");

    quickSort(arr, 0, N - 1); // ������� ����������
    printf("������������ ������� �����������: ");
    for (int i = 0; i < N; ++i)
        printf("%d ", arr[i]);
    printf("\n");

    heapSort(arr, N);         // ������������� ����������
    printf("������������ ������������� �����������: ");
    for (int i = 0; i < N; ++i)
        printf("%d ", arr[i]);
    printf("\n");

    // ��������� ����� ��������� ���������
    int searchElement = 50; // ������� ��� ������
    int index = binarySearch(arr, N, searchElement);
    if (index != -1)
        printf("�������� ������� ������� %d ������ �� ������� %d.\n", searchElement, index);
    else
        printf("������� %d �� ������ �������� �������.\n", searchElement);

    if (BFS(arr, N, searchElement))
        printf("����� � ������ ����� ������� %d.\n", searchElement);
    else
        printf("����� � ������ �� ����� ������� %d.\n", searchElement);

    if (DFS(arr, N, searchElement))
        printf("����� � ������� ����� ������� %d.\n", searchElement);
    else
        printf("����� � ������� �� ����� ������� %d.\n", searchElement);

    return 0;
}