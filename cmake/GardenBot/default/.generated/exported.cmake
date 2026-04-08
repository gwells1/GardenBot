set(DEPENDENT_MP_BIN2HEXGardenBot_default_1S4E_cJp "c:/Program Files/Microchip/xc32/v5.00/bin/xc32-bin2hex.exe")
set(DEPENDENT_DEPENDENT_TARGET_ELFGardenBot_default_1S4E_cJp ${CMAKE_CURRENT_LIST_DIR}/../../../../out/GardenBot/default.elf)
set(DEPENDENT_TARGET_DIRGardenBot_default_1S4E_cJp ${CMAKE_CURRENT_LIST_DIR}/../../../../out/GardenBot)
set(DEPENDENT_BYPRODUCTSGardenBot_default_1S4E_cJp ${DEPENDENT_TARGET_DIRGardenBot_default_1S4E_cJp}/${sourceFileNameGardenBot_default_1S4E_cJp}.c)
add_custom_command(
    OUTPUT ${DEPENDENT_TARGET_DIRGardenBot_default_1S4E_cJp}/${sourceFileNameGardenBot_default_1S4E_cJp}.c
    COMMAND ${DEPENDENT_MP_BIN2HEXGardenBot_default_1S4E_cJp} --image ${DEPENDENT_DEPENDENT_TARGET_ELFGardenBot_default_1S4E_cJp} --image-generated-c ${sourceFileNameGardenBot_default_1S4E_cJp}.c --image-generated-h ${sourceFileNameGardenBot_default_1S4E_cJp}.h --image-copy-mode ${modeGardenBot_default_1S4E_cJp} --image-offset ${addressGardenBot_default_1S4E_cJp} 
    WORKING_DIRECTORY ${DEPENDENT_TARGET_DIRGardenBot_default_1S4E_cJp}
    DEPENDS ${DEPENDENT_DEPENDENT_TARGET_ELFGardenBot_default_1S4E_cJp})
add_custom_target(
    dependent_produced_source_artifactGardenBot_default_1S4E_cJp 
    DEPENDS ${DEPENDENT_TARGET_DIRGardenBot_default_1S4E_cJp}/${sourceFileNameGardenBot_default_1S4E_cJp}.c
    )
