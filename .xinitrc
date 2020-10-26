#!/usr/bin/env bash

# Set background image
setbg $HOME/Pictures/backgrounds

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
