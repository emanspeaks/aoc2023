target_include_directories(${current_day} PUBLIC .)

configure_file(aocday.h.in aocday.h)
target_include_directories(${current_day} PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_sources(${current_day} PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/aocday.h)

target_sources(${current_day} PRIVATE main.h)
target_sources(${current_day} PRIVATE lrmap.h)
