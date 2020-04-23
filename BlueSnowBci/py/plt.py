import pyqtgraph as pg
import numpy as np
x = np.arange(100)
y = np.random.normal(size=(3, 100))
"""
plotWidget = pg.plot(title="Three plot curves")
for i in range(3):
    plotWidget.plot(x, y[i], pen=(i,3))
"""
import matplotlib.pyplot as plt
import asyncio
import websockets; import json
from scipy import signal,fftpack
import time

uri="ws://192.168.4.1:81"
b,a=signal.iirnotch(50,30,1000)
plt.ion()
fig = plt.figure()
ax = fig.add_subplot(111)
x = np.linspace(0, 6*np.pi, 100)[:10]
y = 5*np.sin(x)
line1, = ax.plot(x, y, 'r-')
line2, = ax.plot(x, y, 'r-')

"""
async def plot(y):
    plotWidget.plot(x, y[0], pen=(0,8),clear=True)
    for i in range(7):
        plotWidget.plot(x, y[i+1], pen=(i,8))
"""
async def analyse(msg):
    m= json.loads(msg)
    filtered=signal.filtfilt(b,a,m["data"])/2**20-1.876
    filtered=filtered-np.mean(filtered)
    ffted=np.abs(fftpack.fft(filtered))
    print("anal")
    line1.set_ydata(ffted[0][:10])
    line2.set_ydata(ffted[1][:10]
                    )
    print(filtered[0][0],filtered[1][0])
    fig.canvas.draw()
    fig.canvas.flush_events()
    
    #await plot(z)
    #plotWidget.plot(x, filtered[0],clear=True)

async def wsRoutine():
    async with websockets.connect(uri) as ws:
        while 1:
            msg = await ws.recv()
            #print(msg)
            await analyse(msg)

######################## main ########################
async def main():
    await asyncio.gather(wsRoutine())
asyncio.run(main())
