
def send(msg):
    print(json.dumps(msg)); sys.stdout.flush()

def analyse():
    o=json.loads(sys.argv[1]) # options
    m=json.loads(sys.argv[2]) # esp32 message
    b,a=signal.iirnotch(o["f0"],o["Q"],o["fs"])
    filtered=signal.filtfilt(b,a,m["data"]).tolist()
    ffted=np.abs(fft(m["data"])).tolist()
    send({"filtered":filtered,"ffted":ffted})

try:
    import sys; import json; import numpy as np
    from scipy import signal
    from scipy.fftpack import fft
    analyse()
except Exception as e:
    send("PyErr: "+str(e))
