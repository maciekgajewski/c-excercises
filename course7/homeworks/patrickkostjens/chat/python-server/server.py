#!/usr/bin/env python3

import asyncio
import websockets
import json
import sys

class User():
    user_data = {}
    name = None
    def __init__(self, socket):
        self.socket = socket
    
    def is_registered(self):
        return self.name != None
    
    def register(self, name):
        self.name = name

    def get_name(self):
        return self.name

    def get_user_data(self):
        return self.user_data

connected = set()

async def broadcast(obj, skip_user=None):
    global connected

    message = json.dumps(obj)
    print("Broadcasting: " + message)
    for user in connected:
        if user.is_registered() and user != skip_user:
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
            obj = {}
            try:
                obj = json.loads(message)
            except:
                print("Unexpected error", sys.exc_info())
                print("Invalid message: " + message)
                await send(user, {"type" : "handshake_reply", "error": "Invalid message"})
                continue

            if user.is_registered():
                if obj["type"] == "send_message":
                    await broadcast({"type" : "on_message", "message": obj["message"], "username": user.get_name()}, user)
                elif obj["type"] == "handshake":
                    await send(user, {"type": "handshake_reply", "error": "already registered"})
                else:
                    await send(user, {"type": "error", "error": "unknown message type"})
            else:
                if obj["type"] == "handshake":
                    if not obj["name"]:
                        await send(user, {"type": "handshake_reply", "error": "Empty name not allowed"})
                        continue
                    await broadcast({"type": "user_joined", "name": obj["name"]})
                    user.register(obj["name"])
                    user_list = [{"name": x.get_name(), "data": x.get_user_data()} for x in connected if x.is_registered()]
                    await send(user, {"type": "handshake_reply", "user_list": user_list, "server_info": "Basic Python server"})
                else:
                    await send(user, {"type": "handshake_reply", "error": "Not yet registered"})
    finally:
        connected.remove(user)
        websocket.close()
        print(user.get_name() + " is leaving")
        await broadcast({"type": "user_left", "name": user.get_name(), "user_data": user.get_user_data()})

start_server = websockets.serve(handler, 'localhost', 9876)
asyncio.get_event_loop().run_until_complete(start_server)
asyncio.get_event_loop().run_forever()

