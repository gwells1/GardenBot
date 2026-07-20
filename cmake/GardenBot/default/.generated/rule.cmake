# The following functions contains all the flags passed to the different build stages.

set(PACK_REPO_PATH "C:/Users/gregw/.mchp_packs" CACHE PATH "Path to the root of a pack repository.")

function(GardenBot_default_default_XC32_assemble_rule target)
    set(options
        "-g"
        "${ASSEMBLER_PRE}"
        "-mprocessor=32CM1216MC00032"
        "-Wa,--defsym=__MPLAB_BUILD=1${MP_EXTRA_AS_POST}"
        "-mdfp=${PACK_REPO_PATH}/Microchip/PIC32CM-MC_DFP/1.4.67/PIC32CM1216MC00032")
    list(REMOVE_ITEM options "")
    target_compile_options(${target} PRIVATE "${options}")
endfunction()
function(GardenBot_default_default_XC32_assembleWithPreprocess_rule target)
    set(options
        "-x"
        "assembler-with-cpp"
        "-g"
        "${MP_EXTRA_AS_PRE}"
        "-mdfp=${PACK_REPO_PATH}/Microchip/PIC32CM-MC_DFP/1.4.67/PIC32CM1216MC00032"
        "-mprocessor=32CM1216MC00032"
        "-Wa,--defsym=__MPLAB_BUILD=1${MP_EXTRA_AS_POST}")
    list(REMOVE_ITEM options "")
    target_compile_options(${target} PRIVATE "${options}")
    target_compile_definitions(${target} PRIVATE "XPRJ_default=default")
endfunction()
function(GardenBot_default_default_XC32_compile_rule target)
    set(options
        "-g"
        "${CC_PRE}"
        "-x"
        "c"
        "-c"
        "-mprocessor=32CM1216MC00032"
        "-mdfp=${PACK_REPO_PATH}/Microchip/PIC32CM-MC_DFP/1.4.67/PIC32CM1216MC00032")
    list(REMOVE_ITEM options "")
    target_compile_options(${target} PRIVATE "${options}")
    target_compile_definitions(${target} PRIVATE "XPRJ_default=default")
endfunction()
function(GardenBot_default_default_XC32_compile_cpp_rule target)
    set(options
        "-g"
        "${CC_PRE}"
        "-mprocessor=32CM1216MC00032"
        "-frtti"
        "-fexceptions"
        "-fno-check-new"
        "-fenforce-eh-specs"
        "-fno-common"
        "-mdfp=${PACK_REPO_PATH}/Microchip/PIC32CM-MC_DFP/1.4.67/PIC32CM1216MC00032")
    list(REMOVE_ITEM options "")
    target_compile_options(${target} PRIVATE "${options}")
    target_compile_definitions(${target} PRIVATE "XPRJ_default=default")
endfunction()
function(GardenBot_default_dependentObject_rule target)
    set(options
        "-mprocessor=32CM1216MC00032"
        "-mdfp=${PACK_REPO_PATH}/Microchip/PIC32CM-MC_DFP/1.4.67/PIC32CM1216MC00032")
    list(REMOVE_ITEM options "")
    target_compile_options(${target} PRIVATE "${options}")
endfunction()
function(GardenBot_default_link_rule target)
    set(options
        "-g"
        "${MP_EXTRA_LD_PRE}"
        "-mprocessor=32CM1216MC00032"
        "-Wl,--defsym=__MPLAB_BUILD=1${MP_EXTRA_LD_POST},-Map=mem.map,--report-mem,--memorysummary,memoryfile.xml"
        "-mdfp=${PACK_REPO_PATH}/Microchip/PIC32CM-MC_DFP/1.4.67/PIC32CM1216MC00032")
    list(REMOVE_ITEM options "")
    target_link_options(${target} PRIVATE "${options}")
    target_compile_definitions(${target} PRIVATE "XPRJ_default=default")
endfunction()
function(GardenBot_default_bin2hex_rule target)
    add_custom_target(
        GardenBot_default_Bin2Hex ALL
        COMMAND ${MP_BIN2HEX} ${GardenBot_default_image_name}
        WORKING_DIRECTORY ${GardenBot_default_output_dir}
        BYPRODUCTS "${GardenBot_default_output_dir}/${GardenBot_default_image_base_name}.hex"
        COMMENT "Convert build file to .hex")
    add_dependencies(GardenBot_default_Bin2Hex ${target})
endfunction()
