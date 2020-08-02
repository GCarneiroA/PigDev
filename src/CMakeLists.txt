
set(pig_SRCS
    canimacao.cpp
    cassetloader.cpp
    caudio.cpp
    cclientetcp.cpp
    ccontrole.cpp
    cfilapacotes.cpp
    cgeradorparticulas.cpp
    cgeradorpoligonos.cpp
    cgerenciadoranimacoes.cpp
    cgerenciadoraudios.cpp
    cgerenciadorcontroles.cpp
    cgerenciadorfontes.cpp
    cgerenciadorjanelas.cpp
    cgerenciadorobjetos.cpp
    cgerenciadorparticulas.cpp
    cgerenciadorsockets.cpp
    cgerenciadortimers.cpp
    cgerenciadorvideos.cpp
    cjanela.cpp
    cjogo.cpp
    cmapacaracteres.cpp
    cmapacaracteresdinamicos.cpp
    cmodoanimacao.cpp
    cmouse.cpp
    cobjeto.cpp
    cparticula.cpp
    cpigareadetexto.cpp
    cpigbotao.cpp
    cpigbox.cpp
    cpigcaixatexto.cpp
    cpigcampotextoesenha.cpp
    cpigcheckbox.cpp
    cpigcomponente.cpp
    cpigcursor.cpp
    cpigdropdown.cpp
    cpigerro.cpp
    cpigerroarquivo.cpp
    cpigerroparametro.cpp
    cpigerroindice.cpp
    cpigform.cpp
    cpiggauge.cpp
    cpiggaugecircular.cpp
    cpigitemcheck.cpp
    cpigitemlista.cpp
    cpiglista.cpp
    cpigradiobox.cpp
    cpigscrollbar.cpp
    cpigstringformatada.cpp
    cpilhacoordenada.cpp
    cpoolnumeros.cpp
    cservidortcp.cpp
    csockettcp.cpp
    csocketudp.cpp
    ctimer.cpp
    cvideo.cpp
    cvisual.cpp
    pig.cpp
    pigfuncoesbasicas.cpp
)

add_library(Pig ${pig_SRCS})

# Add definitions for targets
# Values:
#   * Debug: -DPIG_DEBUG=1
#   * Release: -DPIG_DEBUG=0
#   * other: -DPIG_DEBUG=0
target_compile_definitions(Pig PUBLIC "PIG_DEBUG=$<CONFIG:Debug>")

set(generated_headers "${CMAKE_CURRENT_BINARY_DIR}/generated_headers")
set(pig_export "${generated_headers}/pig/pig_export.h")

# https://cmake.org/cmake/help/v3.9/module/GenerateExportHeader.html
include(GenerateExportHeader)
generate_export_header(Pig EXPORT_FILE_NAME ${pig_export})

# Global includes. Used by all targets
# Note:
#   * header location in project: Foo/Source/foo/Bar.hpp
#   * header can be included by C++ code `#include <foo/Bar.hpp>`
#   * header location in project: ${CMAKE_CURRENT_BINARY_DIR}/generated_headers/foo/BAR_EXPORT.h
#   * header can be included by: `#include <BAR_EXPORT.h>`
target_include_directories(
    Pig PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>"
    "$<BUILD_INTERFACE:${generated_headers}>"
)

# link required library
target_link_libraries(Pig PUBLIC SDL2::SDL2)

# Introduce variables:
# * CMAKE_INSTALL_LIBDIR
# * CMAKE_INSTALL_BINDIR
# * CMAKE_INSTALL_INCLUDEDIR
include(GNUInstallDirs)

# Layout. This works for all platforms:
#   * <prefix>/lib*/cmake/<PROJECT-NAME>
#   * <prefix>/lib*/
#   * <prefix>/include/
set(config_install_dir "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")

set(generated_dir "${CMAKE_CURRENT_BINARY_DIR}/generated")

# Configuration
set(version_config "${generated_dir}/${PROJECT_NAME}ConfigVersion.cmake")
set(project_config "${generated_dir}/${PROJECT_NAME}Config.cmake")
set(TARGETS_EXPORT_NAME "${PROJECT_NAME}Targets")
set(namespace "${PROJECT_NAME}::")

# Include module with fuction 'write_basic_package_version_file'
include(CMakePackageConfigHelpers)

# Configure '<PROJECT-NAME>ConfigVersion.cmake'
# Use:
#   * PROJECT_VERSION
write_basic_package_version_file(
    "${version_config}" COMPATIBILITY AnyNewerVersion
)

# Configure '<PROJECT-NAME>Config.cmake'
# Use variables:
#   * TARGETS_EXPORT_NAME
#   * PROJECT_NAME
configure_package_config_file(
    "../cmake/Config.cmake.in"
    "${project_config}"
    INSTALL_DESTINATION "${config_install_dir}"
)

# Targets:
#   * <prefix>/lib/libbar.a
#   * <prefix>/lib/libbaz.a
#   * header location after install: <prefix>/include/foo/Bar.hpp
#   * headers can be included by C++ code `#include <foo/Bar.hpp>`
install(
    TARGETS Pig
    EXPORT "${TARGETS_EXPORT_NAME}"
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
    INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

# Headers:
#   * Source/foo/Bar.hpp -> <prefix>/include/foo/Bar.hpp
#   * Source/foo/Baz.hpp -> <prefix>/include/foo/Baz.hpp
install(
    DIRECTORY .
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    FILES_MATCHING PATTERN "*.h"
)

# Export headers:
#   * ${CMAKE_CURRENT_BINARY_DIR}/.../BAR_EXPORT.h -> <prefix>/include/foo/BAR_EXPORT.h
#   * ${CMAKE_CURRENT_BINARY_DIR}/.../BAZ_EXPORT.h -> <prefix>/include/foo/BAZ_EXPORT.h
install(
    FILES "${pig_export}"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/pig"
)

# Config
#   * <prefix>/lib/cmake/Foo/FooConfig.cmake
#   * <prefix>/lib/cmake/Foo/FooConfigVersion.cmake
install(
    FILES "${project_config}" "${version_config}"
    DESTINATION "${config_install_dir}"
)

# Config
#   * <prefix>/lib/cmake/Foo/FooTargets.cmake
install(
    EXPORT "${TARGETS_EXPORT_NAME}"
    NAMESPACE "${namespace}"
    DESTINATION "${config_install_dir}"
)
