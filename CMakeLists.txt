cmake_minimum_required (VERSION 3.10)
project (ocaml-c-poc)

find_program(ocamlc_PROGRAM ocamlc REQUIRED)
find_program(ocamlopt_PROGRAM ocamlopt REQUIRED)

execute_process(
    COMMAND ${ocamlc_PROGRAM} -where 
    OUTPUT_VARIABLE OCAML_DIR_ORIG
)

string(REGEX REPLACE "\n$" "" OCAML_DIR "${OCAML_DIR_ORIG}")

add_custom_command(
    OUTPUT helloworld.ml.o
    COMMAND ${ocamlopt_PROGRAM} ${CMAKE_CURRENT_SOURCE_DIR}/helloworld.ml -o ${CMAKE_CURRENT_BINARY_DIR}/helloworld.ml.o -output-complete-obj
    MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/helloworld.ml
)


add_executable(main main.c)
target_link_libraries(main ${CMAKE_CURRENT_BINARY_DIR}/helloworld.ml.o m zstd)
target_include_directories(main PUBLIC ${OCAML_DIR})
add_custom_target(compile_helloworld_ml ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/helloworld.ml.o)
add_dependencies(main compile_helloworld_ml)