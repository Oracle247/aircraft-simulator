QT -= gui
QT += opengl

LIBS += -lglut -lGLEW -lGLU -lglfw
CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        camera.cpp \
        indexbuffer.cpp \
        main.cpp \
        mesh.cpp \
        renderer.cpp \
        shader.cpp \
        simulator.cpp \
        texture.cpp \
        vendor/imgui/imgui.cpp \
        vendor/imgui/imgui_demo.cpp \
        vendor/imgui/imgui_draw.cpp \
        vendor/imgui/imgui_impl_glfw_gl3.cpp \
        vendor/stb_image/stb_image.cpp \
        vertexarray.cpp \
        vertexbuffer.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    basic.shader \
    model.shader \
    objmodel.shader \
    ortho_2D.shader \
    res/model/aircraft1.mtl \
    res/model/aircraft1.obj \
    res/model/aircraft2.mtl \
    res/model/aircraft2.obj \
    res/model/airplane.mtl \
    res/model/airplane.obj \
    res/model/ao.jpg \
    res/model/backpack.mtl \
    res/model/backpack.obj \
    res/model/box.obj \
    res/model/cone.obj \
    res/model/cross.obj \
    res/model/cube-3d-shape.mtl \
    res/model/cube-3d-shape.obj \
    res/model/cube.obj \
    res/model/diffuse.jpg \
    res/model/donut.mtl \
    res/model/donut.obj \
    res/model/donut1.mtl \
    res/model/donut1.obj \
    res/model/jetanima.obj \
    res/model/normal.png \
    res/model/quad.mtl \
    res/model/quad.obj \
    res/model/roughness.jpg \
    res/model/source_attribution.txt \
    res/model/specular.jpg \
    res/model/suzanne.obj \
    res/model/torus.obj \
    res/textures/pics/Programming1.jpg \
    res/textures/pics/Screenshot from 2020-11-04 12-39-51.png \
    res/textures/pics/back.jpg \
    res/textures/pics/badge.png \
    res/textures/pics/bottom.jpg \
    res/textures/pics/box.png \
    res/textures/pics/christmas_tree.png \
    res/textures/pics/container.jpg \
    res/textures/pics/dark.png \
    res/textures/pics/front.jpg \
    res/textures/pics/grass.jpg \
    res/textures/pics/grass1.jpg \
    res/textures/pics/jajlands1_bk.jpg \
    res/textures/pics/jajlands1_dn.jpg \
    res/textures/pics/jajlands1_ft.jpg \
    res/textures/pics/jajlands1_lf.jpg \
    res/textures/pics/jajlands1_rt.jpg \
    res/textures/pics/jajlands1_up.jpg \
    res/textures/pics/left.jpg \
    res/textures/pics/path.png \
    res/textures/pics/pavement.jpg \
    res/textures/pics/right.jpg \
    res/textures/pics/roof.jpeg \
    res/textures/pics/snow.png \
    res/textures/pics/snowflake.png \
    res/textures/pics/top.jpg \
    res/textures/pics/wall.jpeg \
    res/textures/pics/wall1.jpeg \
    terrain1.shader \
    terrain2.shader

HEADERS += \
    camera.h \
    indexbuffer.h \
    libs.h \
    material.h \
    mesh.h \
    objloader.h \
    primitive.h \
    renderer.h \
    shader.h \
    simulator.h \
    texture.h \
    vendor/assimp-3.1.1/include/assimp/Importer.hpp \
    vendor/assimp-3.1.1/include/assimp/postprocess.h \
    vendor/assimp-3.1.1/include/assimp/scene.h \
    vendor/imgui/imconfig.h \
    vendor/imgui/imgui.h \
    vendor/imgui/imgui_impl_glfw_gl3.h \
    vendor/imgui/imgui_internal.h \
    vendor/imgui/stb_rect_pack.h \
    vendor/imgui/stb_textedit.h \
    vendor/imgui/stb_truetype.h \
    vendor/stb_image/stb_image.h \
    vertex.h \
    vertexarray.h \
    vertexbuffer.h \
    vertexbufferlayout.h
