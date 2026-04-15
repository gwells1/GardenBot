include("${CMAKE_CURRENT_LIST_DIR}/rule.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/file.cmake")

set(GardenBot_default_library_list )

# Handle files with suffix s, for group default-XC32
if(GardenBot_default_default_XC32_FILE_TYPE_assemble)
add_library(GardenBot_default_default_XC32_assemble OBJECT ${GardenBot_default_default_XC32_FILE_TYPE_assemble})
    GardenBot_default_default_XC32_assemble_rule(GardenBot_default_default_XC32_assemble)
    list(APPEND GardenBot_default_library_list "$<TARGET_OBJECTS:GardenBot_default_default_XC32_assemble>")

endif()

# Handle files with suffix S, for group default-XC32
if(GardenBot_default_default_XC32_FILE_TYPE_assembleWithPreprocess)
add_library(GardenBot_default_default_XC32_assembleWithPreprocess OBJECT ${GardenBot_default_default_XC32_FILE_TYPE_assembleWithPreprocess})
    GardenBot_default_default_XC32_assembleWithPreprocess_rule(GardenBot_default_default_XC32_assembleWithPreprocess)
    list(APPEND GardenBot_default_library_list "$<TARGET_OBJECTS:GardenBot_default_default_XC32_assembleWithPreprocess>")

endif()

# Handle files with suffix [cC], for group default-XC32
if(GardenBot_default_default_XC32_FILE_TYPE_compile)
add_library(GardenBot_default_default_XC32_compile OBJECT ${GardenBot_default_default_XC32_FILE_TYPE_compile})
    GardenBot_default_default_XC32_compile_rule(GardenBot_default_default_XC32_compile)
    list(APPEND GardenBot_default_library_list "$<TARGET_OBJECTS:GardenBot_default_default_XC32_compile>")

endif()

# Handle files with suffix cpp, for group default-XC32
if(GardenBot_default_default_XC32_FILE_TYPE_compile_cpp)
add_library(GardenBot_default_default_XC32_compile_cpp OBJECT ${GardenBot_default_default_XC32_FILE_TYPE_compile_cpp})
    GardenBot_default_default_XC32_compile_cpp_rule(GardenBot_default_default_XC32_compile_cpp)
    list(APPEND GardenBot_default_library_list "$<TARGET_OBJECTS:GardenBot_default_default_XC32_compile_cpp>")

endif()

# Handle files with suffix [cC], for group default-XC32
if(GardenBot_default_default_XC32_FILE_TYPE_dependentObject)
add_library(GardenBot_default_default_XC32_dependentObject OBJECT ${GardenBot_default_default_XC32_FILE_TYPE_dependentObject})
    GardenBot_default_default_XC32_dependentObject_rule(GardenBot_default_default_XC32_dependentObject)
    list(APPEND GardenBot_default_library_list "$<TARGET_OBJECTS:GardenBot_default_default_XC32_dependentObject>")

endif()

# Handle files with suffix elf, for group default-XC32
if(GardenBot_default_default_XC32_FILE_TYPE_bin2hex)
add_library(GardenBot_default_default_XC32_bin2hex OBJECT ${GardenBot_default_default_XC32_FILE_TYPE_bin2hex})
    GardenBot_default_default_XC32_bin2hex_rule(GardenBot_default_default_XC32_bin2hex)
    list(APPEND GardenBot_default_library_list "$<TARGET_OBJECTS:GardenBot_default_default_XC32_bin2hex>")

endif()


# Main target for this project
add_executable(GardenBot_default_image_eAoZMXWI ${GardenBot_default_library_list})

set_target_properties(GardenBot_default_image_eAoZMXWI PROPERTIES
    OUTPUT_NAME "default"
    SUFFIX ".elf"
    RUNTIME_OUTPUT_DIRECTORY "${GardenBot_default_output_dir}")
target_link_libraries(GardenBot_default_image_eAoZMXWI PRIVATE ${GardenBot_default_default_XC32_FILE_TYPE_link})

# Add the link options from the rule file.
GardenBot_default_link_rule( GardenBot_default_image_eAoZMXWI)

# Call bin2hex function from the rule file
GardenBot_default_bin2hex_rule(GardenBot_default_image_eAoZMXWI)

