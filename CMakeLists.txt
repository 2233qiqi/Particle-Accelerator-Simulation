cmake_minimum_required(VERSION 3.16...3.28)
project(geant4_example)
# (2)
find_package(Geant4 REQUIRED ui_all vis_all)
find_package(ROOT REQUIRED)
# (3)
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)
# (4)
add_executable(geant4_example main.cc ${sources} ${headers})
#add_executable(geant4_example main.cc)

target_include_directories(geant4_example PRIVATE include)
target_link_libraries(geant4_example PRIVATE ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})
# (5)
set(EXAMPLEB1_SCRIPTS
#exampleB1.in
#exampleB1.out
init_vis.mac
#run1.mac
#run2.mac
vis.mac
)
foreach(_script ${EXAMPLEB1_SCRIPTS})
configure_file(
 ${PROJECT_SOURCE_DIR}/${_script}
 ${PROJECT_BINARY_DIR}/${_script}
 COPYONLY
 )
endforeach()