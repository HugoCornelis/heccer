

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
        self._connected = False

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


    # alias
    Initiate = Construct

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

        if self._connected:

            raise Exception("Solvers have already been connected")
        
        elif self.model_source is None:

            if not model_source is None:

                self.model_source = model_source
                
            else:
                # an exception here will break it out if we have no model
                # source to connect to.
                raise Exception("Can't connect solvers, no model source")



        try:
                
            self.model_source.SetAllProjectionQueries()

        except Exception, e:

            raise errors.ConnectionError("Can't construct projection matrix: %s" % e)


        # set all projection queries to indices before connecting to DES

        if not self.model_source.ProjectionIndicesBuilt():

            self.model_source.SetAllProjectionQueries()

            
        model_core = self.model_source.GetCore()

        # might need to change this to just pass model_core
        result = heccer_base.DESConnect(self._des, model_core.psr, model_core.ppq)

        if result == 0:

            raise errors.ConnectionError("Can't connect create connection matrix")

        else:

            self._connected = True

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





