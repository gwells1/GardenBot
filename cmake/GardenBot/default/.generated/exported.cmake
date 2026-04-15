set(DEPENDENT_MP_BIN2HEXGardenBot_default_eAoZMXWI "c:/Program Files/Microchip/xc32/v5.00/bin/xc32-bin2hex.exe")
set(DEPENDENT_DEPENDENT_TARGET_ELFGardenBot_default_eAoZMXWI ${CMAKE_CURRENT_LIST_DIR}/../../../../out/GardenBot/default.elf)
set(DEPENDENT_TARGET_DIRGardenBot_default_eAoZMXWI ${CMAKE_CURRENT_LIST_DIR}/../../../../out/GardenBot)
set(DEPENDENT_BYPRODUCTSGardenBot_default_eAoZMXWI ${DEPENDENT_TARGET_DIRGardenBot_default_eAoZMXWI}/${sourceFileNameGardenBot_default_eAoZMXWI}.c)
add_custom_command(
    OUTPUT ${DEPENDENT_TARGET_DIRGardenBot_default_eAoZMXWI}/${sourceFileNameGardenBot_default_eAoZMXWI}.c
    COMMAND ${DEPENDENT_MP_BIN2HEXGardenBot_default_eAoZMXWI} --image ${DEPENDENT_DEPENDENT_TARGET_ELFGardenBot_default_eAoZMXWI} --image-generated-c ${sourceFileNameGardenBot_default_eAoZMXWI}.c --image-generated-h ${sourceFileNameGardenBot_default_eAoZMXWI}.h --image-copy-mode ${modeGardenBot_default_eAoZMXWI} --image-offset ${addressGardenBot_default_eAoZMXWI} 
    WORKING_DIRECTORY ${DEPENDENT_TARGET_DIRGardenBot_default_eAoZMXWI}
    DEPENDS ${DEPENDENT_DEPENDENT_TARGET_ELFGardenBot_default_eAoZMXWI})
add_custom_target(
    dependent_produced_source_artifactGardenBot_default_eAoZMXWI 
    DEPENDS ${DEPENDENT_TARGET_DIRGardenBot_default_eAoZMXWI}/${sourceFileNameGardenBot_default_eAoZMXWI}.c
    )
