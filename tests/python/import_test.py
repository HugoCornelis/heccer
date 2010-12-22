#! /usr/bin/env python
"""
This test checks for the for the Heccer modules 
to be present and importable.
"""
import os
import sys
import pdb

root_path = os.environ['HOME'] + "/neurospaces_project/heccer/source/snapshots/0"

nmc_path = root_path + "/glue/swig/python/"

sys.path.append(nmc_path)


print "Importing heccer_base"
import heccer.heccer_base

print "Importing Heccer"
import heccer.heccer

print "Done!"
