#!/usr/bin/env python3

import asyncio
import websockets

connected = set()

async def handler(websocket, path):
    global connected
    # Register.
    connected.add(websocket)
    try:
        async for message in websocket:
            print("Got message: " + message)
            for ws in connected:
                await ws.send("Broadcast: " + message)
    finally:
        # Unregister.
        connected.remove(websocket)

start_server = websockets.serve(handler, 'localhost', 9876)
asyncio.get_event_loop().run_until_complete(start_server)
asyncio.get_event_loop().run_forever()

