find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)

set(PKG_CONFIG_POSTFIX "lib/pkgconfig/")

# Detect platform and Set up PKG_CONFIG_PATH to find dependencies
if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    # Detect typical Homebrew install prefixes
    if(EXISTS "/opt/homebrew")
        # TODO: Add pkg-config paths for Apple Silicon Homebrew
        set(PKG_CONFIG_PREFIX "")
    elseif(EXISTS "/usr/local")
        # Intel Mac Homebrew
        set(PKG_CONFIG_PREFIX "/usr/local/opt")
    elseif(EXISTS "/opt/local")
        # TODO: Add pkg-config paths for MacPorts
        set(PKG_CONFIG_PREFIX "")
    endif()
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
#TODO: Add pkg-config paths for common Linux distros
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
#TODO: Add pkg-config paths for common Windows package managers
endif()

# Find dependencies
find_path(GTKMM4_PATH
    NAMES gtkmm-4.0.pc
    PATHS ${PKG_CONFIG_PREFIX}/gtkmm4/${PKG_CONFIG_POSTFIX}
)

find_path(LIBJPEG_PATH
    NAMES libjpeg.pc
    PATHS ${PKG_CONFIG_PREFIX}/jpeg/${PKG_CONFIG_POSTFIX}
)

find_path(LIBZSTD_PATH
    NAMES libzstd.pc
    PATHS ${PKG_CONFIG_PREFIX}/zstd/${PKG_CONFIG_POSTFIX}
)

find_path(LIBEPOXY_PATH
    NAMES epoxy.pc
    PATHS ${PKG_CONFIG_PREFIX}/libepoxy/${PKG_CONFIG_POSTFIX}
)

# Expose as a cache variable so user can override in cmake-gui / ccmake
set(PKG_CONFIG_PATH "\
${GTKMM4_PATH}\
:${LIBJPEG_PATH}\
:${LIBZSTD_PATH}\
:${LIBEPOXY_PATH}\
:$ENV{PKG_CONFIG_PATH}\
"
    CACHE STRING "Path for pkg-config to search .pc files")

message(STATUS "Using PKG_CONFIG_PATH: ${PKG_CONFIG_PATH}")

# Apply it for pkg_check_modules
set(ENV{PKG_CONFIG_PATH} "${PKG_CONFIG_PATH}")

pkg_check_modules(GTKMM REQUIRED gtkmm-4.0)
pkg_check_modules(EPOXY REQUIRED epoxy)

