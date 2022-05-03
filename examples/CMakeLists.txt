include_directories(${CMAKE_SOURCE_DIR}/src)

file(GLOB LIB_EXAMPLES_SOURCES *.cpp)

foreach(f ${LIB_EXAMPLES_SOURCES})
    get_filename_component(exampleName ${f} NAME_WE)
    add_executable(${CMAKE_PROJECT_NAME}-${exampleName} ${f})
    target_link_libraries(${CMAKE_PROJECT_NAME}-${exampleName} ${CMAKE_PROJECT_NAME})
    install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}-${exampleName}
            DESTINATION bin
            RENAME ${CMAKE_PROJECT_NAME}-${exampleName})
endforeach(f)