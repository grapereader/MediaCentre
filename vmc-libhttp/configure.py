#!/usr/bin/env python
import glob, os

dirpath = os.path.abspath(os.path.join(os.path.abspath(__file__), os.pardir))
dirname = os.path.relpath(dirpath, os.path.pardir);

objects = ""
sourceFiles = []
includeModules = []

for f in glob.glob("*.cpp"):
    objects += f.replace(".cpp", ".o") + " "
    sourceFiles.append(f)

cflags = "-Wall -std=c++1y -I../vendor/json/include -I/usr/include/mysql -I/usr/include/mysql++"
exe = dirname + ".a"

for i in includeModules:
    cflags += " -I../" + i;

with open("Makefile", "w") as f:
    f.write("CFLAGS=" + cflags + "\n")
    f.write("\n")
    f.write("OBJECTS=" + objects + "\n")
    f.write("\n")
    f.write("all: " + exe + "\n")
    f.write("\n")
    f.write(exe + ": $(OBJECTS)\n")
    f.write("\tar rcs " + exe + " $(OBJECTS)\n")
    for source in sourceFiles:
        obj = source.replace(".cpp", ".o")
        f.write("\n")
        f.write(obj + ": " + source + "\n")
        f.write("\t$(CXX) -c " + source + " -o " + obj + " $(CFLAGS)\n")
    f.write("\n")
    f.write("clean:\n")
    f.write("\trm *.o " + exe + "\n")
