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

        error_msg = "The Heccer core data struct is not allocated: %s : %s" %
        (self.msg, self.value)
        
        return self.msg
