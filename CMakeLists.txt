project(CodeBuilder)
cmake_minimum_required(VERSION 3.15)
aux_source_directory(./src/ SRC_LIST)
aux_source_directory(./src/builders/ SRC_LIST)
aux_source_directory(./src/analyzers/ SRC_LIST)
aux_source_directory(./src/gui/ SRC_LIST)

set(wxWidgets_CONFIGURATION mswu)
find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})

add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})