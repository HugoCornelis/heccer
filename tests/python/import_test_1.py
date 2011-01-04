#! /usr/bin/env python
"""
This test checks for the for the Heccer modules 
to be present and importable.
"""
import os
import sys
import pdb

python_path = "/usr/local/glue/swig/python/"

sys.path.append(python_path)


print "Importing heccer_base"
import g3.heccer.heccer_base

print "Importing Heccer"
import g3.heccer

print "Done!"
