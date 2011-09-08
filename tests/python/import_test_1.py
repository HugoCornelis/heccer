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
import heccer.heccer_base

print "Importing Heccer"
import heccer

print "Done!"
