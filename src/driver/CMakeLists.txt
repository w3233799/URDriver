add_library(driver SHARED URDriver.cpp URScript.cpp) #生成一个动态链接库
target_link_libraries(
        driver
        ${QT_LIBRARIES}
)