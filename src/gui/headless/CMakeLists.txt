set(WEECHAT_HEADLESS_MAIN_SRC
main.c)

set(EXECUTABLE weechat)

list(APPEND EXTRA_LIBS ${CURL_LIBRARIES})

include_directories(.. ../../core ${CMAKE_BINARY_DIR})

add_executable(${EXECUTABLE} ${WEECHAT_HEADLESS_MAIN_SRC})

target_link_libraries(${EXECUTABLE} ${STATIC_LIBS} ${EXTRA_LIBS} ${STATIC_LIBS})
