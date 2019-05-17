cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

# HELPERS
function(POPULATE_SOURCE_FOLDER allSources projectSourceDir sourceFolder virtualFolder)
## create the group path where sources should be stored
string(REPLACE "\\" "\\\\" SOURCE_GROUP_PATH ${sourceFolder})
string(REPLACE "/" "\\\\" SOURCE_GROUP_PATH ${SOURCE_GROUP_PATH})

## get all the source files from the folder
AUX_SOURCE_DIRECTORY("${projectSourceDir}/${sourceFolder}" LOCAL_SOURCES_FILES)

## get all the headers from the folder
file (GLOB LOCAL_HEADERS_FILES "${projectSourceDir}/${sourceFolder}/*.h" "${projectSourceDir}/${sourceFolder}/*.hpp")
file (GLOB LOCAL_GLSL_FILES "${projectSourceDir}/${sourceFolder}/*.glsl" "${projectSourceDir}/${sourceFolder}/*.glslf"
"${projectSourceDir}/${sourceFolder}/*.glslv")

## add the files to the source tree
set(${allSources}
${${allSources}}
${LOCAL_SOURCES_FILES}
${LOCAL_HEADERS_FILES}
${LOCAL_GLSL_FILES}
PARENT_SCOPE)

## create the source group for the files
if (NOT "${virtualFolder}" STREQUAL "")
SET(SOURCE_GROUP_PATH "${virtualFolder}\\\\${SOURCE_GROUP_PATH}")
endif(NOT "${virtualFolder}" STREQUAL "")
source_group(${SOURCE_GROUP_PATH} FILES ${LOCAL_SOURCES_FILES} ${LOCAL_HEADERS_FILES} ${LOCAL_GLSL_FILES})
endfunction(POPULATE_SOURCE_FOLDER)

function(POPULATE_SOURCE_FOLDER_RECURSIVE allSources projectSourceDir virtualFolder)
## recursive get all files
set(ALL_LOCAL_FILES "")
file (GLOB_RECURSE ALL_LOCAL_FILES "${projectSourceDir}/*.h" "${projectSourceDir}/*.hpp" "${projectSourceDir}/*.cpp" "${projectSourceDir}/*.c"
"${projectSourceDir}/*.glsl" "${projectSourceDir}/*.glslf" "${projectSourceDir}/*.glslv")

SET(DIR_LIST "")
foreach (CURRENT_FILE ${ALL_LOCAL_FILES})
## remove the projectSourceDir from found paths
string(LENGTH ${projectSourceDir} PROJECT_SOURCE_DIR_LENGTH)
math(EXPR PROJECT_SOURCE_DIR_LENGTH "${PROJECT_SOURCE_DIR_LENGTH} + 1")
string(SUBSTRING ${CURRENT_FILE} ${PROJECT_SOURCE_DIR_LENGTH} -1 PROCESS_PATH)

## get the path of the file
GET_FILENAME_COMPONENT(DIR_PATH ${PROCESS_PATH} PATH)
# message("${DIR_PATH} ${PROCESS_PATH}")
SET(DIR_LIST ${DIR_LIST} ${DIR_PATH})
endforeach(CURRENT_FILE)

## remove duplicate directories
LIST(REMOVE_DUPLICATES DIR_LIST)

## create the soruce tree frome each directory
SET(newSources "")
foreach(SCANNED_PATH ${DIR_LIST})
POPULATE_SOURCE_FOLDER(newSources "${projectSourceDir}" "${SCANNED_PATH}" "${virtualFolder}")
endforeach(SCANNED_PATH)

## set up the allSources variables
set(${allSources}
${${allSources}}
${newSources}
PARENT_SCOPE)
endfunction(POPULATE_SOURCE_FOLDER_RECURSIVE)

# PROJECT
project(RacingGame)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR)
message(FATAL_ERROR "Please select another build directory!")
endif()

