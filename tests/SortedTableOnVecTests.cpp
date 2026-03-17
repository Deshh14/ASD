#include <gtest/gtest.h>
#include <string>
#include <sstream>
#include "SortedTableOnVec.h"

// Тест 1: Проверка базовых операций и упорядоченности
TEST(SortedTableOnVecTest, BasicOperationsAndOrder) {
    SortedTableOnVec<int, std::string> table;

    EXPECT_TRUE(table.is_empty());

    // Вставка в произвольном порядке
    table.insert(5, "five");
    table.insert(2, "two");
    table.insert(8, "eight");
    table.insert(1, "one");
    table.insert(9, "nine");

    EXPECT_FALSE(table.is_empty());
    EXPECT_EQ(table.size(), 5);  // версия без параметра

    // Проверка consist (вместо contains)
    EXPECT_TRUE(table.consist(2));
    EXPECT_TRUE(table.consist(8));
    EXPECT_FALSE(table.consist(3));

    // Проверка size с ключом
    EXPECT_EQ(table.size(5), 1);
    EXPECT_EQ(table.size(1), 1);
    EXPECT_EQ(table.size(100), 0);

    EXPECT_EQ(table.find(5), "five");
    EXPECT_EQ(table.find(1), "one");

    // Проверка упорядоченности через get_keys
    auto keys = table.get_keys();
    EXPECT_EQ(keys.size(), 5);
    EXPECT_EQ(keys[0], 1);
    EXPECT_EQ(keys[1], 2);
    EXPECT_EQ(keys[2], 5);
    EXPECT_EQ(keys[3], 8);
    EXPECT_EQ(keys[4], 9);

    // Проверка min/max key
    EXPECT_EQ(table.get_min_key(), 1);
    EXPECT_EQ(table.get_max_key(), 9);
}

// Тест 2: Проверка replace и erase с сохранением упорядоченности
TEST(SortedTableOnVecTest, ReplaceAndErase) {
    SortedTableOnVec<std::string, int> table;

    table.insert("banana", 3);
    table.insert("apple", 5);
    table.insert("cherry", 8);
    table.insert("date", 2);

    // Проверка начальной упорядоченности
    auto keys = table.get_keys();
    EXPECT_EQ(keys[0], "apple");
    EXPECT_EQ(keys[1], "banana");
    EXPECT_EQ(keys[2], "cherry");
    EXPECT_EQ(keys[3], "date");

    // Replace не должен нарушать порядок
    table.replace("banana", 30);
    EXPECT_EQ(table.find("banana"), 30);
    EXPECT_EQ(table.size("banana"), 1);

    // Удаление из середины
    table.erase("banana");
    EXPECT_FALSE(table.consist("banana"));
    EXPECT_EQ(table.size(), 3);
    EXPECT_EQ(table.size("banana"), 0);

    // Проверка порядка после удаления
    keys = table.get_keys();
    EXPECT_EQ(keys[0], "apple");
    EXPECT_EQ(keys[1], "cherry");
    EXPECT_EQ(keys[2], "date");
}

// Тест 3: Проверка обработки исключений
TEST(SortedTableOnVecTest, ExceptionHandling) {
    SortedTableOnVec<int, double> table;

    // Попытка найти несуществующий ключ
    EXPECT_THROW(table.find(100), std::runtime_error);

    // Попытка удалить несуществующий ключ
    EXPECT_THROW(table.erase(100), std::runtime_error);

    // Попытка заменить несуществующий ключ
    EXPECT_THROW(table.replace(100, 3.14), std::runtime_error);

    // Попытка получить min/max из пустой таблицы
    EXPECT_THROW(table.get_min_key(), std::runtime_error);
    EXPECT_THROW(table.get_max_key(), std::runtime_error);

    // Вставка элемента
    table.insert(50, 1.5);

    // Попытка вставить дубликат
    EXPECT_THROW(table.insert(50, 2.5), std::runtime_error);

    // Проверка, что значение не изменилось
    EXPECT_EQ(table.find(50), 1.5);
    EXPECT_EQ(table.size(50), 1);
}

// Тест 4: Проверка бинарного поиска и граничных значений
TEST(SortedTableOnVecTest, BinarySearchAndBoundaries) {
    SortedTableOnVec<int, std::string> table;

    // Вставка четных чисел
    for (int i = 0; i <= 20; i += 2) {
        table.insert(i, "value" + std::to_string(i));
    }

    EXPECT_EQ(table.size(), 11);

    // Поиск существующих ключей
    for (int i = 0; i <= 20; i += 2) {
        EXPECT_TRUE(table.consist(i));
        EXPECT_EQ(table.size(i), 1);
        EXPECT_EQ(table.find(i), "value" + std::to_string(i));
    }

    // Поиск несуществующих ключей
    for (int i = 1; i <= 19; i += 2) {
        EXPECT_FALSE(table.consist(i));
        EXPECT_EQ(table.size(i), 0);
    }

    // Проверка граничных значений
    EXPECT_EQ(table.get_min_key(), 0);
    EXPECT_EQ(table.get_max_key(), 20);
}
// Тест 5.1: Проверка работы с разными типами
TEST(SortedTableOnVecTest, DifferentTypes) {
    // Тест с string ключами и double значениями
    SortedTableOnVec<std::string, double> table1;

    table1.insert("pi", 3.14159);
    table1.insert("e", 2.71828);
    table1.insert("phi", 1.61803);

    // Проверка лексикографической сортировки
    auto keys = table1.get_keys();
    EXPECT_EQ(keys[0], "e");
    EXPECT_EQ(keys[1], "phi");
    EXPECT_EQ(keys[2], "pi");

    // Проверка значений
    EXPECT_DOUBLE_EQ(table1.find("pi"), 3.14159);
    EXPECT_DOUBLE_EQ(table1.find("e"), 2.71828);
    EXPECT_EQ(table1.size("phi"), 1);
}

// Тест 5.2: Проверка метода print
TEST(SortedTableOnVecTest, PrintMethod) {
    SortedTableOnVec<std::string, double> table1;
    table1.insert("pi", 3.14159);
    table1.insert("e", 2.71828);
    table1.insert("phi", 1.61803);

    std::stringstream ss;
    table1.print(ss);
    std::string output = ss.str();

    // Проверяем только что вывод не пустой
    EXPECT_FALSE(output.empty());

    // Проверяем наличие ключей
    EXPECT_NE(output.find("pi"), std::string::npos);
    EXPECT_NE(output.find("e"), std::string::npos);
    EXPECT_NE(output.find("phi"), std::string::npos);
}