

import os
import pdb
import sys

try:

    import heccer_base

except ImportError, e:
    
    sys.exit("Could not import compiled SWIG heccer_base library: %s" % e)



DES_DUMP_ALL=heccer_base.DES_DUMP_ALL
DES_DUMP_ALL_EXTENDED=heccer_base.DES_DUMP_ALL_EXTENDED
DES_DUMP_ALL_REDUCED=heccer_base.DES_DUMP_ALL_REDUCED
DES_DUMP_SERVICE=heccer_base.DES_DUMP_SERVICE
DES_DUMP_DISTRIBUTOR_MATRIX=heccer_base.DES_DUMP_DISTRIBUTOR_MATRIX
DES_DUMP_QUEUER_MATRIX=heccer_base.DES_DUMP_QUEUER_MATRIX


#************************* Start DES *******************************************

class DES:


#---------------------------------------------------------------------------

    def __init__(self, name="Untitled DES", model_name=None, model_source=None, options=None):

        self.name = name

        # This is a pointer to a simobj DES struct
        self._des = heccer_base.DESNew(1)

        if self._des is None:

            raise Exception("Allocation Error, Can't create DES object")

        
        if not options is None:

            pass


        else:

            self.options =  options

        self._constructed = False
        self._projections_set = False
        self._solvers_connected = False

        self.time_step = None

        self.projections = []

        self.model_name = model_name

        self.model_source = model_source

#---------------------------------------------------------------------------

    def Construct(self, model=None):

        if self._des is None:
            # should never really be here but just in case
            # I need to do some sort of a reset
            self._des = heccer_base.DESNew(1)

        

#---------------------------------------------------------------------------

    def SetModel(self, model_source):
        """

        """
        self.model_source = model_source

#---------------------------------------------------------------------------

    def SetProjection(self, projection):

        if not self.model_source is None:

            pass
        
#---------------------------------------------------------------------------

    def Connect(self, model_source=None):

        if self._solvers_connected:

            raise Exception("Solvers have already been connected")
        
        elif self.model_source is None:

            if not model_source is None:

                self.model_source = model_source
                
            else:
                
                raise Exception("Can't connect solvers, no model source")

        else:

            # an exception here will break it out

            try:
                
                self.model_source.SetAllProjectionQueries()

            except Exception, e:

                raise errors.ConnectionError("Can't construct projection matrix: %s" % e)

            model_core = self.model_source.GetCore()

            # might need to change this to just pass model_core
            result = heccer_base.DESConnect(model_core.psr, model_core.ppq)

            if result == 0:

                raise errors.ConnectionError("Can't connect create connection matrix")

            else:

                self._solvers_connected = True

#---------------------------------------------------------------------------

    def AddOutput(self, output=None, type=None):

        
        pass

#---------------------------------------------------------------------------

    def GetDistributor(self):

        pass

#---------------------------------------------------------------------------

    def Compile(self):

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





