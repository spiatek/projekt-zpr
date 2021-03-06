#############################################################################
# Makefile for building: projekt-zpr
# Generated by qmake (2.01a) (Qt 4.7.4) on: Wed May 30 19:56:45 2012
# Project:  projekt-zpr.pro
# Template: app
# Command: /usr/bin/qmake -o Makefile projekt-zpr.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_WEBKIT -DQWT_DLL -DQT_NO_DEBUG -DQT_SVG_LIB -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -m64 -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -m64 -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++-64 -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4/QtSvg -I/usr/include/qt4 -I. -Iheaders -I/usr/include/qwt -I.
LINK          = g++
LFLAGS        = -m64 -Wl,-O1
LIBS          = $(SUBLIBS)  -L/usr/lib/x86_64-linux-gnu -L/usr/lib -lqwt -lQtSvg -lQtGui -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = sources/Curve.cpp \
		sources/main.cpp \
		sources/Panel.cpp \
		sources/Plot.cpp \
		sources/fileProxy.cpp \
		sources/PlotWindow.cpp moc_Panel.cpp \
		moc_Plot.cpp \
		moc_PlotWindow.cpp \
		qrc_application.cpp
OBJECTS       = Curve.o \
		main.o \
		Panel.o \
		Plot.o \
		fileProxy.o \
		PlotWindow.o \
		moc_Panel.o \
		moc_Plot.o \
		moc_PlotWindow.o \
		qrc_application.o
DIST          = /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/qwtconfig.pri \
		/usr/share/qt4/mkspecs/features/qwt.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		projekt-zpr.pro
QMAKE_TARGET  = projekt-zpr
DESTDIR       = 
TARGET        = projekt-zpr

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: projekt-zpr.pro  /usr/share/qt4/mkspecs/linux-g++-64/qmake.conf /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/qwtconfig.pri \
		/usr/share/qt4/mkspecs/features/qwt.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/x86_64-linux-gnu/libQtSvg.prl \
		/usr/lib/x86_64-linux-gnu/libQtGui.prl \
		/usr/lib/x86_64-linux-gnu/libQtCore.prl
	$(QMAKE) -o Makefile projekt-zpr.pro
/usr/share/qt4/mkspecs/common/g++.conf:
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/release.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/qwtconfig.pri:
/usr/share/qt4/mkspecs/features/qwt.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/x86_64-linux-gnu/libQtSvg.prl:
/usr/lib/x86_64-linux-gnu/libQtGui.prl:
/usr/lib/x86_64-linux-gnu/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -o Makefile projekt-zpr.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/projekt-zpr1.0.0 || $(MKDIR) .tmp/projekt-zpr1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/projekt-zpr1.0.0/ && $(COPY_FILE) --parents headers/Curve.h headers/FunctionData.h headers/Panel.h headers/Plot.h headers/fileProxy.h headers/PlotWindow.h .tmp/projekt-zpr1.0.0/ && $(COPY_FILE) --parents application.qrc .tmp/projekt-zpr1.0.0/ && $(COPY_FILE) --parents sources/Curve.cpp sources/main.cpp sources/Panel.cpp sources/Plot.cpp sources/fileProxy.cpp sources/PlotWindow.cpp .tmp/projekt-zpr1.0.0/ && (cd `dirname .tmp/projekt-zpr1.0.0` && $(TAR) projekt-zpr1.0.0.tar projekt-zpr1.0.0 && $(COMPRESS) projekt-zpr1.0.0.tar) && $(MOVE) `dirname .tmp/projekt-zpr1.0.0`/projekt-zpr1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/projekt-zpr1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_Panel.cpp moc_Plot.cpp moc_PlotWindow.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_Panel.cpp moc_Plot.cpp moc_PlotWindow.cpp
moc_Panel.cpp: headers/Panel.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) headers/Panel.h -o moc_Panel.cpp

moc_Plot.cpp: headers/Curve.h \
		headers/Plot.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) headers/Plot.h -o moc_Plot.cpp

moc_PlotWindow.cpp: headers/Plot.h \
		headers/Curve.h \
		headers/fileProxy.h \
		headers/FunctionData.h \
		headers/PlotWindow.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) headers/PlotWindow.h -o moc_PlotWindow.cpp

compiler_rcc_make_all: qrc_application.cpp
compiler_rcc_clean:
	-$(DEL_FILE) qrc_application.cpp
qrc_application.cpp: application.qrc \
		images/new.png \
		images/copy.png \
		images/cut.png \
		images/save.png \
		images/paste.png \
		images/open.png
	/usr/bin/rcc -name application application.qrc -o qrc_application.cpp

compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_rcc_clean 

####### Compile

Curve.o: sources/Curve.cpp headers/Curve.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Curve.o sources/Curve.cpp

main.o: sources/main.cpp headers/PlotWindow.h \
		headers/Plot.h \
		headers/Curve.h \
		headers/fileProxy.h \
		headers/FunctionData.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o sources/main.cpp

Panel.o: sources/Panel.cpp headers/Panel.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Panel.o sources/Panel.cpp

Plot.o: sources/Plot.cpp headers/Plot.h \
		headers/Curve.h \
		headers/FunctionData.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Plot.o sources/Plot.cpp

fileProxy.o: sources/fileProxy.cpp headers/fileProxy.h \
		headers/FunctionData.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o fileProxy.o sources/fileProxy.cpp

PlotWindow.o: sources/PlotWindow.cpp headers/PlotWindow.h \
		headers/Plot.h \
		headers/Curve.h \
		headers/fileProxy.h \
		headers/FunctionData.h \
		headers/Panel.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o PlotWindow.o sources/PlotWindow.cpp

moc_Panel.o: moc_Panel.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_Panel.o moc_Panel.cpp

moc_Plot.o: moc_Plot.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_Plot.o moc_Plot.cpp

moc_PlotWindow.o: moc_PlotWindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_PlotWindow.o moc_PlotWindow.cpp

qrc_application.o: qrc_application.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qrc_application.o qrc_application.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

