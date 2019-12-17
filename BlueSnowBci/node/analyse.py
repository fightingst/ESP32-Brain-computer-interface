def send(msg):
    print(json.dumps(msg)); sys.stdout.flush()

class Analyse:
    def __init__(self):
        data=json.loads(sys.argv[1])
        self.filtOpt=json.loads(sys.argv[2])
        if "chip2" in data:
            chip2=np.array(data["chip2"])
        if "filtOpt" in data:
            o=data["filtOpt"]
            b,a=signal.iirnotch(o["f0"],o["Q"],o["fs"])

    def filtAndFft(self,):


try:
    import sys; import json; import numpy as np
    from scipy import signal
    analyse = Analyse()
except Exception as e:
    send("Error: "+str(e))
