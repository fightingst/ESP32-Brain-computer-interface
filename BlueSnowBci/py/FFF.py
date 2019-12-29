import asyncio




import websockets; import json
import numpy as np
from scipy import signal,fftpack
import pyqtgraph as pg
import time
uri="ws://192.168.2.119:81"
b,a=signal.iirnotch(50,30,1000)

x = np.arange(1000)
y = np.random.normal(size=(3, 1000))
plotWidget = pg.plot(title="Three plot curves")
for i in range(3):
    plotWidget.plot(x, y[i], pen=(i,3))

time.sleep(1000)

######################## keypress ########################
from pynput import keyboard

def on_press(key):
    print(f"{key} pressed")

listener=keyboard.Listener(on_press=on_press).start()

######################## ws data ########################

async def plot(y):
    plotWidget.plot(x, y[0], pen=(0,8),clear=True)
    for i in range(7):
        plotWidget.plot(x, y[i+1], pen=(i,8))

async def analyse(msg):
    m= json.loads(msg)
    filtered=signal.filtfilt(b,a,m["data"])
    ffted=np.abs(fftpack.fft(m["data"]))
    print("anal")
    #await plot(z)
    plotWidget.plot(x, filtered[0],clear=True)

async def wsRoutine():
    async with websockets.connect(uri) as ws:
        while 1:
            msg = await ws.recv()
            #print(msg)
            await analyse(msg)

######################## main ########################
async def main():
    await asyncio.gather(wsRoutine())
#asyncio.run(main())
