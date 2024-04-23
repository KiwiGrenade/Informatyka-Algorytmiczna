add_library(L1 SHARED lib.c)
add_library(L2 SHARED GF.cpp)
target_link_libraries(L2 PUBLIC L1)
