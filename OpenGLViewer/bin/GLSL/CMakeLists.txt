#=======================================
#                BINARY
#=======================================

set(GLNGINE_LIBRARY_NAME GLSL)

set(GLNGINE_BINARY
	OpenGLViewer_FP.glsl
	OpenGLViewer_VP.glsl)

add_library(${GLNGINE_LIBRARY_NAME} INTERFACE ${GLNGINE_BINARY})
