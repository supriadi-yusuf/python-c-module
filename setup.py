#!/usr/local/bin/python3

from distutils.core import setup, Extension

module = Extension("myModule", # module name
    sources = ["myModule.c"])

setup(name="PackageName",
    version="1.0",
    description="This is a package for myModule",
    ext_modules=[module])
