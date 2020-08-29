

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_net REQUIRED)

find_package(FFmpeg REQUIRED)

set(pig_SRCS
    canimacao.cpp
    cassetloader.cpp
    caudio.cpp
    cclientetcp.cpp
    ccontrole.cpp
    cfilapacotes.cpp
    cgeradorparticulas.cpp
    cgeradorpoligonos.cpp
    cgerenciadoranimacoes.cpp
    cgerenciadoraudios.cpp
    cgerenciadorcontroles.cpp
    cgerenciadorfontes.cpp
    cgerenciadorjanelas.cpp
    cgerenciadorobjetos.cpp
    cgerenciadorparticulas.cpp
    cgerenciadorsockets.cpp
    cgerenciadortimers.cpp
    cgerenciadorvideos.cpp
    cjanela.cpp
    cjogo.cpp
    cmapacaracteres.cpp
    cmapacaracteresdinamicos.cpp
    cmodoanimacao.cpp
    cmouse.cpp
    cobjeto.cpp
    cparticula.cpp
    cpigareadetexto.cpp
    cpigbotao.cpp
    cpigbox.cpp
    cpigcaixatexto.cpp
    cpigcampotextoesenha.cpp
    cpigcheckbox.cpp
    cpigcomponente.cpp
    cpigcursor.cpp
    cpigdropdown.cpp
    cpigerro.cpp
    cpigerroarquivo.cpp
    cpigerroparametro.cpp
    cpigerroindice.cpp
    cpigform.cpp
    cpiggauge.cpp
    cpiggaugecircular.cpp
    cpigitemcheck.cpp
    cpigitemlista.cpp
    cpiglista.cpp
    cpigradiobox.cpp
    cpigscrollbar.cpp
    cpigstringformatada.cpp
    cpilhacoordenada.cpp
    cpoolnumeros.cpp
    cservidortcp.cpp
    csockettcp.cpp
    csocketudp.cpp
    ctimer.cpp
    cvideo.cpp
    cvisual.cpp
    pig.cpp
    pigfuncoesbasicas.cpp
    coffscreenrenderer.cpp
)

set(SDL_LIBS
    SDL2::Main
    SDL2::Image
    SDL2::Mixer
    SDL2::TTF
    SDL2::Net
)

set(AV_LIBS
    ${FFMPEG_LIBAVCODEC_LIBRARIES}
    ${FFMPEG_LIBAVFORMAT_LIBRARIES}
    ${FFMPEG_LIBAVDEVICE_LIBRARIES}
    ${FFMPEG_LIBAVUTIL_LIBRARIES}
    ${FFMPEG_LIBWSRESAMPLE_LIBRARIES}
    ${FFMPEG_LIBSWSCALE_LIBRARIES}
)

add_library(Pig ${pig_SRCS})

target_include_directories(Pig PUBLIC ${AVCODEC_INCLUDE_DIR} ${AVFORMAT_INCLUDE_DIR})
target_link_libraries(Pig PUBLIC ${SDL_LIBS} ${AV_LIBS})
