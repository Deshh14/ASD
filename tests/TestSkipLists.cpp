#include "SkipList.h"
#include "HashTable.h"
#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include "Heap.h"
#include "Tvector.h"
#include "locale.h"
#include <algorithm>
#include "PriorityQueue.h"


template<typename T>
void heapSort(Tvector<T>& arr) {
    Heap<T> heap(arr);

    for (size_t i = 0; i < arr.size(); ++i) {
        arr[i] = heap.extractMin();
    }
}

int getPriority(const std::string& type) {
    if (type.find("плат") != std::string::npos) {
        return 1;  // Платно
    }
    if (type == "по записи") {
        return 2;  // По записи
    }
    if (type == "без записи") {
        return 3;  // Без записи
    }
    return 3;
}


int timeToMinutes(const std::string& timeStr) {
    int hours = std::stoi(timeStr.substr(0, 2));
    int minutes = std::stoi(timeStr.substr(3, 2));
    return hours * 60 + minutes;
}

std::string minutesToTime(int minutes) {
    int hours = minutes / 60;
    int mins = minutes % 60;
    char buffer[6];
    sprintf(buffer, "%02d:%02d", hours, mins);
    return std::string(buffer);
}

Tvector<std::string> parsePatient(const std::string& line) {
    Tvector<std::string> result;

    std::string timeStr = line.substr(0, 5);
    result.push_back(timeStr);

    size_t dashPos = line.find('-');

    size_t nameStart = dashPos + 2;
    size_t spacePos = line.find(' ', nameStart);

    std::string name;
    std::string type;

    if (spacePos == std::string::npos) {
        name = line.substr(nameStart);
        type = "";
    }
    else {
        name = line.substr(nameStart, spacePos - nameStart);
        type = line.substr(spacePos + 1);
    }

    result.push_back(name);
    result.push_back(type);

    return result;
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
    //std::cout << "=== Тестирование кучи ===\n";
    //Heap<int> heap;
    //heap.insert(5);
    //heap.insert(3);
    //heap.insert(8);
    //heap.insert(1);
    //heap.insert(10);
    //std::cout << "После вставки:\n";
    //heap.print();

    //if (heap.top() == 1) {
    //    std::cout << "Минимальный элемент: " << heap.top() << " \n";
    //}

    //Tvector<int> extracted;
    //while (!heap.isEmpty()) {
    //    extracted.push_back(heap.extractMin());
    //}

    //std::cout << "Извлечённые элементы: ";
    //for (size_t i = 0; i < extracted.size(); ++i) {
    //    std::cout << extracted[i] << " ";
    //}
    //std::cout << "\n";

    //bool sorted = true;
    //for (size_t i = 1; i < extracted.size(); ++i) {
    //    if (extracted[i - 1] > extracted[i]) {
    //        sorted = false;
    //        break;
    //    }
    //}
    //if (sorted) {
    //    std::cout << "Элементы извлечены в отсортированном порядке\n";
    //}

    //Tvector<int> arr;
    //arr.push_back(7);
    //arr.push_back(2);
    //arr.push_back(9);
    //arr.push_back(4);
    //arr.push_back(1);
    //arr.push_back(8);
    //arr.push_back(5);

    //Heap<int> heap2(arr);
    //std::cout << "\nКуча из массива {7, 2, 9, 4, 1, 8, 5}:\n";
    //heap2.print();

    //if (heap2.top() == 1) {
    //    std::cout << "Минимальный элемент: " << heap2.top() << "\n";
    //}

    //std::cout << "\n=== Тест сортировки ===\n";
    //Tvector<int> sortArr;
    //sortArr.push_back(64);
    //sortArr.push_back(34);
    //sortArr.push_back(25);
    //sortArr.push_back(12);
    //sortArr.push_back(22);
    //sortArr.push_back(11);
    //sortArr.push_back(90);

    //std::cout << "Исходный массив: ";
    //for (size_t i = 0; i < sortArr.size(); ++i) {
    //    std::cout << sortArr[i] << " ";
    //}
    //std::cout << "\n";
    //heapSort(sortArr);

    //std::cout << "Отсортированный массив: ";
    //for (size_t i = 0; i < sortArr.size(); ++i) {
    //    std::cout << sortArr[i] << " ";
    //}
    //std::cout << "\n";

    Tvector<std::string> inputData = {
        "12.30 - Иванов по записи",
        "12.35 - Петров без записи",
        "12.50 - Воронин по записи",
        "12.55 - Сидоров без записи на платной основе",
        "13.10 - Васильев по записи",
        "13.15 - Михайлов без записи",
        "14.05 - Борисов без записи на платной основе",
        "14.07 - Владимиров без записи на платной основе",
        "14.30 - Федоров по записи",
        "14.50 - Нестеров по записи"
    };

    Tvector<int> arrivalTimes;
    Tvector<std::string> names;
    Tvector<std::string> types;
    Tvector<int> priorities;

    for (const auto& line : inputData) {
        Tvector<std::string> parsed = parsePatient(line);

        int time = timeToMinutes(parsed[0]);
        std::string name = parsed[1];
        std::string type = parsed[2];
        int priority = getPriority(type);

        arrivalTimes.push_back(time);
        names.push_back(name);
        types.push_back(type);
        priorities.push_back(priority);
    }

    for (size_t i = 0; i < arrivalTimes.size() - 1; i++) {
        for (size_t j = 0; j < arrivalTimes.size() - i - 1; j++) {
            if (arrivalTimes[j] > arrivalTimes[j + 1]) {
                std::swap(arrivalTimes[j], arrivalTimes[j + 1]);
                std::swap(names[j], names[j + 1]);
                std::swap(types[j], types[j + 1]);
                std::swap(priorities[j], priorities[j + 1]);
            }
        }
    }

    PriorityQueue<std::string> pq;
    Tvector<std::string> result;

    int currentTime = arrivalTimes[0];
    size_t patientIndex = 0;

    std::cout << "=== СИМУЛЯЦИЯ ПРИЕМА ПАЦИЕНТОВ ===" << std::endl;
    std::cout << "Длительность приема: 20 минут" << std::endl;
    std::cout << "Приоритеты: 1 - платно, 2 - по записи, 3 - без записи" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    std::cout << std::endl;

    while (patientIndex < arrivalTimes.size() || !pq.isEmpty()) {
        while (patientIndex < arrivalTimes.size() && arrivalTimes[patientIndex] <= currentTime) {
            std::cout << minutesToTime(arrivalTimes[patientIndex]) << " - Пришел "
                << names[patientIndex];
            if (!types[patientIndex].empty()) {
                std::cout << " (" << types[patientIndex];
                if (priorities[patientIndex] == 1) {
                    std::cout << ", приоритет 1";
                }
                std::cout << ")";
            }
            std::cout << std::endl;

            pq.push(names[patientIndex], priorities[patientIndex]);
            pq.print();

            patientIndex++;
        }

    if (!pq.isEmpty()) {
        std::string currentPatient = pq.extractTop();
        result.push_back(currentPatient);

        std::cout << "\n>>> " << minutesToTime(currentTime)
            << " - Начинается прием: " << currentPatient
            << std::endl;

        currentTime += 20;

        if (!pq.isEmpty()) {
            std::cout << "Оставшиеся в очереди: ";
            pq.print();
        }
        else {
            std::cout << "Очередь пуста";
        }
        std::cout << "\n" << std::endl;
    }
    else {
        if (patientIndex < arrivalTimes.size()) {
            currentTime = arrivalTimes[patientIndex];
        }
    }
}

    std::cout << "\n=== ПОРЯДОК ПРИЕМА ПАЦИЕНТОВ ===" << std::endl;
    std::cout << std::string(30, '=') << std::endl;
    for (size_t i = 0; i < result.size(); i++) {
        std::cout << result[i];
        if (i != result.size() - 1) {
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
}