#! /usr/bin/env python
"""

"""
import os
import sys
import pdb

from test_library import add_package_path

add_package_path("heccer")


from heccer.__cbi__ import PackageInfo

_package_info = PackageInfo()

version = _package_info.GetVersion()

print "%s" % version

print "Done!"
