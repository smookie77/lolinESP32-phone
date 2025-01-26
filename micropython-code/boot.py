import network
import time

# Connect to Wi-Fi
ssid = "242.wifi.smooker.org"
password = "tplinkmotorola12"
wlan = network.WLAN(network.STA_IF)
wlan.active(True)
wlan.connect(ssid, password)

# Wait for connection
print("Connecting to wifi...", end="")
while not wlan.isconnected():
    time.sleep(1)
    print(".", end="")

print("Connected to Wi-Fi:", wlan.ifconfig())

import main