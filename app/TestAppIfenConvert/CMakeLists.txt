##############################################################
# Copyright(c) 2013 Loctronix Corporation
# http://www.loctronix.com
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
##############################################################

##############################################################
# Common additions
##############################################################


##############################################################
# Register "TestAppIfenConvert" component,
##############################################################

LIBUHD_REGISTER_COMPONENT("TestAppIfenConvert"
    ENABLE_TESTIFENCONVERT ON "ENABLE_METADATA_API" OFF)

IF(ENABLE_TESTIFENCONVERT)

##############################################################
# Create executables
##############################################################

    ADD_EXECUTABLE(TestAppIfenConvert TestAppIfenConvert.cpp)

##############################################################
# Conditionally embed the GnssMetadata library
##############################################################

    TARGET_LINK_LIBRARIES(TestAppIfenConvert GnssMetadata tinyxml2 rt)

##############################################################
# Install information
##############################################################

    UHD_INSTALL(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/TestAppIfenConvert
        DESTINATION ${RUNTIME_DIR} COMPONENT utilities)

ENDIF()
