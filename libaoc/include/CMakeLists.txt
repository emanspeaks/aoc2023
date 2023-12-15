target_include_directories(${current_day} PUBLIC .)

target_sources(${current_day} PRIVATE aoc.h)
target_sources(${current_day} PRIVATE aocgrid.h)
target_sources(${current_day} PRIVATE debug.h)
target_sources(${current_day} PRIVATE timing.h)
target_sources(${current_day} PRIVATE a_star.h)
target_sources(${current_day} PRIVATE strings.h)
target_sources(${current_day} PRIVATE utf8.h)
