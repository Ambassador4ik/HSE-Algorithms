#include <iostream>
#include <vector>

void insertionSort(std::vector<int>& arr, int left, int right) {
    for (int i = left+1; i <= right; i++) {
        int key = arr[i];
        int j = i - 1;

        // Перемещаем элементы arr[left..i-1], которые больше, чем key
        // на одну позицию вперед их текущего положения
        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// Функция слияния двух половин массива
void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1; // Размер левой половины
    int n2 = right - mid;    // Размер правой половины

    // Временные массивы для хранения половин
    std::vector<int> L(n1), R(n2);

    // Копирование данных во временные массивы
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Слияние временных массивов обратно в arr[l..r]
    int i = 0; // Начальный индекс первой половины
    int j = 0; // Начальный индекс второй половины
    int k = left; // Начальный индекс объединенной половины

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Копирование оставшихся элементов L, если они есть
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Копирование оставшихся элементов R, если они есть
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Модифицированная функция hybridSort, которая использует insertionSort для малых массивов
void hybridSort(std::vector<int>& arr, int left, int right, int N) {
    if (right - left + 1 <= N) {
        insertionSort(arr, left, right);
    } else {
        if (left < right) {
            // Находит середину
            int mid = left + (right - left) / 2;

            // Сортирует первую и вторую половины
            hybridSort(arr, left, mid, N);
            hybridSort(arr, mid + 1, right, N);

            // Слияет две половины, если они не отсортированы с помощью insertionSort
            merge(arr, left, mid, right);
        }
    }
}

// Реализация сортировки слиянием
void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        // Находит середину
        int mid = left + (right - left) / 2;

        // Сортирует первую и вторую половины
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Слияет две половины
        merge(arr, left, mid, right);
    }
}
