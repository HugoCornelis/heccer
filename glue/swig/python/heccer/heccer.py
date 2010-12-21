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

import errors

try:

    import heccer_base

except ImportError, e:
    sys.exit("Could not import compiled SWIG heccer_base library: %s" % e)




#************************* Begin Heccer **************************
class Heccer:



#---------------------------------------------------------------------------

    def __init__(self, options=None):
        """!
        @brief 
        """

        self._options_core = None
        
        if 'model_source' in options:
            
            self._heccer_core = heccer_base.HeccerNew("heccer constructed from python", None, None, None)
            
            heccer_base.HeccerConstruct( self._heccer_core,
                                         options['model_source'],
                                         options['name'],
                                         None,
                                         None )
        else:
            
            print "model_source not found in the heccer options, cannot construct a heccer"

        if isinstance(options, heccer_base.HeccerOptions):

            self._options_core = options

        else:

            self._options_core = heccer_base.HeccerOptions()


#---------------------------------------------------------------------------

    def GetCore(self):
        """!
        @brief Returns the internal raw heccer struct
        """
        return self._heccer_core


#---------------------------------------------------------------------------

    def GetName(self):
        """!
        @brief 
        """
        if self._heccer_core is not None:
            
            return self._heccer_core.pcName

        else:

            from errors.import HeccerNotAllocatedError

            raise HeccerNotAllocatedError()


#---------------------------------------------------------------------------

    def GetErrorCount(self):
        """!
        @brief 
        """
        if self._heccer_core is not None:
            
            return self._heccer_core.iErrorCount

        else:

            from errors.import HeccerNotAllocatedError

            raise HeccerNotAllocatedError()


#---------------------------------------------------------------------------

    def GetStatus(self):
        """!
        @brief 
        """
        if self._heccer_core is not None:
            
            return self._heccer_core.iStatus

        else:

            from errors.import HeccerNotAllocatedError

            raise HeccerNotAllocatedError()
        

#---------------------------------------------------------------------------

    def GetAddress(self, serial, field):
        """!
        @brief Returns the Heccer Address variable
        """
        address = None
        
        if self._heccer_core is None:


            from errors.import HeccerNotAllocatedError

            raise HeccerNotAllocatedError()

        else:
            
            address = heccer_base.HeccerAddressVariable(self._heccer_core, serial, field)

        
        return address



    def SetIntervalStart(self, dstart):

        

#---------------------------------------------------------------------------

    def Step(self, time):
        """!
        @brief
        """

        return heccer_base.HeccerHeccs(self._heccer_core, time)


#---------------------------------------------------------------------------

    def Advance(self,time):
        """!
        @brief
        @sa Step
        """
        return self.Step(time)


#---------------------------------------------------------------------------

    def Compile(self):
        """!
        @brief This compiles the solver for the Heccer core
        """

        if self._heccer_core is not None:
            
            heccer_base.HeccerCompileP1(self._heccer_core)
            heccer_base.HeccerCompileP2(self._heccer_core)
            heccer_base.HeccerCompileP3(self._heccer_core)

        else:

            from errors.import HeccerNotAllocatedError

            raise HeccerNotAllocatedError()
        
#---------------------------------------------------------------------------

    def Finish(self):
        """!
        @brief Completes the process and closes the solver
        """
        pass

#---------------------------------------------------------------------------

    def SetTimeStep(self, dt):
        """!
        @brief 
        """
        if self._heccer_core is not None:
        
            self._heccer_core.dStep = dt

        else:

            from errors.import HeccerNotAllocatedError
        
            raise HeccerNotAllocatedError()
    
#---------------------------------------------------------------------------

    def GetTimeStep(self):

        if self._heccer_core is not None:
        
            return self._heccer_core.dStep 

        else:

            from errors.import HeccerNotAllocatedError

            raise HeccerNotAllocatedError()


        
#************************* End Heccer **************************
