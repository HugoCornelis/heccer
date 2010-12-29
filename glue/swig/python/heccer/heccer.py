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


def GetVersion():

    return heccer_base.HeccerGetVersion()



#************************* Heccer Mathcomponent constants **************************
#
# Moved these here so that these constants can be accessible from the top level 
# import of the heccer module.
#
MATH_TYPE_ChannelConc = heccer_base.MATH_TYPE_ChannelConc 
MATH_TYPE_ChannelActConc = heccer_base.MATH_TYPE_ChannelActConc
MATH_TYPE_ChannelActInact = heccer_base.MATH_TYPE_ChannelActInact
MATH_TYPE_ChannelPersistentSteadyStateDualTau = heccer_base.MATH_TYPE_ChannelPersistentSteadyStateDualTau
MATH_TYPE_ChannelPersistentSteadyStateTau = heccer_base.MATH_TYPE_ChannelPersistentSteadyStateTau
MATH_TYPE_ChannelSpringMass = heccer_base.MATH_TYPE_ChannelSpringMass
MATH_TYPE_ChannelSteadyStateSteppedTau = heccer_base.MATH_TYPE_ChannelSteadyStateSteppedTau 
MATH_TYPE_Compartment = heccer_base.MATH_TYPE_Compartment 
MATH_TYPE_ExponentialDecay = heccer_base.MATH_TYPE_ExponentialDecay 
MATH_TYPE_GHK = heccer_base.MATH_TYPE_GHK 
MATH_TYPE_InternalNernst = heccer_base.MATH_TYPE_InternalNernst 
MATH_TYPE_MGBlocker = heccer_base.MATH_TYPE_MGBlocker 
MATH_TYPE_SpikeGenerator = heccer_base.MATH_TYPE_SpikeGenerator
MATH_TYPE_Concentration = heccer_base.MATH_TYPE_Concentration 
MATH_TYPE_GateConcept = heccer_base.MATH_TYPE_GateConcept 
MATH_TYPE_CallOut_flag = heccer_base.MATH_TYPE_CallOut_flag
MATH_TYPE_CallOut_conductance_current = heccer_base.MATH_TYPE_CallOut_conductance_current

#********************* End Heccer Mathcomponent constants **************************



#************************* Begin Heccer **************************
class Heccer:

    """!
    @class Heccer

    The Heccer class manages a heccer solver object and its options.

    """

#---------------------------------------------------------------------------

    def __init__(self, name="Untitled", pts=None, ped=None,
                 peq=None, iOptions=None, dStep=None,
                 pinter=None, filename=None):
        """!
        @brief Constructor
        @param name The identifier for this Heccer
        @param pts Pointer to a translation service
        @param ped Pointer to an event queuer object
        @param iOptions
        @param dStep Step size value
        @param pinter A pointer to an intermediary
        """

        self._options_core = None

        self._p1 = False
        self._p2 = False
        self._p3 = False

        self._is_constructed = False
        
        if filename is not None:

            if os.path.isfile(filename):

                self._heccer_core = heccer_base.HeccerFromFile(filename)

        elif pinter is not None:

            self._heccer_core = heccer_base.HeccerNewP2(name, pinter)
            
        elif iOptions is not None and dStep is not None:

            self._heccer_core = heccer_base.HeccerNewP1(name, pts, ped, peq, iOptions, dStep)

        else:

            self._heccer_core = heccer_base.HeccerNew(name, pts, ped, peq)



        if self._heccer_core.ho is not None:
    
            self._options_core = self._heccer_core.ho

        else:

            self._options_core = heccer_base.HeccerOptions()
        
#-----------------------------------------------------------------------------

#         if 'model_source' in options:
            
#             self._heccer_core = heccer_base.HeccerNew(name, None, None, None)

#         else:
            
#             print "model_source not found in the heccer options, cannot construct a heccer"


#         if isinstance(options, heccer_base.HeccerOptions):

