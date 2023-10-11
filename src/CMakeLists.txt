add_executable(main main.cpp glad.c stb_image.cpp)

target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_directories(main PRIVATE ${CMAKE_SOURCE_DIR}/libs)

# 链接编译需要的系统框架
target_link_libraries(main "-framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo")

target_link_libraries(main glfw3)