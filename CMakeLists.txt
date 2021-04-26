cmake_minimum_required (VERSION 3.7.0)
project (digest VERSION 0.1.0)

find_package (OpenSSL REQUIRED COMPONENTS Crypto)

aux_source_directory (src SRC)
add_library (${PROJECT_NAME} ${SRC})

target_include_directories (${PROJECT_NAME} PUBLIC inc)
target_link_libraries (${PROJECT_NAME} OpenSSL::Crypto)
