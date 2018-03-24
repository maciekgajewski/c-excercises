#!/usr/bin/env python3

import asyncio
import websockets
import json
import sys

class User():
    name = None
    def __init__(self, socket):
        self.socket = socket
    
    def is_registered(self):
        return self.name != None
    
    def register(self, name):
        self.name = name

    def get_name(self):
        return self.name if self.is_registered() else "anonymous"

connected = set()

async def broadcast(obj):
    global connected

    message = json.dumps(obj)
    print("Broadcasting: " + message)
    for user in connected:
        if user.is_registered():
            await user.socket.send(message)

async def send(user, obj):
    await user.socket.send(json.dumps(obj))

async def handler(websocket, path):
    global connected
    user = User(websocket)
    connected.add(user)
    print("User connected")
    try:
        async for message in websocket:
            print("Got message: " + message)
            if user.is_registered():
                await broadcast({"type" : "on_message", "message": message, "username": user.get_name()})
            else:
                try:
                    obj = json.loads(message)
                    if obj["type"] == "handshake":
                        if not obj["name"]: raise "Empty name not allowed"
                        await broadcast({"type": "user_joined", "name": obj["name"]})
                        user.register(obj["name"])
                        await send(user, {"type": "handshake_reply", "user_list": [x.get_name() for x in connected if x.is_registered()], "server_info": "Basic Python server"})
                    else:
                        await send(user, {"type": "handshake_reply", "error": "Not yet registered"})
                except:
                    print("Unexpected error", sys.exc_info())
                    print("Invalid message: " + message)
                    await send(user, {"type" : "handshake_reply", "error": "Invalid message"})
    finally:
        connected.remove(user)
        websocket.close()
        print(user.get_name() + " is leaving")
        await broadcast({"type": "user_left", "name": user.get_name()})

start_server = websockets.serve(handler, 'localhost', 9876)
asyncio.get_event_loop().run_until_complete(start_server)
asyncio.get_event_loop().run_forever()

