set(DEPENDENT_MP_BIN2HEXGardenBot_default_b6TNGsHU "c:/Program Files/Microchip/xc32/v5.00/bin/xc32-bin2hex.exe")
set(DEPENDENT_DEPENDENT_TARGET_ELFGardenBot_default_b6TNGsHU ${CMAKE_CURRENT_LIST_DIR}/../../../../out/GardenBot/default.elf)
set(DEPENDENT_TARGET_DIRGardenBot_default_b6TNGsHU ${CMAKE_CURRENT_LIST_DIR}/../../../../out/GardenBot)
set(DEPENDENT_BYPRODUCTSGardenBot_default_b6TNGsHU ${DEPENDENT_TARGET_DIRGardenBot_default_b6TNGsHU}/${sourceFileNameGardenBot_default_b6TNGsHU}.c)
add_custom_command(
    OUTPUT ${DEPENDENT_TARGET_DIRGardenBot_default_b6TNGsHU}/${sourceFileNameGardenBot_default_b6TNGsHU}.c
    COMMAND ${DEPENDENT_MP_BIN2HEXGardenBot_default_b6TNGsHU} --image ${DEPENDENT_DEPENDENT_TARGET_ELFGardenBot_default_b6TNGsHU} --image-generated-c ${sourceFileNameGardenBot_default_b6TNGsHU}.c --image-generated-h ${sourceFileNameGardenBot_default_b6TNGsHU}.h --image-copy-mode ${modeGardenBot_default_b6TNGsHU} --image-offset ${addressGardenBot_default_b6TNGsHU} 
    WORKING_DIRECTORY ${DEPENDENT_TARGET_DIRGardenBot_default_b6TNGsHU}
    DEPENDS ${DEPENDENT_DEPENDENT_TARGET_ELFGardenBot_default_b6TNGsHU})
add_custom_target(
    dependent_produced_source_artifactGardenBot_default_b6TNGsHU 
    DEPENDS ${DEPENDENT_TARGET_DIRGardenBot_default_b6TNGsHU}/${sourceFileNameGardenBot_default_b6TNGsHU}.c
    )
