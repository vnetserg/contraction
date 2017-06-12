cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

include_directories(include)

add_executable(
    bidi
    src/bidi.cpp
    src/bidijkstra.cpp
    src/digraph.cpp
    src/intheap.cpp
)
target_compile_features(bidi PRIVATE cxx_auto_type)

add_executable(
    conhier
    src/conhier.cpp
    src/contraction_hierarchies.cpp
    src/vertex_order.cpp
    src/bidijkstra.cpp
    src/digraph.cpp
    src/intheap.cpp
)
target_compile_features(conhier PRIVATE cxx_auto_type)
