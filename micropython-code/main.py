import machine 
from machine import Pin
import time
import uasyncio as asyncio

led = Pin(22, Pin.OUT)

from sim800 import SIM800
sim800 = SIM800(uart_pin=1, baud=115200)

# async def blink_led():
#     while True:
#         led(1)
#         await asyncio.sleep_ms(500)
#         led(0)
#         await asyncio.sleep_ms(500)


# async def print_ntp():
#     import ntptime
#     BULGARIAN_TIME_OFFSET = 2 * 3600
#     ntptime.host = "0.bg.pool.ntp.org"
#     ntptime.settime()
#     while True:
#         local_time = time.localtime(time.time() + BULGARIAN_TIME_OFFSET)
#         print(local_time)
#         await asyncio.sleep(1)



# async def manage_display():
#     print("Managing display")
#     await asyncio.sleep(1)

# async def main():
#     # Schedule tasks
#     blink_led_Task = asyncio.create_task(blink_led())
#     print_time_Task = asyncio.create_task(print_ntp())
#     display_Task = asyncio.create_task(manage_display())

#     # Keep the tasks running indefinitely
#     await asyncio.gather(blink_led_Task, print_time_Task, display_Task)

# # Run the main event loop
# asyncio.run(main())