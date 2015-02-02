##############################################################
# Copyright(c) 2015 Institute of Navigation
# http://www.ion.org
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
# Register GNSS_METADATA API: no dependencies, to be ON by default.
##############################################################

LIBUHD_REGISTER_COMPONENT("GNSS METADATA API" ENABLE_METADATA_API ON "" OFF)

##############################################################
# Conditionally configure GNSS METADATA API.
##############################################################

IF(ENABLE_METADATA_API)

    INCLUDE_DIRECTORIES(
        ${TINYXML_INCLUDE_DIR}
    )

    SET(METADATA_API_sources
        ${CMAKE_CURRENT_SOURCE_DIR}/AnyUri.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/AttributedObject.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Band.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/BaseTypes.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Block.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Chunk.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Cluster.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Comment.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Date.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Duration.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/File.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Frequency.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Lane.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Lump.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Metadata.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Position.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Session.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Stream.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Xml/AnyUriTranslator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Xml/BandTranslator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Xml/BlockTranslator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Xml/ChunkTranslator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Xml/ClusterTranslator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Xml/DurationTranslator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Xml/FileSetTranslator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Xml/FileTranslator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Xml/FrequencyTranslator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Xml/LaneTranslator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Xml/LumpTranslator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Xml/MetadataTranslator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Xml/OscillatorTranslator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Xml/PositionTranslator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Xml/RfConfigTranslator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Xml/SessionTranslator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Xml/SourceTranslator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Xml/StreamTranslator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Xml/SystemTranslator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Xml/Translator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Xml/XmlProcessor.cpp
    )        

    ADD_LIBRARY(GnssMetadata SHARED ${METADATA_API_sources})

     # set library properties

    SET_TARGET_PROPERTIES(GnssMetadata PROPERTIES
        VERSION ${${PROJECT_NAME}_VERSION_FULL}
    )

    IF(UNIX)
        SET_TARGET_PROPERTIES(GnssMetadata PROPERTIES
            SOVERSION ${${PROJECT_NAME}_VERSION_PATCH}
        )
    ENDIF(UNIX)

    IF(APPLE)
        SET_TARGET_PROPERTIES(GnssMetadata PROPERTIES
            INSTALL_NAME_DIR "${CMAKE_INSTALL_PREFIX}/${LIBRARY_DIR}"
        )
    ENDIF(APPLE)

    # Install information

    INSTALL(TARGETS GnssMetadata
        LIBRARY DESTINATION ${LIBRARY_DIR} COMPONENT libraries # .so file
        ARCHIVE DESTINATION ${LIBRARY_DIR} COMPONENT libraries # .lib file
        RUNTIME DESTINATION ${RUNTIME_DIR} COMPONENT libraries # .dll file
    )

ENDIF(ENABLE_METADATA_API)
