"""
A test library of functions and classes
for running heccer tests from python.

"""

import os
import sys
import pdb


# compartment = {dCm: 4.57537e-11,
#                dEm: -0.08,
#                dInitVm: -0.068,
#                dInject: 1e-8,
#                dRa: 360502,
#                dRm: 3.58441e+08,
#                iParent: -1
#                }



def add_package_path(package):
    """
    Adds an import path to a python module in a project directory.
    """
    directory = "/neurospaces_project/" + package + "/source/snapshots/0"

    root_path = os.environ['HOME'] + directory

    path = root_path + "/glue/swig/python/"

    sys.path.append(path)

