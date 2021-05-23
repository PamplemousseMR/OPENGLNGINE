#=======================================
#                BINARY
#=======================================

set(GLNGINE_LIBRARY_NAME GLSL)

set(GLNGINE_BINARY
    GLSL/Default/Default_FP.glsl
    GLSL/Default/Default_VP.glsl
    GLSL/BlinnPhong/BlinnPhong_FP.glsl
    GLSL/BlinnPhong/BlinnPhong_VP.glsl)

add_library(${GLNGINE_LIBRARY_NAME} INTERFACE ${GLNGINE_BINARY})
