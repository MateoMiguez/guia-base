cmake_minimum_required(VERSION 3.24)
project(guia-2024-base C)

set(CMAKE_C_STANDARD 11)

# Habilitar todas las advertencias
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

add_subdirectory(tads)
add_subdirectory(utilidades)

add_subdirectory(practicas/0-repaso)
add_subdirectory(practicas/1-recursividad)
add_subdirectory(practicas/2-tads)
add_subdirectory(practicas/3-listas)
add_subdirectory(practicas/4-pilas)
add_subdirectory(practicas/5-colas)
add_subdirectory(practicas/6-arboles)
add_subdirectory(practicas/7-tabla-hash)
add_subdirectory(practicas/8-conjuntos)

enable_testing()

file(GLOB DATA_FILES "archivos/*.txt")
foreach (DATA_FILE ${DATA_FILES})
    get_filename_component(FILE_NAME ${DATA_FILE} NAME)
    configure_file(${DATA_FILE} archivos/${FILE_NAME} COPYONLY)
endforeach ()
