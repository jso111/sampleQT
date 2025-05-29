cmake_minimum_required(VERSION 3.29)

project(sampleQT VERSION 0.1 LANGUAGES CXX)
set(CMAKE_FIND_DEBUG_MODE FALSE)
set(CMAKE_VERBOSE_MAKEFILE ON)
add_definitions(-w)
add_compile_options(-w)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Vulkan REQUIRED)
message("Vulkan_INCLUDE_DIRS: ${Vulkan_INCLUDE_DIRS}")

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        camerawidget.cpp 
        camerawidget.h
)
#This comment messes up my testbranch
if (LINUX)
    list(APPEND CMAKE_PREFIX_PATH "/opt/Qt/6.8.2/gcc_64")
    list(APPEND CMAKE_PREFIX_PATH "/opt/Qt/6.9.0/gcc_64")
    list(APPEND CMAKE_PREFIX_PATH "/opt/Qt/6.10.0/gcc_64")
    list(APPEND CMAKE_PREFIX_PATH "/opt/Qt/6.8.0/gcc_64")
    list(APPEND CMAKE_PREFIX_PATH "/HDF_Group/HDF5/1.14.5")
    find_package(Qt6 REQUIRED COMPONENTS Widgets Gui Charts Multimedia MultimediaWidgets PrintSupport)
    find_package(OpenCV REQUIRED)
    qt_add_executable(sampleQT
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
    target_link_libraries(sampleQT PUBLIC
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Charts
        Qt${QT_VERSION_MAJOR}::Gui
        Qt6::PrintSupport
        Qt6::Multimedia
        Qt6::MultimediaWidgets
        ${OpenCV_LIBS}
    )
    target_include_directories(sampleQT PUBLIC
                            "${PROJECT_BINARY_DIR}"
                            "${PROJECT_SOURCE_DIR}"
                            )
endif ()

if (WIN32)
    add_compile_definitions(_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS)
    add_compile_definitions(_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /FS")
    
    list(APPEND CMAKE_PREFIX_PATH "C:/Qt/6.8.0/msvc2022_64")
    list(APPEND CMAKE_PREFIX_PATH "C:/Qt/6.8.1/msvc2022_64")
    list(APPEND CMAKE_PREFIX_PATH "C:/Qt/6.8.2/msvc2022_64")
    list(APPEND CMAKE_PREFIX_PATH "C:/Qt/6.9.0/msvc2022_64")
    list(APPEND CMAKE_PREFIX_PATH "C:/Qt/6.10.0/msvc2022_64")

    include_directories(${Vulkan_INCLUDE_DIRS})
    list(APPEND CMAKE_PREFIX_PATH "C:/Qt/6.8.2/msvc2022_64")
    list(APPEND CMAKE_PREFIX_PATH "C:/Qt/6.8.2/msvc2022_64/bin")
    include_directories("C:/Qt/6.8.2/msvc2022_64/bin")

    list(APPEND CMAKE_PREFIX_PATH "C:/opencv/build")
    find_package(OpenCV REQUIRED)
    message("OpenCV_LIBS: ${OpenCV_LIBS}")
    message("OpenCV_INCLUDE_DIRS: ${OpenCV_INCLUDE_DIRS}")
    message("OpenCV_LIB_DIR: ${OpenCV_LIB_DIR}")   
    message("OpenCV_DIR: ${OpenCV_DIR}")   
    qt_add_executable(cvib3 ${PROJECT_SOURCES})
endif()

find_package(Qt6 6 REQUIRED COMPONENTS Core Widgets Gui Charts Multimedia MultimediaWidgets PrintSupport)
message("Qt6_DIR: ${Qt6_DIR}")
message("Qt6_VERSION: ${Qt6_VERSION}")
message("Qt6_VERSION_MAJOR: ${Qt6_VERSION_MAJOR}")  


qt_standard_project_setup()
MESSAGE("MSVC: ${MSVC}")
if(MSVC)
    if(NOT STATIC_DEPS OR CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_link_options(sampleQT PUBLIC /nodefaultlib:LIBCMT.lib /nodefaultlib:LIBCMTd.lib)
    endif()
    
endif()
qt_add_executable(sampleQT ${PROJECT_SOURCES})
target_link_libraries(sampleQT PRIVATE 
        Qt6::Widgets
        Qt6::Charts
        Qt6::Gui
        Qt6::PrintSupport
        Qt6::Multimedia
        Qt6::MultimediaWidgets
        ${Vulkan_LIBRARIES}
        ${OpenCV_LIBS}
        )
include(CPack)
include(GNUInstallDirs)
set_target_properties(sampleQT PROPERTIES
    ${BUNDLE_ID_OPTION}
    WIN32_EXECUTABLE TRUE
)


install(TARGETS sampleQT
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
qt_generate_deploy_app_script(
    TARGET sampleQT
    OUTPUT_SCRIPT deployApp
    NO_UNSUPPORTED_PLATFORM_ERROR
)
SET(BIN_DBG ${CMAKE_CURRENT_BINARY_DIR}/Debug)
SET(BIN_REL ${CMAKE_CURRENT_BINARY_DIR}/Release)

if (WIN32)
    ADD_CUSTOM_COMMAND(
    TARGET sampleQT
    POST_BUILD 
    COMMAND
        CD $<$<CONFIG:Debug>:${BIN_DBG}>$<$<CONFIG:Release>:${BIN_REL}> &&
        ${WINDEPLOYQT_EXECUTABLE} --pdb sampleQT.exe
        --verbose 1 --dir . --plugindir plugins --compiler-runtime
        )
    message("WINDEPLOYQT_EXECUTABLE: ${WINDEPLOYQT_EXECUTABLE}")
endif()

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(sampleQT)
endif()
