#=======================================
#                BINARY
#=======================================

set(GLNGINE_LIBRARY_NAME Sample_GLSL)

set(GLNGINE_BINARY
    Common/Default_FP.glsl
    Common/Default_VP.glsl
    Lighting/BlinnPhong_FP.glsl
    Lighting/BlinnPhong_VP.glsl
    Texture/SamplerMap_FP.glsl
    Texture/SamplerMap_VP.glsl)

add_library(${GLNGINE_LIBRARY_NAME} INTERFACE ${GLNGINE_BINARY})
