cmake_minimum_required(VERSION 3.29)
project(cpp_algorithm)

set(CMAKE_CXX_STANDARD 14)

add_executable(cpp_algorithm
    cpp/algrithm/dp/dp1.cpp
    cpp/algrithm/dp/floor.cpp
    cpp/algrithm/Tree/pre_in2tree.cpp
    cpp/algrithm/Tree/treeLeftDown.cpp
    cpp/algrithm/Tree/Trie.cpp
    cpp/algrithm/Trie.cpp
        cpp/algrithm/graph/max_island.cpp
        cpp/algrithm/graph/pacific_atlantic.cpp
        cpp/algrithm/Tree/Judge_AVL.cpp
        cpp/algrithm/multi_thread/thread_pool_ABC.cpp
        cpp/algrithm/dp/longestArith.cpp
        cpp/algrithm/dp/minDistance.cpp
        cpp/algrithm/dp/minASCII.cpp
        cpp/algrithm/greedy/partionLabel.cpp)
