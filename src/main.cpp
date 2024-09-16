#include <iostream>
#include <gtest/gtest.h>
#include "bst.h"

int main(int argc, char **argv)
{
    if (false) // make false to run unit-tests
    //if (true) // make true to run unit-tests
    {
        // debug section
            BST bst{};
            if (bst.get_root() == nullptr) {
                std::cout << "root is nullptr" << std::endl;
            }
            std::cout << "root address: " << bst.get_root() << std::endl;
            std::cout << "nullptr address: " << nullptr << std::endl;
    }
    else
    {
        ::testing::InitGoogleTest(&argc, argv);
        std::cout << "RUNNING TESTS ..." << std::endl;
        int ret{RUN_ALL_TESTS()};
        if (!ret)
            std::cout << "<<<SUCCESS>>>" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
    return 0;   
}