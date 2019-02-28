MACRO(ADD_QT_DEPENDENCY)
  IF(PROJECT_USE_QT4)
    #FIND_PACKAGE(Qt4 REQUIRED QtXml)
    FIND_PACKAGE(Qt4 REQUIRED QtCore QtGui QtOpenGl QtNetwork QtXml)
    SET(PROJECT_QT_LIBS Qt4::QtCore Qt4::QtGui Qt4::QtOpenGl Qt4::QtNetwork Qt4::QtXml)
    SET(PKG_CONFIG_EXTRA "qtversion=${QT_VERSION_MAJOR}.${QT_VERSION_MINOR}.${QT_VERSION_PATCH}\n${PKG_CONFIG_EXTRA}")
    INCLUDE(${QT_USE_FILE})
    SET(PROJECT_QT_INCLUDE_DIRS ${QT_INCLUDE_DIRS})
  ELSE()
    FOREACH (component "Xml" "Core" "Widgets" "Gui" "OpenGL" "Network" "Concurrent")
      FIND_PACKAGE ("Qt5${component}" REQUIRED)
      LIST(APPEND PROJECT_QT_INCLUDE_DIRS ${Qt5${component}_INCLUDE_DIRS})
      LIST(APPEND PROJECT_QT_LIBS Qt5::${component})
    ENDFOREACH ()
    SET(PKG_CONFIG_EXTRA "qtversion=${Qt5Core_VERSION}\n${PKG_CONFIG_EXTRA}")
  ENDIF()

  SET(CMAKE_INCLUDE_CURRENT_DIR ON)
  SET(CMAKE_AUTOMOC ON)
  SET(CMAKE_AUTOUIC ON)

  INCLUDE_DIRECTORIES(SYSTEM ${PROJECT_QT_INCLUDE_DIRS})
ENDMACRO(ADD_QT_DEPENDENCY)