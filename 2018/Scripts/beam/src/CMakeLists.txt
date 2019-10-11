project(beam)
cmake_minimum_required(VERSION 2.6.4)

message(STATUS "Looking for LibXml2...")
find_package(LibXml2 REQUIRED)
if(LIBXML2_FOUND)
  message(STATUS "Looking for LibXml2... -  Found")
else(LIBXML2_FOUND)
  message(STATUS "Looking for LibXml2... - Not Found")
endif(LIBXML2_FOUND)

message(STATUS "  >> Building beam usecase code...")

#---------------------------------------------------------------------
# Includes directory
#---------------------------------------------------------------------
include_directories(${LIBXML2_INCLUDE_DIR})
message(STATUS "    >> LIBXML2_INCLUDE_DIR ${LIBXML2_INCLUDE_DIR}")

###add_definitions(-pipe -W -g -fPIC -Wno-deprecated ${LIBXML2_DEFINITION})
message(STATUS "    >> LIBXML2_DEFINITION ${LIBXML2_DEFINITION}")

#---------------------------------------------------------------------
# Add sources
#---------------------------------------------------------------------
add_executable(beam main.cpp beam.cpp)

#---------------------------------------------------------------------
# Link Libraries
#---------------------------------------------------------------------
message(STATUS "    >> LIBXML2_LIBRARIES ${LIBXML2_LIBRARIES}")
target_link_libraries(beam ${LIBXML2_LIBRARIES})

#---------------------------------------------------------------------
# Install target per OS
#---------------------------------------------------------------------
install(TARGETS beam DESTINATION ${CMAKE_SOURCE_DIR}/bin)

#-----------------------------------------------------------------------
# End of the main section of the CMakeLists file
#-----------------------------------------------------------------------
message(STATUS "  >> Building beam code... - Built")

# End Of File





