# add the executable
add_executable(unittest indefinite-unittest.cpp)

add_test(NAME IndefiniteStream.unittest COMMAND unittest)
