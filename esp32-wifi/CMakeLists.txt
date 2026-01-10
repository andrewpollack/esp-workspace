cmake_minimum_required(VERSION 3.16)

set(EXTRA_COMPONENT_DIRS ${CMAKE_CURRENT_LIST_DIR}/../common)

# Project configuration
set(MDNS_HOSTNAME "esp32-wifi")

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(esp32-wifi)

# Pass hostname to compiler
idf_build_set_property(COMPILE_DEFINITIONS "MDNS_HOSTNAME=\"${MDNS_HOSTNAME}\"" APPEND)
