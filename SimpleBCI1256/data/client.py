import asyncio
import websockets

async def hello(uri):
    async with websockets.connect(uri) as websocket:
        await websocket.send("Hello world!")
        msg = await websocket.recv()
        print(msg)
while 1:
    asyncio.get_event_loop().run_until_complete(
        hello('ws://192.168.4.1:81'))

