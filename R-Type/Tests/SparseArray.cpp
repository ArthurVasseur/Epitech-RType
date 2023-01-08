/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** SparseArray
*/

#include <gtest/gtest.h>
#include "SparseAarray.hpp"

TEST(SparseArray, insert)
{
    SparseArray<int> array;

    int val = array.insert_at(8, 12).value();
    EXPECT_EQ(12, val);
}

TEST(SparseArray, EmplaceAt)
{
    SparseArray<int> array;

    int val = array.emplace_at(3, 78).value();
    EXPECT_EQ(78, val);
}

TEST(SparseArray, operatorIndex)
{
    SparseArray<int> array;

    try
    {
        array[8] = 9;
        FAIL();
    }
    catch(const std::exception& e)
    {
        SUCCEED();
    }

    array.emplace_at(0, 9);
    try
    {
        EXPECT_EQ(9, array[0]);
    }
    catch(const std::exception& e)
    {
        FAIL();
    }

    try
    {
        array[0] = 10;
        EXPECT_EQ(10, array[0]);
    }
    catch(const std::exception& e)
    {
        FAIL();
    }
}

TEST(SparseArray, remove)
{
    SparseArray<int> array;

    try
    {
        array.remove_at(10);
        SUCCEED();
    }
    catch(const std::exception& e)
    {
        FAIL();
    }
    auto &elem = array.emplace_at(9, 10);

    try
    {
        array.remove_at(9);
        if(elem.has_value())
            FAIL();
        else SUCCEED();
    }
    catch(const std::exception& e)
    {
        SUCCEED();
    }
}