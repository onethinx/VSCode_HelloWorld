cmake_minimum_required(VERSION 3.7.2)

set(DEBUG_ON false)
######################################################################
#
#	Toolchain
#
######################################################################

if(${DEBUG_ON})
    set(CMAKE_VERBOSE_MAKEFILE ON CACHE BOOL "ON")
    message("INFO: path=$ENV{PATH}")
endif()

set(TOOLS_DIR $ENV{ONETHINX_PACK_LOC}/tools_2.0)
set(DESIGN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/design)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source)
set(CONFIG_DIR $ENV{ONETHINX_PACK_LOC}/config)
set(CY_PDL_DIR $ENV{ONETHINX_PDL_LOC})
set(LINKER_DIR $ENV{ONETHINX_PACK_LOC}/linker)


if (${CMAKE_HOST_SYSTEM_NAME} MATCHES "Windows")
    find_program (BASH_TOOL ${TOOLS_DIR}/bash/bash.exe DOC "The bash executable")
else()
    find_program (BASH_TOOL bash DOC "The bash executable")
endif()

find_program(CYPRESS_ELF_TOOL CyMcuElfTool "${TOOLS_DIR}/cymcuelftool-1.0/bin" DOC "Cypress ELF tool executable")
find_program(READELF_TOOL arm-none-eabi-readelf "${COMPILER_DIR}" DOC "ReadELF tool executable")

#Get the top directory name. This will be used as project_name in later section
string(FIND ${CMAKE_CURRENT_SOURCE_DIR} / POSITION REVERSE )
MATH(EXPR POSITION "${POSITION}+1")
string(SUBSTRING ${CMAKE_CURRENT_SOURCE_DIR} ${POSITION} -1 TOP_DIR_NAME)
set(ENV{TOP_DIR_NAME} ${TOP_DIR_NAME})

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/local.cmake)
    include (${CMAKE_CURRENT_SOURCE_DIR}/local.cmake)
endif()
set (CMAKE_TOOLCHAIN_FILE "${CONFIG_DIR}/cmake/arm-none-eabi-toolchain.cmake")

######################################################################
#
#	Project
#
######################################################################

message("INFO: Project \"${TOP_DIR_NAME}\"")
project(${TOP_DIR_NAME})
enable_language(ASM)

execute_process(COMMAND ${CMAKE_C_COMPILER} -print-multi-lib OUTPUT_VARIABLE GCC_VERSION)
string(FIND "${GCC_VERSION}" "armv7-m" ARM_V7M_DETECTED)
if (${ARM_V7M_DETECTED} EQUAL "-1")
    message( FATAL_ERROR "Wrong compiler selected, CMake will exit." )
endif()

# Use Cypress PDL
include(${CONFIG_DIR}/cmake/cypress_peripheral_drivers_library.cmake)

# Define PSoC63 chip used in the project
# CY8C6347BZI_BLD53 - Used on the Onethinx LoRaWAN Core board
set(CHIP "CY8C6347BZI_BLD53" CACHE STRING "Chip variant used on a board")
set_property(CACHE CHIP PROPERTY STRINGS CY8C6347BZI_BLD54 CY8C6347BZI_BLD53)

message("INFO: Chip variant= ${CHIP}")
add_definitions(-D ${CHIP})

#Include common settings
include(${CONFIG_DIR}/cmake/common.cmake)

######################################################################
#
#	Project compiler & linker options
#
######################################################################

set(PROJECT_FLAGS_ARCH
    "-mthumb"
    "-Og"
    "-mcpu=cortex-m4"
    "-mslow-flash-data"
    "-mfloat-abi=softfp"
    "-mfpu=fpv4-sp-d16"
    "-DCYDEV_CLK_ALTHF__HZ=8000000UL"
)

set(PROJECT_LINKER_FLAGS
    "-Wl,-Map=${PROJECT_NAME}.map"
    "-TOnethinxCore_18.ld"
)

set(PROJECT_C_FLAGS_WARNINGS "${COMMON_FLAGS_WARNINGS} ${C_FLAGS_WARNINGS_EXTRA}")
set(PROJECT_CXX_FLAGS_WARNINGS "${COMMON_FLAGS_WARNINGS}")

######################################################################
#
#	Sources
#
######################################################################

