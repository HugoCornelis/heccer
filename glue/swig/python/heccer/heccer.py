"""!
@package heccer


"""

__author__ = 'Mando Rodriguez'
__credits__ = []
__license__ = "GPL"
__version__ = "0.1"
__status__ = "Development"


import os
import sys

try:

    import heccer_base

except ImportError:
    sys.exit("Could not import compiled SWIG heccer_base library")



class Heccer:
    
    def __init__(self, options):
        """!
        @brief 
        """

        self._options_core = None
        
        if 'model_source' in options:
            
            self._core = heccer_base.HeccerNew("heccer constructed from python", None, None, None)
            
            heccer_base.HeccerConstruct( self._core,
                                         options['model_source'],
                                         options['name'],
                                         None,
                                         None )
        else:
            
            print "model_source not found in the heccer options, cannot construct a heccer"


    def GetCore(self):
        """!
        @brief Returns the internal raw heccer struct
        """
        return self._core


    def GetName(self):
        """!
        @brief 
        """
        if self._core is not None:
            
            return self._core.pcName

        else:

            return None


    def GetErrorCount(self):
        """!
        @brief 
        """
        if self._core is not None:
            
            return self._core.iErrorCount

        else:

            return None

    def GetStatus(self):
        """!
        @brief 
        """
        if self._core is not None:
            
            return self._core.iStatus

        else:

            return None
        

    def GetAddress(self, serial, field):
        """!
        @brief Returns the Heccer Address variable
        """
        return heccer_base.HeccerAddressVariable(self._core, serial, field)
        
    def Step(self, time):
        """!
        @brief
        """
        return heccer_base.HeccerHeccs(self._core, time)

    def Advance(self,time):
        """!
        @brief
        @sa Step
        """
        return self.Step(time)
        

    def Compile(self):
        """!
        @brief 
        """
        heccer_base.HeccerCompileP1(self._core)
        heccer_base.HeccerCompileP2(self._core)
        heccer_base.HeccerCompileP3(self._core)

    def Finish(self):
        """!
        @brief Completes the process and closes the solver
        """
        pass

    def TimeStep(self, dt):
        """!
        @brief 
        """
        self._core.dStep = dt
        

