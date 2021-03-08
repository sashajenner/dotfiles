#!/usr/bin/env bash

# Set main external monitor above laptop monitor
xrandr --output eDP-1 --auto --below DP-1

# Set background image
setbg /home/en0cs/Pictures/backgrounds

# Set brightness to same as previously
bright-control same

# Connect to VPN
piactl connect

# Setup daemons if not already running
if ! pgrep mpd; then
    mpd
fi
if ! pgrep transmission; then
    transmission-daemon
fi

# For transparency of st terminal
xcompmgr &

# Setup auto-updating status bar
dwmblocks &

# Turn on the screensaver after 2 min inactivity
xset s 120
# Invoke the lock screen when screensaver on
xsidle.sh slock &

# Startup dwm
exec dwm
