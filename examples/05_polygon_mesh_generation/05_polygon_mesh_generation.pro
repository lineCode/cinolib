TEMPLATE        = app
TARGET          = 05_polygon_mesh_generation
QT             += core opengl xml
CONFIG         += c++11
CONFIG         -= app_bundle
INCLUDEPATH    += /usr/local/include
INCLUDEPATH    += /Users/cino/Documents/research/devel/lib/CinoLib/include
DEPENDPATH     += /Users/cino/Documents/research/devel/lib/CinoLib/include # force recompilation if cinolib changes

# ------------------------------------ #
# --------- WARNINGS CONTROL --------- #
# ------------------------------------ #

QMAKE_CXXFLAGS += -Wno-deprecated-declarations       # gluQuadric gluSphere and gluCylinde are deprecated in macOS 10.9

# ------------------------------------ #
# ------- EXTERNAL DEPENDENCIES ------ #
# ------------------------------------ #

# enable a OpenGL, QT and QGLViewer based GUI (used in cinolib/gui/qt/glcanvas.cpp)
DEFINES      += CINOLIB_USES_OPENGL
DEFINES      += CINOLIB_USES_QT_AND_QGLVIEWER
INCLUDEPATH  += /Library/Frameworks/QGLViewer.framework/Versions/2/Headers
QMAKE_LFLAGS *= -F/Library/Frameworks
LIBS         += -framework QGLViewer

# enable Triangle ()
DEFINES += CINOLIB_USES_TRIANGLE
LIBS    += -ltriangle

# ------------------------------------ #
# -------------- SOURCES ------------- #
# ------------------------------------ #

SOURCES += main.cpp