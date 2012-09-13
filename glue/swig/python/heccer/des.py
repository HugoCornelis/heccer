

import os
import pdb
import sys

try:

    import heccer_base

except ImportError, e:
    
    sys.exit("Could not import compiled SWIG heccer_base library: %s" % e)



#************************* Start DES *******************************************

class DES:


#---------------------------------------------------------------------------

    def __init__(self, name="Untitled DES", model=None, model_source=None, options=None):

        self.name = name

        self._des = heccer_base.DESNew(1)

        if self._des is None:

            raise Exception("Allocation Error, Can't create DES object")

        
        if not options is None:

            pass


        self.time_step = None

        self.projections = []

        self.model_name = None

        self.model_source = None
        
#---------------------------------------------------------------------------

    def GetDistributor(self):

        pass

#---------------------------------------------------------------------------

    def Compile(self):

        pass

#---------------------------------------------------------------------------

    def Connect(self):

        pass

#---------------------------------------------------------------------------

    def Dump(self):

        pass

    def Finish(self):

        pass
    
#---------------------------------------------------------------------------

    def Report(self):

        pass


        
#************************* End DES *********************************************
