#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(LxeProject)
#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
#
include(${Geant4_USE_FILE})
#----------------------------------------------------------------------------
# Locate sources and headers for this project
#
include_directories(${PROJECT_SOURCE_DIR}/include 
                    ${Geant4_INCLUDE_DIR})
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

#----------------------------------------------------------------------------
# Find ROOT (required package)
#
find_package(ROOT QUIET)
if(NOT ROOT_FOUND)
  message(STATUS "G4 Examples: ROOT package not found")
  return()
else()
  include_directories(${ROOT_INCLUDE_DIR})
endif()

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(LxeSim LxeSim.cc ${sources} ${headers})
target_link_libraries(LxeSim ${Geant4_LIBRARIES} )
if(ROOT_FOUND)
  target_link_libraries(LxeSim ${ROOT_LIBRARIES} )
endif()

#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build N01. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/output/)
#
set(Lxesim_SCRIPTS
    ./macro/vis.mac
    ./macro/run1.mac
    ./macro/gui.mac
    ./macro/icons.mac
    ./macro/init.mac
    ./macro/init_vis.mac
    ./macro/ChangeGometry.mac
  )

foreach(_script ${Lxesim_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()
# Add program to the project targets
# (this avoids the need of typing the program name after make)
#
add_custom_target(LxeProject DEPENDS LxeSim)

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS LxeSim RUNTIME DESTINATION Simulation)
install(DIRECTORY macro DESTINATION Simulation PATTERN ".svn" EXCLUDE)
install(DIRECTORY DESTINATION Simulation/output/ PATTERN ".svn" EXCLUDE)
