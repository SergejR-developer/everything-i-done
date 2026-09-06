import time
import threading
import ctypes
import sys
import os

from playsound import playsound
import pystray
from pystray import MenuItem as item
from PIL import Image, ImageDraw

import configparser

#CONFIG

config = configparser.ConfigParser()
config.read_file(open(os.getcwd() + r'\reminder\cfg.txt'))

WORK_TIME = config.get('CONFIG', 'WORK_TIME')
REST_TIME = config.get('CONFIG', 'REST_TIME')

BEEP1 = config.get('CONFIG', 'BEEP1')
BEEP2 = config.get('CONFIG', 'BEEP2')

#------

running = True
paused = False

def interruptible_sleep(seconds):
    for _ in range(int(seconds)):
            if not running:
                return False
            while paused:
                time.sleep(0.5)
            time.sleep(1)
    return True
            

def reminder_loop():
    global running

    while running:
        ctypes.windll.user32.MessageBoxW(0, "Start working.", "20 20 20", 0)
        
        if not interruptible_sleep(WORK_TIME):
            break
        
        playsound(BEEP1)

        ctypes.windll.user32.MessageBoxW(0, "Look far.", "20 20 20", 0)
        
        if not interruptible_sleep(REST_TIME):
            break

        playsound(BEEP2)

    sys.exit()

#TRAY LOGIC

def on_pause(icon, item):
    global paused
    paused = True

def on_resume(icon, item):
    global paused
    paused = False

def on_exit(icon, item):
    global running
    running = False
    icon.stop()

#TRAY ICON SETUP

def create_image():
    image = Image.new("RGB", (64, 64), "black")
    draw = ImageDraw.Draw(image)
    draw.rectangle((16, 16, 48, 48), fill="white")
    return image

menu = (
    item('Pause', on_pause),
    item('Resume', on_resume),
    item('Exit', on_exit)
)

icon = pystray.Icon(
    'EyeReminder',
    create_image(),
    'Eye Reminder',
    menu
)

#START

threading.Thread(target=reminder_loop, daemon=True).start()
icon.run()