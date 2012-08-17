__STANDARD__=YES

SRCROOT=../..

RM=rm -f

RM_DIR=rm -rf

MAKE_DEP=

MAKE_DEP_FLAGS=$(INCLUDES) $(DEFINES)

MAKE_LIB=python $(BUILD_ROOT)/bin/pyar.py cr

MAKE_LIB_FLAGS=

RANLIB=ranlib

CP=cp

MAKE=make

CC=gcc

CCFLAGS=-pipe -Wall -Wreturn-type -fno-exceptions -march=pentium -mcpu=pentium -O0 -g -DDEBUG -D_DEBUG  $(INCLUDES) $(DEFINES)

CXX=g++

CXXFLAGS=-pipe -Wall -Wreturn-type -Wno-non-virtual-dtor -fno-exceptions --permissive -Wno-ctor-dtor-privacy -fno-rtti -march=pentium -mcpu=pentium -O0 -g -DDEBUG -D_DEBUG  $(INCLUDES) $(DEFINES)

SRCS=main.cpp excontxt.cpp exadvsnk.cpp exerror.cpp iids.cpp print.cpp preflist.cpp exaumgr.cpp exsitsup.cpp fivemmap.cpp exprdnld.cpp

OBJS=$(COMPILED_OBJS) $(SOURCE_OBJS)

COMPILED_OBJS=dbg/obj/main.o dbg/obj/excontxt.o dbg/obj/exadvsnk.o dbg/obj/exerror.o dbg/obj/iids.o dbg/obj/print.o dbg/obj/preflist.o dbg/obj/exaumgr.o dbg/obj/exsitsup.o dbg/obj/fivemmap.o dbg/obj/exprdnld.o

SOURCE_OBJS=

COMPILED_RESOURCES=

OUTPUT_DIR=dbg

INCLUDES=-I../../common/runtime/pub -I/usr/X11R6/include -I../../common/include -I../../client/include -I../../client/common/system/pub -I../../common/container/pub -I../../datatype/rm/include -I../../video/include -I../../datatype/image/png/common/pub -I./pub -I../../common/system/pub -I../../common/dbgtool/pub -I../../common/util/pub -I../../common/import/zlib/pub

DEFINES=-I. -include dbg/clientapps_simpleplayer_ribodefs.h

STATIC_LIBS=../../common/runtime/dbg/runtlib.a ../../common/system/dbg/syslib.a ../../common/container/dbg/contlib.a ../../client/common/system/dbg/sysclntlib.a ../../common/dbgtool/dbg/debuglib.a ../../common/util/dbg/utillib.a  ../../common/fileio/dbg/fileiolib.a ../../common/log/logutil/dbg/logutillib.a ../../client/medpltfm/dbg/hxmedpltfmlib.a ../../common/netio/dbg/netiolib.a ../../protocol/http/dbg/httplib.a ../../protocol/common/util/dbg/protutillib.a  ../../client/common/container/dbg/contclntlib.a ../../client/common/util/dbg/utlclntlib.a ../../client/common/netio/dbg/netioclntlib.a ../../client/netwksvc/dbg/netsvclib.a ../../common/lang/xml/dbg/xmllib.a 

DYNAMIC_LIBS=-ldl -lm -lpthread -lX11

.SUFFIXES: .cpp .so

.c.o: 
	$(CC) $(CCFLAGS) -o  $@ -c $<

.cpp.o: 
	$(CXX) $(CXXFLAGS) -o  $@ -c $<

all: dbg/obj dbg/splay

dbg/obj: 
	-@test -d dbg || mkdir dbg
	-@test -d dbg/obj || mkdir dbg/obj

all_objects: $(OBJS)

dbg/splay: $(OBJS) $(STATIC_LIBS)
	-@test -d dbg || mkdir dbg
	python $(BUILD_ROOT)/bin/armerge.py -a ar -d dbg/obj/lib dbg/splay_libs.a $(STATIC_LIBS)
	g++ -o dbg/splay $(OBJS) dbg/splay_libs.a -L/usr/X11R6/lib  $(DYNAMIC_LIBS)
#rm "dbg/splay_libs.a"

dbg/obj/main.o: main.cpp
	-@test -d dbg || mkdir dbg
	-@test -d dbg/obj || mkdir dbg/obj
	$(CXX) $(CXXFLAGS) -o dbg/obj/main.o -c main.cpp

dbg/obj/excontxt.o: excontxt.cpp
	-@test -d dbg || mkdir dbg
	-@test -d dbg/obj || mkdir dbg/obj
	$(CXX) $(CXXFLAGS) -o dbg/obj/excontxt.o -c excontxt.cpp

