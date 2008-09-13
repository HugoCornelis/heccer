#!/usr/bin/python

import SwiggableHeccer

class AddressError:
    def __init__(self, cause):
        self.cause = cause

class Heccer:
    def __init__(self, options):
        if 'model_source' in options:
            self.backend = SwiggableHeccer.HeccerNew("heccer constructed from python", None, None, None)
            SwiggableHeccer.HeccerConstruct( self.backend, options['model_source'], options['name'], None )
        else:
            print "model_source not found in the heccer options, cannot construct a heccer"

    def Address(self, serial, field):
        return SwiggableHeccer.HeccerAddressVariable(self.backend, serial, field)
        
    def advance(self, time):
        return SwiggableHeccer.HeccerHeccs(self.backend, time)

    def compile(self):
        SwiggableHeccer.HeccerCompileP1(self.backend)
        SwiggableHeccer.HeccerCompileP2(self.backend)
        SwiggableHeccer.HeccerCompileP3(self.backend)

    def finish(self):
        pass

    def timestep(self, dt):
        self.backend.dStep = dt

class Output:
    def __init__(self, filename):
        self.backend = SwiggableHeccer.OutputGeneratorNew(filename)

    def advance(self, time):
        return SwiggableHeccer.OutputGeneratorTimedStep(self.backend, time)

    def compile(self):
        pass

    def AddOutput(self, name, address):
        SwiggableHeccer.OutputGeneratorAddVariable(self.backend, name, address)

    def finish(self):
        SwiggableHeccer.OutputGeneratorFinish(self.backend)
