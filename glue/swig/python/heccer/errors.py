from exceptions import Exception


class AddressError(Exception):
    """

    """
    def __init__(self, cause):
        self.cause = cause

    def __str__(self):
        return self.cause


class HeccerNotAllocatedError(Exception):
    """

    """
    def __init__(self,msg):
        self.msg = msg
    
    def __str__(self):

        error_msg = "The Heccer core data struct is not allocated\n %s : %s" % (self.msg, self.value)
        
        return error_msg

class HeccerOptionsError(Exception):
    """

    """
    def __init__(self,msg):
        self.msg = msg
    
    def __str__(self):

        error_msg = "Error in the Heccer options\n %s : %s" % (self.msg, self.value)
        
        return error_msg


class HeccerCompileError(Exception):
    """

    """
    def __init__(self,msg):
        self.msg = msg
    
    def __str__(self):

        error_msg = "Error compiling Heccer\n %s : %s" % (self.msg, self.value)
        
        return error_msg
