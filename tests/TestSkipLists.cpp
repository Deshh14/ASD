#include "SkipList.h"
#include "HashTable.h"
#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include "Heap.h"
#include "Tvector.h"
#include "locale.h"

template<typename T>
void heapSort(Tvector<T>& arr) {
    Heap<T> heap(arr);

    for (size_t i = 0; i < arr.size(); ++i) {
        arr[i] = heap.extractMin();
    }
}

int main(int argc, char** argv) {

    setlocale(LC_ALL, "rus");
    /*SkipList<std::string, double> skipList(6);

    skipList.insert("key1", 12.15);
    skipList.insert("key2", 4.0);
    skipList.insert("key6", 7.523);
    skipList.insert("key13", 87.2);
    skipList.insert("key234", 78.5);
    skipList.insert("key634", 5.8);
    skipList.insert("key655", 58.4238);
    skipList.insert("key7654", 8.769455);

    std::cout << "\n=== SkipList Demo ===\n";
    skipList.print(std::cout);
    std::cout << "\n=====================\n\n";
*/

    
    
    /*HashTableC<std::string, int> dict1;
    dict1.insert("apple", 5);
    dict1.insert("banana", 3);
    dict1.insert("orange", 7);

    HashTableC<std::string, int> dict2;
    dict2.insert("banana", 10);  // конфликт
    dict2.insert("grape", 4);
    dict2.insert("kiwi", 6);

    auto merged1 = mergeTables(dict1, dict2, MergeStrategy::KEEP_FIRST);

    auto merged2 = mergeTables(dict1, dict2, MergeStrategy::KEEP_SECOND);

    */


    std::cout << "=== Тестирование кучи ===\n";

    Heap<int> heap;

    heap.insert(5);
    heap.insert(3);
    heap.insert(8);
    heap.insert(1);
    heap.insert(10);

    std::cout << "После вставки:\n";
    heap.print();

    if (heap.top() == 1) {
        std::cout << "Минимальный элемент: " << heap.top() << " \n";
    }

    Tvector<int> extracted;
    while (!heap.isEmpty()) {
        extracted.push_back(heap.extractMin());
    }

    std::cout << "Извлечённые элементы: ";
    for (size_t i = 0; i < extracted.size(); ++i) {
        std::cout << extracted[i] << " ";
    }
    std::cout << "\n";

    bool sorted = true;
    for (size_t i = 1; i < extracted.size(); ++i) {
        if (extracted[i - 1] > extracted[i]) {
            sorted = false;
            break;
        }
    }
    if (sorted) {
        std::cout << "Элементы извлечены в отсортированном порядке\n";
    }

    Tvector<int> arr;
    arr.push_back(7);
    arr.push_back(2);
    arr.push_back(9);
    arr.push_back(4);
    arr.push_back(1);
    arr.push_back(8);
    arr.push_back(5);

    Heap<int> heap2(arr);
    std::cout << "\nКуча из массива {7, 2, 9, 4, 1, 8, 5}:\n";
    heap2.print();

    if (heap2.top() == 1) {
        std::cout << "Минимальный элемент: " << heap2.top() << "\n";
    }

    std::cout << "\n=== Тест сортировки ===\n";
    Tvector<int> sortArr;
    sortArr.push_back(64);
    sortArr.push_back(34);
    sortArr.push_back(25);
    sortArr.push_back(12);
    sortArr.push_back(22);
    sortArr.push_back(11);
    sortArr.push_back(90);

    std::cout << "Исходный массив: ";
    for (size_t i = 0; i < sortArr.size(); ++i) {
        std::cout << sortArr[i] << " ";
    }
    std::cout << "\n";

    heapSort(sortArr);

    std::cout << "Отсортированный массив: ";
    for (size_t i = 0; i < sortArr.size(); ++i) {
        std::cout << sortArr[i] << " ";
    }
    std::cout << "\n";

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}