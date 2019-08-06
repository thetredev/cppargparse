
set(CPPARGPARSE_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/cppargparse/globals.h
    ${CMAKE_CURRENT_SOURCE_DIR}/cppargparse/parser.h
    ${CMAKE_CURRENT_SOURCE_DIR}/cppargparse/types.h

    ${CMAKE_CURRENT_SOURCE_DIR}/cppargparse/type_traits/type_traits.h
    ${CMAKE_CURRENT_SOURCE_DIR}/cppargparse/type_traits/double.h
    ${CMAKE_CURRENT_SOURCE_DIR}/cppargparse/type_traits/float.h
    ${CMAKE_CURRENT_SOURCE_DIR}/cppargparse/type_traits/int.h
    ${CMAKE_CURRENT_SOURCE_DIR}/cppargparse/type_traits/string.h
    ${CMAKE_CURRENT_SOURCE_DIR}/cppargparse/type_traits/stub.h

    PARENT_SCOPE
)
