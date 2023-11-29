#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <sstream>
#include <algorithm>
#include "../lib/json.hpp"

using json = nlohmann::json;

int main() {
    const int ARRAY_SIZE = 4000;
    const int VALUE_MIN = 0;
    const int VALUE_MAX = 3000;

    // Массив для случайных значений
    std::vector<int> randomArray(ARRAY_SIZE);

    // Генератор случайных чисел
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> uni(VALUE_MIN, VALUE_MAX);

    // Заполнение массива случайными числами
    for (int& value : randomArray) {
        value = uni(rng);
    }

    // Создание массива, отсортированного в обратном порядке
    std::vector<int> reverseSortedArray(randomArray);
    std::sort(reverseSortedArray.begin(), reverseSortedArray.end(), std::greater<int>());

    // Создание отсортированного массива
    std::vector<int> sortedArray(randomArray);
    std::sort(sortedArray.begin(), sortedArray.end());

    // Создание функции для "испорченного" отсортированного массива
    auto make_almost_sorted = [&](std::vector<int>& arr, int num_swaps) {
        for (int i = 0; i < num_swaps; ++i) {
            int idx1 = uni(rng) % ARRAY_SIZE;
            int idx2;
            do {
                idx2 = uni(rng) % ARRAY_SIZE;
            } while (idx1 == idx2); // Убедимся, что индексы не совпадают

            std::swap(arr[idx1], arr[idx2]);
        }
    };

    // Портим весь отсортированный массив
    make_almost_sorted(sortedArray, 10); // количество "порч" на весь массив

    // Теперь, вместо того чтобы портить almostSortedArray, мы создаем его срезы ниже
    json subArrays;

    // Теперь для указанных размеров массива создаем срезы
    for (int size = 500; size <= ARRAY_SIZE; size += 100) {
        // Срезы randomArray и reverseSortedArray
        std::vector<int> subRandomArray(randomArray.begin(), randomArray.begin() + size);
        std::vector<int> subReverseSortedArray(reverseSortedArray.begin(), reverseSortedArray.begin() + size);

        // Для almostSortedArray берем срез из уже "испорченного" массива
        std::vector<int> subAlmostSortedArray(sortedArray.begin(), sortedArray.begin() + size);

        // Форматируем ключ с ведущим нулем
        std::ostringstream key_stream;
        key_stream << std::setfill('0') << std::setw(4) << size;
        std::string key = key_stream.str();

        // Добавляем срезы в JSON объект
        json subJson;
        subJson["randomArray"] = subRandomArray;
        subJson["reverseSortedArray"] = subReverseSortedArray;
        subJson["almostSortedArray"] = subAlmostSortedArray;
        subArrays[key] = subJson;
    }

    // Сохранение JSON с срезами в файл
    std::ofstream file("tests.json");
    if (file.is_open()) {
        file << subArrays.dump(4);
        file.close();
    } else {
        std::cerr << "Failed to write data to file!" << std::endl;
        return 1;
    }

    return 0;
}