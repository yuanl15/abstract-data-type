cmake_minimum_required(VERSION 3.13)
project(abstract_data_type)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(abstract_data_type
        algorithm.cpp
        algorithm.hpp
        AVL.cpp
        AVL.hpp
        binNode.cpp
        binNode.hpp
        BinTree.cpp
        BinTree.hpp
        BST.cpp
        BST.hpp
        graph.cpp
        graph.hpp
        list.cpp
        list.hpp
        listNode.cpp
        listNode.hpp
        main.cpp
        math.cpp
        math.h
        queue.cpp
        queue.hpp
        RedBlack.cpp
        RedBlack.hpp
        stack.cpp
        stack.hpp
        tools.cpp
        tools.hpp
        vector.cpp
        vector.h)