#             self._options_core = options

#         else:

#             self._options_core = heccer_base.HeccerOptions()


#---------------------------------------------------------------------------

    def New(cls, name, pts, ped, peq):
        """!
        @brief Factory Method
        @param name Name for this heccer object
        @param pts Pointer to a translation service
        @param ped Pointer to an event queuer object
        
        """
        obj = cls(name=name, pts=pts, ped=ped, peq=peq)
        
        return obj        

#---------------------------------------------------------------------------

    def NewP1(cls, name , pts, ped, peq, iOptions, dStep):
        """!
        @brief Factory Method
        @param name Name for this heccer object
        @param pts Pointer to a translation service
        @param ped Pointer to an event distributor
        @param iOptions
        @param dStep Step size value
        """
        obj = cls(name=name, pts=pts, ped=ped, iOptions=iOptions, dStep=dStep)

        return obj

#---------------------------------------------------------------------------

    def NewP2(cls, name, pinter):
        """!
        @brief Factory Method
        """
        obj = cls(name=name, pinter=pinter)

        return obj

#---------------------------------------------------------------------------

    def NewFromFile(cls, filename):
        """!
        @brief Factory Method
        @param pc 
        """
        obj = cls(filename=filename)

        return obj
        
#---------------------------------------------------------------------------

    def Construct(self):
        """
        @brief Constructs heccer from the options
        """
        if self.GetCore() is not None:

            heccer = self.GetCore()
            
        else:

            from errors import HeccerNotAllocatedError

            raise HeccerNotAllocatedError()



        if self.GetOptions() is not None:

            options = self.GetOptions()

        else:

            from errors import HeccerOptionsError

            raise HeccerOptionsError("Heccer Options are not allocated")


        
        if 'model_source' not in options:

            raise HeccerOptionsError("model_source not found in the heccer options, cannot construct a heccer")
        
            return None


        # Probably need to check allow options to be passed to the next two
        # args
        result = heccer_base.HeccerConstruct( heccer,
                                     options['model_source'],
                                     options['name'],
                                     None,
                                     None
                                     )
        return result

#---------------------------------------------------------------------------

    def IsConstructed(self):

        return self._is_constructed

#---------------------------------------------------------------------------

    def GetCore(self):
        """!
        @brief Returns the internal raw heccer struct
        """
        return self._heccer_core


#---------------------------------------------------------------------------

    def SetCore(self, hecc):
        """!
        @brief Sets the core heccer to the value passed in hecc
        """
        self._heccer_core = hecc

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

        elif isinstance(ho, dict):

            pass


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




    def SetSmallTableSize(self, size):

        if self.GetOptions() is not None:

            self.GetOptions().iSmallTableSize = size

        else:

            from errors import HeccerOptionsError

            raise HeccerOptionsError("Heccer Options are not allocated")

#---------------------------------------------------------------------------  

    def SetIntervalEntries(self, entries):

        if self.GetOptions() is not None:

            self.GetOptions().iIntervalEntries = entries

        else:

            from errors import HeccerOptionsError

            raise HeccerOptionsError("Heccer Options are not allocated")


    def GetIntervalEntries(self):

        if self.GetOptions() is not None:

            return self.GetOptions().iIntervalEntries

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

    def IsActivatorSet(self):

        
        if self.GetOptions() is not None:

            value = self.GetOptions().iActivatorSet

            if value != 0:

                return True

            else:

                return False

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

    def Initiate(self):
        """!
        @brief 
        """
        if self.GetCore() is not None:

            heccer_base.HeccerInitiate(self.GetCore())

        else:

            from errors import HeccerNotAllocatedError

            raise HeccerNotAllocatedError("Can't initiate, Heccer not allocated")


