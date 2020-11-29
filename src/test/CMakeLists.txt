add_executable(test test.cpp MainWindow.cpp)

include_directories("../driver")
target_link_libraries(
        test
        driver
)