# Find Source includes folders (containing *.h)
FIND_DIRECTORIES(SOURCE_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/*.h)
# include these paths
include_directories (
    ${DESIGN_DIR}/GeneratedSource
    ${PDL_INCLUDE_DIRS}
    ${SOURCE_INCLUDE_DIRS}
)

# Find Source files (containing *.c)
FILE(GLOB_RECURSE SOURCE_SRCS ${SOURCE_DIR}/*.c)
FILE(GLOB_RECURSE DESIGN_SRCS ${DESIGN_DIR}/GeneratedSource/*.c)

set(PROJECT_SRCS
    ${SOURCE_SRCS}
    ${DESIGN_SRCS}
#Chip startup and core system
    ${CY_PDL_DIR}/devices/bsp/COMPONENT_MTB/startup/system_psoc6_cm4.c
    ${CY_PDL_DIR}/devices/bsp/COMPONENT_MTB/startup/TOOLCHAIN_GCC_ARM/startup_psoc6_02_cm4.S
)

if(${DEBUG_ON})
    message("INFO: Project source folder  = ${PROJECT_SOURCE_DIR}")
    message("INFO: Source include folders = ${SOURCE_INCLUDE_DIRS}")
    message("INFO: Source folders         = ${SOURCE_SRCS}")
    message("INFO: Design source folders  = ${DESIGN_SRCS}")
endif()

######################################################################
#
#	TARGET
#
######################################################################

#TODO: Evaluate ASM FLAGS
set (CMAKE_ASM_FLAGS "${C_FLAGS} ${C_FLAGS_WARNINGS} ${FLAGS_OPTIMIZATION} ${PROJECT_FLAGS_ARCH}")
set (CMAKE_C_FLAGS "${C_FLAGS} ${C_FLAGS_WARNINGS} ${FLAGS_OPTIMIZATION} ${PROJECT_FLAGS_ARCH}")
set (CMAKE_CXX_FLAGS "${CXX_FLAGS} ${CXX_FLAGS_WARNINGS} ${FLAGS_OPTIMIZATION} ${PROJECT_FLAGS_ARCH}")
set (CMAKE_EXE_LINKER_FLAGS "${LINKER_FLAGS} ${PROJECT_LINKER_FLAGS} ${FLAGS_OPTIMIZATION} ${PROJECT_FLAGS_ARCH}")

# CMake lists are separated by semicolons, remove these
string(REGEX REPLACE ";" " " CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS}")
string(REGEX REPLACE ";" " " CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
string(REGEX REPLACE ";" " " CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
string(REGEX REPLACE ";" " " CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")

set (CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS}" CACHE STRING "" FORCE)
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS}" CACHE STRING "" FORCE)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" CACHE STRING "" FORCE)
set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}" CACHE STRING "" FORCE)

if(${DEBUG_ON})
    message("INFO: ASM Options    = ${CMAKE_ASM_FLAGS}")
    message("INFO: C Options      = ${CMAKE_C_FLAGS}")
    message("INFO: C++ Options    = ${CMAKE_CXX_FLAGS}")
    message("INFO: Linker Options = ${CMAKE_EXE_LINKER_FLAGS}")
endif()

add_executable(${PROJECT_NAME}.elf ${PROJECT_SRCS} ${PDL_SRCS})

######################################################################
#
#	Build actions
#
######################################################################

add_custom_target(
    ${PROJECT_NAME} ALL
    #POST BUILD
    COMMAND "${CYPRESS_ELF_TOOL}" --sign "${PROJECT_NAME}.elf" --output "${PROJECT_NAME}_signed.elf" --hex "${PROJECT_NAME}.hex"
    COMMAND echo "------- Memory usage -------"
    #COMMAND "${CYPRESS_ELF_TOOL}" -A "${PROJECT_NAME}.elf"
    COMMAND "${READELF_TOOL}" -Sl ${PROJECT_NAME}.elf > ${PROJECT_NAME}.readelf
    COMMAND "${BASH_TOOL}" ${CONFIG_DIR}/scripts/memcalc.bash ${PROJECT_NAME}.readelf "917504" "229376" "268435456" "134217728" #Flash 0x0e0000   SRAM 0x38000   Flash start 0x10000000   SRAM start 0x08000000
    DEPENDS "${PROJECT_NAME}.elf"
)
