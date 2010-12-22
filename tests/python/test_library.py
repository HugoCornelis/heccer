"""
A test library of functions and classes
for running heccer tests from python.

"""

import os
import sys
import pdb


def add_package_path(package):

    directory = "/neurospaces_project/" + package + "/source/snapshots/0"

    root_path = os.environ['HOME'] + directory

    path = root_path + "/glue/swig/python/"

    sys.path.append(path)