#--------------------------------------------------------------------------- 

    def Dump(self, file, selection):
        """!

        """
        my_file = None
        
        if self.GetCore() is not None:

            if file == 0:

                my_file = None
                
            heccer_base.HeccerDump(self.GetCore(), my_file, selection)

        else:

            from errors import HeccerNotAllocatedError

            raise HeccerNotAllocatedError()

#---------------------------------------------------------------------------

    def DumpV(self):
        """!

        """
        if self.GetCore() is not None:

            heccer_base.HeccerDumpV(self.GetCore())

        else:

            from errors import HeccerNotAllocatedError

            raise HeccerNotAllocatedError()   

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

    def CompileAll(self):
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

    def CompileP1(self):
        """!
        @brief This compiles the solver for the Heccer core
        """

        if self.GetCore() is not None:
            
            heccer_base.HeccerCompileP1(self.GetCore())

        else:

            from errors import HeccerNotAllocatedError

            raise HeccerNotAllocatedError()


#---------------------------------------------------------------------------

    def CompileP2(self):
        """!
        @brief This compiles the solver for the Heccer core
        """

        if self.GetCore() is not None:
            
            heccer_base.HeccerCompileP2(self.GetCore())

        else:

            from errors import HeccerNotAllocatedError

            raise HeccerNotAllocatedError()


#---------------------------------------------------------------------------

    def CompileP3(self):
        """!
        @brief This compiles the solver for the Heccer core
        """

        if self.GetCore() is not None:
            
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





#************************* Start HeccerOptions **************************
# class HeccerOptions(heccer_base.HeccerOptions):

#     def __init__(self, options=, corrections=, 
#                  interval_set=1, interval_start=-0.1, interval_end=0.05,
#                  activator_set=0,
#                  concentration_gate_start=0, concentration_gate_end=,
#                  interval_entries=3000, small_table_size=):


#************************* End HeccerOptions ****************************
        

#************************* Start Intermediary **************************

class Intermediary(heccer_base.Intermediary):



    def __init__(self, compartments=None, comp2mech=None):

        heccer_base.Intermediary.__init__(self)

        if compartments is not None:
            
            self.SetCompartments(compartments)

        if comp2mech is not None:

            self.SetComp2Mech(comp2mech)


#---------------------------------------------------------------------------

    def SetCompartments(self, comps):
        """!
        @brief Sets a python list into a C array
        """

        if comps is None:

            return

        if self.pcomp is not None:
        
            heccer_base.delete_CompartmentArray(self.pcomp)
            
        if isinstance(comps, list):
            
            num_comps = len(comps)
            
            self.pcomp = heccer_base.new_CompartmentArray(num_comps)

            
            for index, c in enumerate(comps):

                heccer_base.CompartmentArray_setitem(self.pcomp, index, c)

            self.SetNumCompartments(num_comps)
            
        else:

            # If it's not a list then just set the value

            self.pcomp = heccer_base.new_CompartmentArray(1)

            heccer_base.CompartmentArray_setitem(self.pcomp, 0, comps)

            self.SetNumCompartments(1)


#---------------------------------------------------------------------------

    def GetCompartment(self, index):
        """!
        @brief 
        """

        c = heccer_base.CompartmentArray_getitem(self.pcomp,index)

        return c


#---------------------------------------------------------------------------

    def SetNumCompartments(self, ncomp):

        self.iCompartments = ncomp
        

#---------------------------------------------------------------------------

    def SetComp2Mech(self, c2m):

        if self.piC2m is not None:

            heccer_base.delete_IntArray(self.piC2m)

        size = 0
        
        if isinstance(c2m, list):

            size = len(c2m)

            self.piC2m = heccer_base.new_IntArray(size)

            for index, c in enumerate(c2m):

                heccer_base.IntArray_setitem(self.piC2m, index, c)

        else:

            size = 1

            self.piC2m = heccer_base.new_IntArray(size)

            heccer_base.IntArray_setitem(self.piC2m, 0, c2m)


#************************* End Intermediary *****************************
