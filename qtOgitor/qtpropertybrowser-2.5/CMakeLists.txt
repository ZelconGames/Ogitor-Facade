PROJECT(QtSolutions_PropertyBrowser)
SET(QT_MIN_VERSION "4.5.0")
FIND_PACKAGE(Qt4 REQUIRED)

IF(NOT QT4_FOUND)
  MESSAGE(SEND_ERROR "Failed to find Qt 4.5 or greater.")
ELSE(NOT QT4_FOUND)

  INCLUDE(${QT_USE_FILE})
  SET(CMAKE_PACKAGE_QTGUI TRUE)

  SET(qtpropertyeditor_SRCS
	src/qtpropertybrowser.cpp
	src/qtpropertymanager.cpp
	src/qteditorfactory.cpp
	src/qtvariantproperty.cpp
	src/qttreepropertybrowser.cpp
	src/qtbuttonpropertybrowser.cpp
	src/qtgroupboxpropertybrowser.cpp
	src/qtpropertybrowserutils.cpp
   )

  SET(qtpropertyeditor_HDRS
  src/qtpropertybrowser.h
  src/qtpropertymanager.h
  src/qteditorfactory.h
  src/qtvariantproperty.h
  src/qttreepropertybrowser.h
  src/qtbuttonpropertybrowser.h
  src/qtgroupboxpropertybrowser.h
  src/qtpropertybrowserutils_p.h
  )

  include_directories(${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}/src)
  include_directories(src)
  INCLUDE_DIRECTORIES(
   ${QT_INCLUDE_DIR}
  )

qt4_generate_moc(
  src/qtpropertybrowser.h
  ${CMAKE_CURRENT_BINARY_DIR}/moc_qtpropertybrowser.cpp
)
qt4_generate_moc(
  src/qtpropertymanager.h
  ${CMAKE_CURRENT_BINARY_DIR}/moc_qtpropertymanager.cpp
)
qt4_generate_moc(
  src/qteditorfactory.h
  ${CMAKE_CURRENT_BINARY_DIR}/moc_qteditorfactory.cpp
)
qt4_generate_moc(
  src/qtvariantproperty.h
  ${CMAKE_CURRENT_BINARY_DIR}/moc_qtvariantproperty.cpp
)
qt4_generate_moc(
  src/qttreepropertybrowser.h
  ${CMAKE_CURRENT_BINARY_DIR}/moc_qttreepropertybrowser.cpp
)
qt4_generate_moc(
  src/qtbuttonpropertybrowser.h
  ${CMAKE_CURRENT_BINARY_DIR}/moc_qtbuttonpropertybrowser.cpp
)
qt4_generate_moc(
  src/qtgroupboxpropertybrowser.h
  ${CMAKE_CURRENT_BINARY_DIR}/moc_qtgroupboxpropertybrowser.cpp
)
qt4_generate_moc(
  src/qtpropertymanager.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/qtpropertymanager.moc
)
qt4_generate_moc(
  src/qteditorfactory.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/qteditorfactory.moc
)
qt4_generate_moc(
  src/qttreepropertybrowser.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/qttreepropertybrowser.moc
)

set(
  qtpropertyeditor_HEADERS_ONLY_MOC
  ${CMAKE_CURRENT_BINARY_DIR}/moc_qtpropertybrowser.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/moc_qtpropertymanager.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/moc_qteditorfactory.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/moc_qtvariantproperty.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/moc_qttreepropertybrowser.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/moc_qtbuttonpropertybrowser.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/moc_qtgroupboxpropertybrowser.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/qtpropertymanager.moc
  ${CMAKE_CURRENT_BINARY_DIR}/qteditorfactory.moc
  ${CMAKE_CURRENT_BINARY_DIR}/qttreepropertybrowser.moc
)

set_source_files_properties(
  ${qtpropertyeditor_HEADERS_ONLY_MOC}
  PROPERTIES
    HEADER_FILE_ONLY true
)

qt4_generate_moc(
  src/qtpropertybrowserutils_p.h
  ${CMAKE_CURRENT_BINARY_DIR}/moc_qtpropertybrowserutils_p.cpp
)

set(
  qtpropertyeditor_HEADERS_MOC
  ${CMAKE_CURRENT_BINARY_DIR}/moc_qtpropertybrowserutils_p.cpp
)

set(
  qtpropertyeditor_MOC
  ${qtpropertyeditor_HEADERS_MOC}
  ${qtpropertyeditor_HEADERS_ONLY_MOC}
)

qt4_add_resources(
  qtpropertyeditor_RESOURCES
  src/qtpropertybrowser.qrc
)

#set(
#  extension_SRCS
#  main.cpp
#)

#qt4_generate_moc(
#  main.cpp
#  ${CMAKE_CURRENT_SOURCE_DIR}/main.moc
#)

#set(
#  extension_MOC
#  ${CMAKE_CURRENT_SOURCE_DIR}/main.moc
#)

#set_source_files_properties(
#  ${extension_MOC}
#  PROPERTIES
#    HEADER_FILE_ONLY true
#)

  QT4_ADD_RESOURCES(RESOURCE_SRCS src/qtpropertybrowser.qrc)

  #${extension_SRCS}

  SET(SRCS   ${extension_MOC}
  ${qtpropertyeditor_MOC}
  ${qtpropertyeditor_SRCS}
  ${qtpropertyeditor_RESOURCES}
  ${qtpropertyeditor_HDRS}
  )

  ADD_LIBRARY(QtSolutions_PropertyBrowser SHARED ${SRCS})

  TARGET_LINK_LIBRARIES(QtSolutions_PropertyBrowser ${QT_LIBRARIES})

  ADD_DEFINITIONS(${QT_DEFINITIONS})
  ADD_DEFINITIONS(-DQT_DLL)
  ADD_DEFINITIONS(-DQT_QTPROPERTYBROWSER_EXPORT)
  ADD_DEFINITIONS(-DQT_PLUGIN)
  #ADD_DEFINITIONS(-DQT_NO_DEBUG)
  ADD_DEFINITIONS(-DQT_SHARED)

IF(WIN32)
	add_custom_command( TARGET QtSolutions_PropertyBrowser POST_BUILD
		COMMAND copy \"$(TargetPath)\" ..\\..\\RunPath\\bin )
ENDIF(WIN32)

IF(WIN32)
install(TARGETS QtSolutions_PropertyBrowser
	RUNTIME DESTINATION bin
	CONFIGURATIONS Release RelWithDebInfo MinSizeRel)
ENDIF(WIN32)

IF(UNIX AND NOT APPLE)

set_target_properties( QtSolutions_PropertyBrowser PROPERTIES OUTPUT_NAME "QtSolutions_PropertyBrowser_Ogitor" VERSION
${OGITOR_VERSION_STRING} SOVERSION ${abi_version} )

install(TARGETS QtSolutions_PropertyBrowser
    LIBRARY DESTINATION lib
    CONFIGURATIONS Release RelWithDebInfo MinSizeRel)

ENDIF(UNIX AND NOT APPLE)

ENDIF(NOT QT4_FOUND)

