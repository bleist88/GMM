
from __imports__ import *

for f in os.listdir("Output/"):
    if os.path.isdir("Output/" + f):
        print( "Cleaning Output/" + f )
        for h in os.listdir("Output/" + f):
            if ".dat" in h:
                os.remove("Output/" + f + "/" + h)
