#=======================================
#                BINARY
#=======================================

set(GLNGINE_LIBRARY_NAME Sample_Texture)

set(TEXTURE_BINARY
    BrickWall.png)

add_library(${GLNGINE_LIBRARY_NAME} INTERFACE ${GLNGINE_BINARY} ${TEXTURE_BINARY})
