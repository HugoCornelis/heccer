"""
A test library of functions and classes
for running heccer tests from python.

"""

import os
import sys
import pdb


INITIATE=1
INTERVAL_START=-0.1
INTERVAL_END=0.05
INTERVAL_ENTRIES=3000
INTERPOL_INTERVAL_ENTRIES=149
OPTIONS=0
OUTPUT=0
REPORTING_GRANULARITY=1
SCHEDULE=1
STEPS=10
TIME_GRANULARITY=1e-9
TIME_STEP=2e-5

def add_package_path(package):
    """
    Adds an import path to a python module in a project directory.
    """
    directory = "/neurospaces_project/" + package + "/source/snapshots/0"

    root_path = os.environ['HOME'] + directory

    path = root_path + "/glue/swig/python/"

    sys.path.append(path)


    

    
