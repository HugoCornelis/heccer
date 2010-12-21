#!/usr/bin/python
import os
import sys

sys.path.append('/usr/local/glue/swig/python')


try:


    import SwiggableHeccer


except ImportError, e:
    sys.exit("%s" % e)




