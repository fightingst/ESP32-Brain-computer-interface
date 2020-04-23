import numpy as np
import matplotlib.pyplot as plt
import asyncio, websockets, json
from scipy import signal, fftpack
import time
from pynput import keyboard

######################## funcDef ########################

def on_press(key):
    print(f"{key} pressed")

async def analyse(msg,doPlot=False):
    m = json.loads(msg)
    print(msg)
    filtered = signal.filtfilt(b,a,m["data"])
    ffted = np.abs(fftpack.fft(filtered))
    print("done analyzing")
    if doPlot : plot(filtered,ffted)

def plot(filtered,ffted):
    print(filtered.shape,ffted.shape)
    filtLine.set_ydata(filtered[0]); fftLine.set_ydata(ffted[0])
    fig.canvas.draw(); fig.canvas.flush_events()

async def wsRoutine():
    async with websockets.connect(uri) as ws:
        while 1:
            msg = await ws.recv()
            await analyse(msg,doPlot=True)

async def main():
    await asyncio.gather(wsRoutine())

######################## main ########################
b, a = signal.iirnotch(w0=55,Q=30,fs=1000)
sampleSize = 100
uri="ws://192.168.4.1:81"

plt.ion()
fig = plt.figure()
filtPlt = fig.add_subplot(121); fftPlt = fig.add_subplot(122)
x = np.linspace(0,6*np.pi,sampleSize)
y = np.sin(x)
filtLine, = filtPlt.plot(x,y); fftLine, = filtPlt.plot(x,y)

listener=keyboard.Listener(on_press=on_press).start()
asyncio.run(main())