# SRC FILES
file(GLOB COLLISION_SRC_FILES ${PROJECT_SOURCE_DIR}/IvCollision/*.cpp)
file(GLOB CURVES_SRC_FILES ${PROJECT_SOURCE_DIR}/IvCurves/*.cpp)
file(GLOB ENGINE_SRC_FILES ${PROJECT_SOURCE_DIR}/IvEngine/*.cpp)
file(GLOB ENGINE_OGL_SRC_FILES ${PROJECT_SOURCE_DIR}/IvEngine/OGL/*.cpp)
file(GLOB GRAPHICS_SRC_FILES ${PROJECT_SOURCE_DIR}/IvGraphics/*.cpp)
file(GLOB GRAPHICS_OGL_SRC_FILES ${PROJECT_SOURCE_DIR}/IvGraphics/OGL/*.cpp)
file(GLOB MATH_SRC_FILES ${PROJECT_SOURCE_DIR}/IvMath/*.cpp)
file(GLOB RANDOM_SRC_FILES ${PROJECT_SOURCE_DIR}/IvRandom/*.cpp)
file(GLOB SCENE_SRC_FILES ${PROJECT_SOURCE_DIR}/IvScene/*.cpp)
file(GLOB UTILITY_SRC_FILES ${PROJECT_SOURCE_DIR}/IvUtility/*.cpp)

file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/Game/*.cpp)

# HDR FILES
file(GLOB COLLISION_HDR_FILES ${PROJECT_SOURCE_DIR}/IvCollision/*.h)
file(GLOB CURVES_HDR_FILES ${PROJECT_SOURCE_DIR}/IvCurves/*.h)
file(GLOB ENGINE_HDR_FILES ${PROJECT_SOURCE_DIR}/IvEngine/*.h)
file(GLOB ENGINE_OGL_HDR_FILES ${PROJECT_SOURCE_DIR}/IvEngine/OGL/*.h)
file(GLOB GRAPHICS_HDR_FILES ${PROJECT_SOURCE_DIR}/IvGraphics/*.h)
file(GLOB GRAPHICS_OGL_HDR_FILES ${PROJECT_SOURCE_DIR}/IvGraphics/OGL/*.h)
file(GLOB MATH_HDR_FILES ${PROJECT_SOURCE_DIR}/IvMath/*.h)
file(GLOB RANDOM_HDR_FILES ${PROJECT_SOURCE_DIR}/IvRandom/*.h)
file(GLOB SCENE_HDR_FILES ${PROJECT_SOURCE_DIR}/IvScene/*.h)
file(GLOB UTILITY_HDR_FILES ${PROJECT_SOURCE_DIR}/IvUtility/*.h)

file(GLOB_RECURSE H_FILES ${PROJECT_SOURCE_DIR}/Game/*.h)
file(GLOB_RECURSE HPP_FILES ${PROJECT_SOURCE_DIR}/Game/*.hpp)


# GLSL FILES
file(GLOB_RECURSE GLSL_FILES  ${PROJECT_SOURCE_DIR}/Game/*.glsl)
file(GLOB_RECURSE GLSLV_FILES ${PROJECT_SOURCE_DIR}/Game/*.glslv)
file(GLOB_RECURSE GLSLF_FILES ${PROJECT_SOURCE_DIR}/Game/*.glslf)

# INCLUDE PATHS
include_directories(
${PROJECT_SOURCE_DIR}/../glfw-3.1.1/include/
${PROJECT_SOURCE_DIR}/../assimp/build/include/
${PROJECT_SOURCE_DIR}/../assimp/include/

${PROJECT_SOURCE_DIR}/IvCollision/
${PROJECT_SOURCE_DIR}/IvCurves/
${PROJECT_SOURCE_DIR}/IvEngine/
${PROJECT_SOURCE_DIR}/IvEngine/OGL/
${PROJECT_SOURCE_DIR}/IvGraphics/
${PROJECT_SOURCE_DIR}/IvGraphics/OGL/
${PROJECT_SOURCE_DIR}/IvMath/
${PROJECT_SOURCE_DIR}/IvRandom/
${PROJECT_SOURCE_DIR}/IvScene/
${PROJECT_SOURCE_DIR}/IvUtility/

${PROJECT_SOURCE_DIR}/Game/
${PROJECT_SOURCE_DIR}/Game/Player/
${PROJECT_SOURCE_DIR}/Game/SceneManagement/
${PROJECT_SOURCE_DIR}/Game/GameStates/
${PROJECT_SOURCE_DIR}/Game/shaders/
${PROJECT_SOURCE_DIR}/Game/RayBoxIntersection/
${PROJECT_SOURCE_DIR}/Game/ModelLoader/
${PROJECT_SOURCE_DIR}/Game/ResourceManager/
${PROJECT_SOURCE_DIR}/Game/Helper/
${PROJECT_SOURCE_DIR}/Game/Helper/Shaders/
${PROJECT_SOURCE_DIR}/Game/BasicMenu/
${PROJECT_SOURCE_DIR}/Game/Car/
${PROJECT_SOURCE_DIR}/Game/BasicMenu/Resources/
${PROJECT_SOURCE_DIR}/Game/BasicMenu/Shaders/
${PROJECT_SOURCE_DIR}/Game/Environment/
${PROJECT_SOURCE_DIR}/Game/Environment/Resources/
${PROJECT_SOURCE_DIR}/Game/Environment/Shaders/
${PROJECT_SOURCE_DIR}/Game/RoadGeneration/

${PROJECT_SOURCE_DIR}/Game/Test/
${PROJECT_SOURCE_DIR}/Game/Test/Resources/
${PROJECT_SOURCE_DIR}/Game/Test/TestCustomAttributes/
${PROJECT_SOURCE_DIR}/Game/Test/TestCustomAttributes/Shader/
${PROJECT_SOURCE_DIR}/Game/Test/TestRenderTargets/
${PROJECT_SOURCE_DIR}/Game/Test/TestRenderTargets/Shader/
${PROJECT_SOURCE_DIR}/Game/Test/TestHelper/
${PROJECT_SOURCE_DIR}/Game/Test/TestRayBoxIntersection/
${PROJECT_SOURCE_DIR}/Game/Test/TestBezier/

)

# LINK PATHS
link_directories(
${PROJECT_SOURCE_DIR}/../glfw-3.1.1/lib-MacOS-10.8/
${PROJECT_SOURCE_DIR}/../assimp/build/code/
${PROJECT_SOURCE_DIR}/../assimp/build/contrib/irrXML/
)

POPULATE_SOURCE_FOLDER_RECURSIVE(ALL_ENGINE_SOURCE_FILES "${PROJECT_SOURCE_DIR}" "Source Files")

# EXECUTABLE
add_executable(RacingGame
${COLLISION_SRC_FILES}
${CURVES_SRC_FILES}
${ENGINE_SRC_FILES}
${ENGINE_OGL_SRC_FILES}
${GRAPHICS_SRC_FILES}
${GRAPHICS_OGL_SRC_FILES}
${MATH_SRC_FILES}
${RANDOM_SRC_FILES}
${SCENE_SRC_FILES}
${UTILITY_SRC_FILES}
${SRC_FILES}

${COLLISION_HDR_FILES}
${CURVES_HDR_FILES}
${ENGINE_HDR_FILES}
${ENGINE_OGL_HDR_FILES}
${GRAPHICS_HDR_FILES}
${GRAPHICS_OGL_HDR_FILES}
${MATH_HDR_FILES}
${RANDOM_HDR_FILES}
${SCENE_HDR_FILES}
${UTILITY_HDR_FILES}
${H_FILES}
${HPP_FILES}

${GLSL_FILES}
${GLSLF_FILES}
${GLSLV_FILES}
)

# LINK LIBS
target_link_libraries(RacingGame
"-framework Foundation"
"-framework OpenGL"
"-framework CoreVideo"
"-framework IOKit"
"-framework AppKit"
libglfw3.a
libIrrXML.dylib
libassimp.4.1.0.dylib
)
