#!/bin/bash

Xephyr -screen 800x600+0+0 -reset -terminate -extension GLX +xinerama +extension RANDR 2>/dev/null :1 &
# Xephyr -screen 800x600+0+0 -screen 800x600+800+0 -reset -terminate -extension GLX +xinerama +extension RANDR 2>/dev/null :1 &
export DISPLAY=:1
sleep 0.1
./dwm
