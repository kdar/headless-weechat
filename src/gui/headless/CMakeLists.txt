set(WEECHAT_HEADLESS_MAIN_SRC
main.c
color.c
window.c
bar-window.c
chat.c
mouse.c
key.c
term.c)

if ( CMAKE_COMPILER_IS_GNUCC )
    add_definitions("-Wno-unused-variable -Wno-unused-parameter")
endif()

set(EXECUTABLE weechat)

list(APPEND EXTRA_LIBS ${CURL_LIBRARIES})

include_directories(.. ../../core ${CMAKE_BINARY_DIR})

add_executable(${EXECUTABLE} ${WEECHAT_HEADLESS_MAIN_SRC})

target_link_libraries(${EXECUTABLE} ${STATIC_LIBS} ${EXTRA_LIBS} ${STATIC_LIBS})