dbg/obj/exadvsnk.o: exadvsnk.cpp
	-@test -d dbg || mkdir dbg
	-@test -d dbg/obj || mkdir dbg/obj
	$(CXX) $(CXXFLAGS) -o dbg/obj/exadvsnk.o -c exadvsnk.cpp

dbg/obj/exerror.o: exerror.cpp
	-@test -d dbg || mkdir dbg
	-@test -d dbg/obj || mkdir dbg/obj
	$(CXX) $(CXXFLAGS) -o dbg/obj/exerror.o -c exerror.cpp

dbg/obj/iids.o: iids.cpp
	-@test -d dbg || mkdir dbg
	-@test -d dbg/obj || mkdir dbg/obj
	$(CXX) $(CXXFLAGS) -o dbg/obj/iids.o -c iids.cpp

dbg/obj/print.o: print.cpp
	-@test -d dbg || mkdir dbg
	-@test -d dbg/obj || mkdir dbg/obj
	$(CXX) $(CXXFLAGS) -o dbg/obj/print.o -c print.cpp

dbg/obj/preflist.o: preflist.cpp
	-@test -d dbg || mkdir dbg
	-@test -d dbg/obj || mkdir dbg/obj
	$(CXX) $(CXXFLAGS) -o dbg/obj/preflist.o -c preflist.cpp

dbg/obj/exaumgr.o: exaumgr.cpp
	-@test -d dbg || mkdir dbg
	-@test -d dbg/obj || mkdir dbg/obj
	$(CXX) $(CXXFLAGS) -o dbg/obj/exaumgr.o -c exaumgr.cpp

dbg/obj/exsitsup.o: exsitsup.cpp
	-@test -d dbg || mkdir dbg
	-@test -d dbg/obj || mkdir dbg/obj
	$(CXX) $(CXXFLAGS) -o dbg/obj/exsitsup.o -c exsitsup.cpp

dbg/obj/fivemmap.o: fivemmap.cpp
	-@test -d dbg || mkdir dbg
	-@test -d dbg/obj || mkdir dbg/obj
	$(CXX) $(CXXFLAGS) -o dbg/obj/fivemmap.o -c fivemmap.cpp

dbg/obj/exprdnld.o: exprdnld.cpp
	-@test -d dbg || mkdir dbg
	-@test -d dbg/obj || mkdir dbg/obj
	$(CXX) $(CXXFLAGS) -o dbg/obj/exprdnld.o -c exprdnld.cpp

clean: 
	$(RM) dbg/splay dbg/obj/lib dbg/splay_libs.a dbg/obj/main.o dbg/obj/excontxt.o dbg/obj/exadvsnk.o dbg/obj/exerror.o dbg/obj/iids.o dbg/obj/print.o dbg/obj/preflist.o dbg/obj/exaumgr.o dbg/obj/exsitsup.o dbg/obj/fivemmap.o dbg/obj/exprdnld.o

realclean: clean
	$(RM) Umakefil.upp
	-$(RM_DIR) dbg ribosome_logs

../../debug/splay: dbg/splay
	-@test -d ../../debug || mkdir ../../debug
	rm -f "../../debug/splay"
	cp "dbg/splay" "../../debug/splay"

copy: ../../debug/splay

depend: 
	$(BUILD_ROOT)/bin/mkdepend.py --gnumake -tdbg/obj -mMakefile $(INCLUDES) $(SRCS)

# DO NOT DELETE -- mkdepend depends on this line
# Dependency magic by $Id: mkdepend_exe.py,v 1.6 2010/01/04 18:46:56 robertn Exp $
ifneq ($(MAKECMDGOALS),clean)
-include $(COMPILED_OBJS:.o=.dep)
endif

dbg/obj/%.dep: %.cc
	@test -d dbg || mkdir dbg
	@test -d dbg/obj || mkdir dbg/obj
	/usr/bin/python /home/collins/simplecore/build//bin/mkdepend.py --gnumake -tdbg/obj $?

dbg/obj/%.dep: %.c
	@test -d dbg || mkdir dbg
	@test -d dbg/obj || mkdir dbg/obj
	/usr/bin/python /home/collins/simplecore/build//bin/mkdepend.py --gnumake -tdbg/obj $?

dbg/obj/%.dep: %.cxx
	@test -d dbg || mkdir dbg
	@test -d dbg/obj || mkdir dbg/obj
	/usr/bin/python /home/collins/simplecore/build//bin/mkdepend.py --gnumake -tdbg/obj $?

dbg/obj/%.dep: %.cpp
	@test -d dbg || mkdir dbg
	@test -d dbg/obj || mkdir dbg/obj
	/usr/bin/python /home/collins/simplecore/build//bin/mkdepend.py --gnumake -tdbg/obj $?


