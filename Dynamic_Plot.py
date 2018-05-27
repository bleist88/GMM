"""
This class hosts an object which allows for dynamic plotting.
"""


from __imports__ import *

##  ============================================================================

class Dynamic_Plot:

    def __init__( self, figsize=(12,12) ):

        self.fig    = figsize

        self.x_lim  = None
        self.y_lim  = None
        self.z_lim  = None
