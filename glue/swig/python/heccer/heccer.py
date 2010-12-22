"""!
@package heccer

The heccer python module provides an abstraction over the
heccer data structures and their accompanying functions.
"""

__author__ = 'Mando Rodriguez'
__credits__ = []
__license__ = "GPL"
__version__ = "0.1"
__status__ = "Development"

# System imports
import os
import sys

# User imports
import errors

try:

    import heccer_base

except ImportError, e:
    sys.exit("Could not import compiled SWIG heccer_base library: %s" % e)




#************************* Begin Heccer **************************
class Heccer:

    """!
    @class Heccer

    The Heccer class manages a heccer solver object and its options.

    """

#---------------------------------------------------------------------------

    def __init__(self, name, options=None):
        """!
        @brief Constructor
        @param name The identifier for this Heccer
        @param options A HeccerOptions struct
        """

        self._options_core = None
        
        if 'model_source' in options:
            
            self._heccer_core = heccer_base.HeccerNew(name, None, None, None)

            #! should move this somewhere else.
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

    def GetOptions(self):
        """!

        """
        return self._options_core


#---------------------------------------------------------------------------

    def SetOptions(self, ho):
        """!
        @brief 
        """

        if isinstance(ho, heccer_base.HeccerOptions):

            self._options_core = ho

        

#---------------------------------------------------------------------------

    def GetName(self):
        """!
        @brief 
        """
        if self.GetCore() is not None:
            
            return self.GetCore().pcName

        else:

            from errors import HeccerNotAllocatedError

            raise HeccerNotAllocatedError()


#---------------------------------------------------------------------------

    def GetErrorCount(self):
        """!
        @brief 
        """
        if self.GetCore() is not None:
            
            return self.GetCore().iErrorCount

        else:

            from errors import HeccerNotAllocatedError

            raise HeccerNotAllocatedError()


#---------------------------------------------------------------------------

    def GetStatus(self):
        """!
        @brief 
        """
        if self.GetCore() is not None:
            
            return self.GetCore().iStatus

        else:

            from errors import HeccerNotAllocatedError

            raise HeccerNotAllocatedError()
        

#---------------------------------------------------------------------------

    def GetAddress(self, serial, field):
        """!
        @brief Returns the Heccer Address variable
        """
        address = None
        
        if self.GetCore() is None:


            from errors import HeccerNotAllocatedError

            raise HeccerNotAllocatedError()

        else:
            
            address = heccer_base.HeccerAddressVariable(self.GetCore(), serial, field)

        
        return address

#---------------------------------------------------------------------------

    def SetIntervalStart(self, dstart):

        if self.GetOptions() is not None:

            self.GetOptions().dIntervalStart = dstart

        else:

            from errors import HeccerOptionsError

            raise HeccerOptionsError("Heccer Options are not allocated")


#---------------------------------------------------------------------------  


    def GetIntervalStart(self):

        if self.GetOptions() is not None:

            return self.GetOptions().dIntervalStart

        else:

            from errors import HeccerOptionsError

            raise HeccerOptionsError("Heccer Options are not allocated")

#---------------------------------------------------------------------------


    def SetIntervalEnd(self, dend):

        if self.GetOptions() is not None:

            self.GetOptions().dIntervalEnd = dend

        else:

            from errors import HeccerOptionsError

            raise HeccerOptionsError("Heccer Options are not allocated")


#---------------------------------------------------------------------------  

    def GetIntervalEnd(self):

        if self.GetOptions() is not None:

            return self.GetOptions().dIntervalEnd

        else:

            from errors import HeccerOptionsError

            raise HeccerOptionsError("Heccer Options are not allocated")


#---------------------------------------------------------------------------  

    def SetConcentrationGateStart(self, dconc):

        if self.GetOptions() is not None:

            self.GetOptions().dConcentrationGateStart = dconc

        else:

            from errors import HeccerOptionsError

            raise HeccerOptionsError("Heccer Options are not allocated")


#---------------------------------------------------------------------------  

    def GetConcentrationGateStart(self):

        if self.GetOptions() is not None:

            return self.GetOptions().dConcentrationGateStart

        else:

            from errors import HeccerOptionsError

            raise HeccerOptionsError("Heccer Options are not allocated")

#---------------------------------------------------------------------------  

    def SetConcentrationGateEnd(self, dconc):

        if self.GetOptions() is not None:

            self.GetOptions().dConcentrationGateEnd = dconc

        else:

            from errors import HeccerOptionsError

            raise HeccerOptionsError("Heccer Options are not allocated")

#---------------------------------------------------------------------------  

    def GetConcentrationGateEnd(self):

        if self.GetOptions() is not None:

            return self.GetOptions().dConcentrationGateEnd

        else:

            from errors import HeccerOptionsError

            raise HeccerOptionsError("Heccer Options are not allocated")


#---------------------------------------------------------------------------         

    def WriteToFile(self, filename):
        """!
        @brief Writes out heccer to a file
        """
        if self.GetCore() is not None:

            heccer_base.HeccerWriteToFile(self.GetCore(), filename)

        else:

            from errors import HeccerNotAllocatedError

            raise HeccerNotAllocatedError()



#---------------------------------------------------------------------------

    def Step(self, time):
        """!
        @brief
        """

        if self.GetCore() is not None:

            return heccer_base.HeccerHeccs(self.GetCore(), time)

        else:

            from errors import HeccerNotAllocatedError

            raise HeccerNotAllocatedError()

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

        if self.GetCore() is not None:
            
            heccer_base.HeccerCompileP1(self.GetCore())
            heccer_base.HeccerCompileP2(self.GetCore())
            heccer_base.HeccerCompileP3(self.GetCore())

        else:

            from errors import HeccerNotAllocatedError

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
        if self.GetCore() is not None:
        
            self.GetCore().dStep = dt

        else:

            from errors import HeccerNotAllocatedError
        
            raise HeccerNotAllocatedError()
    
#---------------------------------------------------------------------------

    def GetTimeStep(self):

        if self.GetCore() is not None:
        
            return self.GetCore().dStep 

        else:

            from errors import HeccerNotAllocatedError

            raise HeccerNotAllocatedError()


        
#************************* End Heccer **************************
