import asyncio

######################## keypress ########################
from pynput import keyboard

def on_press(key):
    print(f"{key} pressed")

listener=keyboard.Listener(on_press=on_press).start()

######################## ws data ########################
import websockets; import json
import numpy as np
from scipy import signal,fftpack

uri="ws://192.168.2.154:81"
b,a=signal.iirnotch(50,30,1000)

async def analyse(msg):
    m= json.loads(msg)
    filtered=signal.filtfilt(b,a,m["data"])
    print("filtered")
    ffted=np.abs(fftpack.fft(m["data"]))
    print("ffted")

async def wsRoutine():
    async with websockets.connect(uri) as ws:
        while 1:
            msg = await ws.recv()
            await analyse(msg)


async def main():
    await asyncio.gather(wsRoutine())
asyncio.run(main())
