#=======================================
#                BINARY
#=======================================

set(GLNGINE_LIBRARY_NAME GLSL)

set(GLNGINE_BINARY
    Default/Default_FP.glsl
    Default/Default_VP.glsl
    BlinnPhong/BlinnPhong_FP.glsl
    BlinnPhong/BlinnPhong_VP.glsl
    Geometry/Geometry_FP.glsl
    Geometry/Geometry_GP.glsl
    Geometry/Geometry_VP.glsl)

add_library(${GLNGINE_LIBRARY_NAME} INTERFACE ${GLNGINE_BINARY})
