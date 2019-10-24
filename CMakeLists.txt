cmake_minimum_required (VERSION 3.8)

project(DataStructure)

file(GLOB LKLISTSRC  "LinkedList/*.cpp" "LinkedList/*.h" "Test/LinkedListTest.cpp")
file(GLOB HEAPSRC "Heap/*.cpp" "Heap/*.h" "Test/HeapTest.cpp" )
file(GLOB TREESRC "Tree/*.cpp" "Tree/*.h" "Test/TreeTest.cpp" )
file(GLOB GRAPHSRC "Tree/*.cpp" "Tree/*.h" "Test/GraphTest.cpp" )
file(GLOB UTILSRC "Util/*.cpp" "Util/*.h" "Test/UtilTest.cpp" )


add_executable (linkedlistTest ${LKLISTSRC})
add_executable (heapTest ${HEAPSRC})
add_executable (treeTest ${TREESRC})
add_executable (graphTest ${GRAPHSRC})
add_executable (utilTest ${UTILSRC})

