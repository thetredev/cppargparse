
set(CPPARGPARSE_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/globals.h
    ${CMAKE_CURRENT_SOURCE_DIR}/parser.h
    ${CMAKE_CURRENT_SOURCE_DIR}/types.h

    ${CMAKE_CURRENT_SOURCE_DIR}/type_traits/type_traits.h
    ${CMAKE_CURRENT_SOURCE_DIR}/type_traits/type_traits_float.h
    ${CMAKE_CURRENT_SOURCE_DIR}/type_traits/type_traits_int.h
    ${CMAKE_CURRENT_SOURCE_DIR}/type_traits/type_traits_string.h
    ${CMAKE_CURRENT_SOURCE_DIR}/type_traits/type_traits_stub.h

    PARENT_SCOPE
)
