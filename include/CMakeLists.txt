
set(CPPARGPARSE_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/cppargparse/globals.h
    ${CMAKE_CURRENT_SOURCE_DIR}/cppargparse/parser.h
    ${CMAKE_CURRENT_SOURCE_DIR}/cppargparse/types.h

    ${CMAKE_CURRENT_SOURCE_DIR}/cppargparse/type_traits/type_traits.h
    ${CMAKE_CURRENT_SOURCE_DIR}/cppargparse/type_traits/type_traits_double.h
    ${CMAKE_CURRENT_SOURCE_DIR}/cppargparse/type_traits/type_traits_float.h
    ${CMAKE_CURRENT_SOURCE_DIR}/cppargparse/type_traits/type_traits_int.h
    ${CMAKE_CURRENT_SOURCE_DIR}/cppargparse/type_traits/type_traits_string.h
    ${CMAKE_CURRENT_SOURCE_DIR}/cppargparse/type_traits/type_traits_stub.h

    PARENT_SCOPE
)
