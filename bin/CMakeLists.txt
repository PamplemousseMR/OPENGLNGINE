#=======================================
#                BINARY
#=======================================

set(GLNGINE_LIBRARY_NAME GLSL)

set(GLNGINE_BINARY
    GLSL/default/default_FP.glsl
    GLSL/default/default_VP.glsl)

add_library(${GLNGINE_LIBRARY_NAME} INTERFACE ${GLNGINE_BINARY})
