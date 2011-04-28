#! /usr/bin/env python
"""
This test checks for the for the heccer modules 
to be present and importable.
"""
import os
import sys
import pdb

from test_library import add_package_path

add_package_path("heccer")

print "Importing heccer_base"
import neurospaces.heccer.heccer_base

print "Importing heccer"
import neurospaces.heccer

print "Done!"
