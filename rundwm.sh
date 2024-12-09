#!/bin/bash

Xephyr -screen 1280x720 -reset -terminate -extension GLX 2>/dev/null :1 &
export DISPLAY=:1
sleep 0.1
./dwm
