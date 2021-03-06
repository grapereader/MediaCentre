#!/usr/bin/env python
import glob, os
from subprocess import Popen
vmcLibs = ["vmc-libctrl", "vmc-libstream", "vmc-libhttp", "vmc-libselect", "vmc-libutils"]
vmcLibsFiles = ""

for lib in vmcLibs:
    Popen(["python", "configure.py"], cwd="./" + lib)
    vmcLibsFiles = vmcLibsFiles + lib + "/" + lib + ".a "

objects = "";
sourceFiles = [];

for f in glob.glob("*.cpp"):
    objects += f.replace(".cpp", ".o") + " ";
    sourceFiles.append(f);

cflags = "-Wall -std=c++1y -I./vendor/json/include -I/usr/include/mysql -I/usr/include/mysql++ -I./ `pkg-config giomm-2.4 --cflags`"
ldflags = "-lboost_system -lboost_filesystem -lpthread -lmysqlpp -lmysqlclient -lcryptopp `pkg-config giomm-2.4 --libs`"
exe = "media-server"

with open("Makefile", "w") as f:
    f.write("CFLAGS=" + cflags + "\n")
    f.write("LDFLAGS=" + ldflags + "\n")
    f.write("\n")
    f.write("OBJECTS=" + objects + "\n")
    f.write("\n")
    f.write("all:")
    for lib in vmcLibs:
        f.write(" " + lib + "/" + lib + ".a")
    f.write(" " + exe + "\n")
    for lib in vmcLibs:
        f.write(lib + "/" + lib + ".a:\n")
        f.write("\t+$(MAKE) -C " + lib + "\n")
    f.write("\n")
    f.write(exe + ": $(OBJECTS)\n");
    f.write("\t$(CXX) -o " + exe + " $(OBJECTS) " + vmcLibsFiles  + " $(LDFLAGS)\n")
    for source in sourceFiles:
        obj = source.replace(".cpp", ".o")
        f.write("\n")
        f.write(obj + ": " + source + "\n")
        f.write("\t$(CXX) -c " + source + " -o " + obj + " $(CFLAGS)\n")
    f.write("\n")
    f.write("clean:\n")
    for lib in vmcLibs:
        f.write("\t+$(MAKE) -C " + lib + " clean\n")
    f.write("\trm *.o " + exe + "\n")
