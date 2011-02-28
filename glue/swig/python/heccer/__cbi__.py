"""
@file __cbi__.py

This file provides data for a packages integration
into the CBI architecture.
"""

def GetRevisionInfo():
# $Format:    "return \"${monotone_id}\""$
    return "63153100d5649f717b40876dc6a6de3d85b9d766"

def GetPackageName():
# $Format:    "return \"${package}\""$
    return "sspy"


def GetVersion():
# $Format:    "return \"${major}.${minor}.${micro}-${label}\""$
    return "0.0.0-alpha"

def GetDependencies():
    """!
    @brief Provides a list of other CBI dependencies needed.
    """
    dependencies = []

    return dependencies
