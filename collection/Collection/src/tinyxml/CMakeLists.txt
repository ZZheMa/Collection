set(SRCS
    tinystr.h
    tinystr.cpp
    tinyxml.h
    tinyxml.cpp
    tinyxmlerror.cpp
    tinyxmlparser.cpp
    )

# Enable TinyXml STL
add_definitions(-DTIXML_USE_STL)

add_library(tinyxml ${SRCS})

