#! /usr/bin/env python
"""

"""
import os
import sys
import pdb

from test_library import add_package_path

add_package_path("heccer")


from heccer import GetVersion

version = GetVersion()

print "%s" % version

print "Done!"
