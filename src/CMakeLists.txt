add_library(h595-shift-register-nn STATIC ${CMAKE_CURRENT_SOURCE_DIR}/src/h595-shift-register-nn.c)
target_include_directories(h595-shift-register-nn PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(h595-shift-register-nn pico_stdlib)