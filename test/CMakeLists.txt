# add the executable
add_executable(unittest indefinite_unittest.cpp)

add_test(NAME IndefiniteStream.unittest COMMAND unittest)
