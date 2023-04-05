cmake_minimum_required(VERSION 3.21.1)

set(TARGET_NAME translations)

SET(SOURCE_DIR ${TILED_BASE_DIR}/translations)
# Translation files
SET(QON_TS_FILES
    tiled_ar_DZ.ts
    tiled_bg.ts
    tiled_cs.ts
    tiled_de.ts
    tiled_en.ts
    tiled_es.ts
    tiled_fi.ts
    tiled_fr.ts
    tiled_he.ts
    tiled_hu.ts
    tiled_it.ts
    tiled_ja.ts
    tiled_ko.ts
    tiled_nb.ts
    tiled_nl.ts
    tiled_pl.ts
    tiled_pt.ts
    tiled_pt_PT.ts
    tiled_ru.ts
    tiled_sv.ts
    tiled_th.ts
    tiled_tr.ts
    tiled_uk.ts
    tiled_zh_CN.ts
    tiled_zh_TW.ts
    translations.qbs
)

find_package(Qt6 REQUIRED COMPONENTS LinguistTools)
string(REGEX REPLACE "([^;]+)" "${SOURCE_DIR}/\\1" SOURCE_FILES "${QON_TS_FILES}")
qt6_add_translation(QON_QM_FILES TS_FILES
        ${SOURCE_FILES}
)
add_custom_target(${TARGET_NAME} DEPENDS ${QON_QM_FILES})
install(FILES ${QON_QM_FILES}
        DESTINATION "share/tiled/translations")