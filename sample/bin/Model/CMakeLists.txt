#=======================================
#                BINARY
#=======================================

set(GLNGINE_LIBRARY_NAME Model)

set(MODEL_BINARY
    Flamethrower/FlamerJetFuelTank_d.png
    Flamethrower/FlamerJetFuelTank_n.png
    Flamethrower/FlamerJetFuelTank_s.png
    Flamethrower/FlamerJetFuelTank_s2.png
    Flamethrower/FlamerJetFuelTank_s3.png
    Flamethrower/FlamerMagazineLarge_d.png
    Flamethrower/FlamerMagazineLarge_n.png
    Flamethrower/FlamerMagazineLarge_s.png
    Flamethrower/FlamerMagazineLarge_s2.png
    Flamethrower/FlamerMagazineLarge_s3.png
    Flamethrower/FlamerNapalmTank_d.png
    Flamethrower/FlamerNapalmTank_n.png
    Flamethrower/FlamerNapalmTank_s.png
    Flamethrower/FlamerNapalmTank_s2.png
    Flamethrower/FlamerNapalmTank_s3.png
    Flamethrower/Flamer_d.png
    Flamethrower/Flamer_n.png
    Flamethrower/Flamer_s.png
    Flamethrower/Flamer_s2.png
    Flamethrower/Flamer_s3.png
    Flamethrower/Flamethrower.mtl
    Flamethrower/Flamethrower.obj)

add_library(${GLNGINE_LIBRARY_NAME} INTERFACE ${GLNGINE_BINARY} ${MODEL_BINARY})
