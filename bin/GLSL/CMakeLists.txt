#=======================================
#                BINARY
#=======================================

set(GLNGINE_LIBRARY_NAME GLSL)

set(GLNGINE_BINARY
    Common/Default_FP.glsl
    Common/Default_VP.glsl
    Lighting/BlinnPhong_FP.glsl
    Lighting/BlinnPhong_VP.glsl)

add_library(${GLNGINE_LIBRARY_NAME} INTERFACE ${GLNGINE_BINARY})
