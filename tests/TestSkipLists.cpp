#include "SkipList.h"
#include <gtest/gtest.h>
#include <iostream>
#include <string>

int main(int argc, char** argv) {
    SkipList<std::string, double> skipList(6);

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


    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}