#!/usr/bin/env python
import glob, os

objects = "";
sourceFiles = [];

for f in glob.glob("*.cpp"):
    objects += f.replace(".cpp", ".o") + " ";
    sourceFiles.append(f);

cflags = "-Wall -std=c++1y"
ldflags = "-lboost_system -lpthread"
exe = "stream-server"

with open("Makefile", "w") as f:
    f.write("CFLAGS=" + cflags + "\n")
    f.write("LDFLAGS=" + ldflags + "\n")
    f.write("\n")
    f.write("OBJECTS=" + objects + "\n")
    f.write("\n")
    f.write("all: " + exe + "\n")
    f.write("\n")
    f.write(exe + ": $(OBJECTS)\n");
    f.write("\t$(CXX) -o " + exe + " $(OBJECTS) $(LDFLAGS)\n")
    for source in sourceFiles:
        obj = source.replace(".cpp", ".o")
        f.write("\n")
        f.write(obj + ": " + source + "\n")
        f.write("\t$(CXX) -c " + source + " -o " + obj + " $(CFLAGS)\n")
    f.write("\n")
    f.write("clean:\n")
    f.write("\trm *.o " + exe + "\n")
