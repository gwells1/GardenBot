set(DEPENDENT_MP_BIN2HEXGardenBot_default_sQoKaYgV "/opt/microchip/xc32/v5.00/bin/xc32-bin2hex")
set(DEPENDENT_DEPENDENT_TARGET_ELFGardenBot_default_sQoKaYgV ${CMAKE_CURRENT_LIST_DIR}/../../../../out/GardenBot/default.elf)
set(DEPENDENT_TARGET_DIRGardenBot_default_sQoKaYgV ${CMAKE_CURRENT_LIST_DIR}/../../../../out/GardenBot)
set(DEPENDENT_BYPRODUCTSGardenBot_default_sQoKaYgV ${DEPENDENT_TARGET_DIRGardenBot_default_sQoKaYgV}/${sourceFileNameGardenBot_default_sQoKaYgV}.c)
add_custom_command(
    OUTPUT ${DEPENDENT_TARGET_DIRGardenBot_default_sQoKaYgV}/${sourceFileNameGardenBot_default_sQoKaYgV}.c
    COMMAND ${DEPENDENT_MP_BIN2HEXGardenBot_default_sQoKaYgV} --image ${DEPENDENT_DEPENDENT_TARGET_ELFGardenBot_default_sQoKaYgV} --image-generated-c ${sourceFileNameGardenBot_default_sQoKaYgV}.c --image-generated-h ${sourceFileNameGardenBot_default_sQoKaYgV}.h --image-copy-mode ${modeGardenBot_default_sQoKaYgV} --image-offset ${addressGardenBot_default_sQoKaYgV} 
    WORKING_DIRECTORY ${DEPENDENT_TARGET_DIRGardenBot_default_sQoKaYgV}
    DEPENDS ${DEPENDENT_DEPENDENT_TARGET_ELFGardenBot_default_sQoKaYgV})
add_custom_target(
    dependent_produced_source_artifactGardenBot_default_sQoKaYgV 
    DEPENDS ${DEPENDENT_TARGET_DIRGardenBot_default_sQoKaYgV}/${sourceFileNameGardenBot_default_sQoKaYgV}.c
    )
