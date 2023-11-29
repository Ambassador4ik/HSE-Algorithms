#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include "Sort.h"
#include "../lib/json.hpp"

using namespace std::chrono;
using json = nlohmann::json;

// Функция для записи строки в CSV файл
void writeResultsToCSV(std::ofstream& file, const std::string& sizeStr, const std::string& arrayType, const std::string& sortType, int N, long long duration) {
    file << sizeStr << ","
         << arrayType << ","
         << sortType << ","
         << N << ","
         << duration << std::endl;
}

int main() {
    // Загрузка JSON с срезами из файла
    std::ifstream inFile("../tests/tests.json");
    if (!inFile.is_open()) {
        std::cerr << "Failed to read data from file!" << std::endl;
        return 1;
    }
    json subArrays;
    inFile >> subArrays;
    inFile.close();

    // Создаем CSV файл для записи результатов
    std::ofstream outFile("results.csv");
    outFile << "ArraySize,ArrayType,SortType,N,Duration(µs)" << std::endl; // Заголовки столбцов

    // Проходим по всем ключам в JSON объекте
    for (auto& [sizeStr, testData] : subArrays.items()) {
        auto randomArray = testData["randomArray"].get<std::vector<int>>();
        auto reverseSortedArray = testData["reverseSortedArray"].get<std::vector<int>>();
        auto almostSortedArray = testData["almostSortedArray"].get<std::vector<int>>();

        // Список настроек сортировки
        std::vector<std::tuple<std::vector<int>, std::string, int>> sortSettings = {
                {randomArray, "Random", -1},
                {reverseSortedArray, "ReverseSorted", -1},
                {almostSortedArray, "AlmostSorted", -1},
        };

        // Добавляем гибридные сортировки с различными значениями N
        std::vector<int> N_values = {5, 10, 20, 50};
        for (int N : N_values) {
            sortSettings.push_back({randomArray, "Random", N});
            sortSettings.push_back({reverseSortedArray, "ReverseSorted", N});
            sortSettings.push_back({almostSortedArray, "AlmostSorted", N});
        }

        // Тестируем каждую сортировку и записываем результаты
        for (const auto& [array, arrayType, N] : sortSettings) {
            auto copyArray = array; // Делаем копию массива для сортировки
            auto start = high_resolution_clock::now();

            if (N == -1) {
                mergeSort(copyArray, 0, copyArray.size() - 1);
            } else {
                hybridSort(copyArray, 0, copyArray.size() - 1, N);
            }

            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start).count();
            std::string sortType = N == -1 ? "MergeSort" : "HybridSort";

            writeResultsToCSV(outFile, sizeStr, arrayType, sortType, N, duration);
        }
    }

    outFile.close();
    return 0;
}