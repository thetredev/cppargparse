
#
# sample: application usage
#
add_executable(sample_usage_traditional
    ${CMAKE_CURRENT_SOURCE_DIR}/traditional/usage.cpp
)

add_executable(sample_usage_callback
    ${CMAKE_CURRENT_SOURCE_DIR}/callback/usage.cpp
)


#
# sample: required arguments
#
add_executable(sample_required_callback
    ${CMAKE_CURRENT_SOURCE_DIR}/callback/required.cpp
)

add_executable(sample_required_traditional
    ${CMAKE_CURRENT_SOURCE_DIR}/traditional/required.cpp
)


#
# samples: build all samples
#
add_custom_target(samples)
add_dependencies(samples
    sample_usage_traditional
    sample_usage_callback

    sample_required_callback
    sample_required_traditional
)
