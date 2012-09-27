

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

        # This is a pointer to a simobj DES struct
        self._des = heccer_base.DESNew(1)

        if self._des is None:

            raise Exception("Allocation Error, Can't create DES object")

        
        if not options is None:

            pass

        self._constructed = False
        self._projections_set = False
        self._solvers_connected = False

        self.time_step = None

        self.projections = []

        self.model_name = None

        self.model_source = None

#---------------------------------------------------------------------------

    def Construct(self, model=None):

        pass

#---------------------------------------------------------------------------

    def SetModel(self, model_source):
        """

        """
        self.model_source = model_source

#---------------------------------------------------------------------------

    def SetProjection(self, projection):

        if not self.model_source None:

            
            
        
#---------------------------------------------------------------------------

    def ConnectSolvers(self):

        if self._solvers_connected:

            raise Exception("Solvers have already been connected")
        
        elif self.model_source is None:

            raise Exception("Can't connect solvers, no model source")

        else:

            model_core = self.model_core.GetCore()
            
            result = heccer_base.DESConnect(model_core.psr, model_core.ppq)

            if result == 0:

                raise Exception("DESConnect Error: Can't connect create connection matrix")

            else:

                self._solvers_connected = True
        
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

#---------------------------------------------------------------------------

    def Finish(self):

        pass
    
#---------------------------------------------------------------------------

    def Report(self):

        pass


#--------------------------------------------------------------------------

    def Step(self, time=None):
        """
        @param time A time value for the DES to increment by
        
        Performs a step on the Discrete event system.
        """
        
        cpu_core = 0

        _time = time

        if not self.options is None:

            if self.options.has_key('cpu_core'):

                cpu_core = self.options['cpu_core']

            if self.options.has_key('time'):

                _time = self.options['time']

        queuer = heccer_base.DESGetQueuer(cpu_core)

        if _time is None:

            raise Exception("Can't perform step in DES object, no time value is present or in options")

        result = heccer_base.EventQueuerProcess(queuer, _time)

        return result
        
#************************* End DES *********************************************





#************************* Start Distributor ***********************************

class Distributor:


    def __init__(self):

        pass

#************************* End Distributor *************************************





#************************* Start Queuer ****************************************

class Queuer:


    def __init__(self):

        pass

#************************* End Queuer ******************************************