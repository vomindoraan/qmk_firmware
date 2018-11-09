#!/bin/sh

USAGE="Usage: $0 [keyboard[:keymap[:target]]]"

# Check preconditions
for arg; do
    if [ "$arg" = "--help" ]; then
        echo "$USAGE"
        exit 0
    fi
done
if [ $# -gt 1 ]; then
    echo "$USAGE" >&2
    exit 1
elif ! command -v docker >/dev/null 2>&1; then
    echo "Error: docker not found" >&2
    echo "See https://docs.docker.com/install/#supported-platforms for installation instructions" >&2
    exit 2
fi

# Determine arguments
if [ $# -eq 0 ]; then
    printf "keyboard=" && read -r keyboard
    [ -n "$keyboard" ] && printf "keymap=" && read -r keymap
    [ -n "$keymap"   ] && printf "target=" && read -r target
else
    IFS=':' read -r keyboard keymap target x <<EOF
$1
EOF
    if [ -n "$x" ]; then
        echo "$USAGE" >&2
        exit 1
    fi
fi
if [ -n "$target" ]; then
    if [ "$(uname)" = "Linux" ] || docker-machine active >/dev/null 2>&1; then
        usb_args="--privileged -v /dev/bus/usb:/dev/bus/usb"
    else
        echo "Error: target requires docker-machine to work on your platform" >&2
        echo "See http://gw.tnode.com/docker/docker-machine-with-usb-support-on-windows-macos" >&2
        exit 3
    fi
fi
dir=$(pwd -W 2>/dev/null) || dir=$PWD  # Use Windows path if on Windows

# Run container and build firmware
docker run --rm $usb_args -v "$dir":/qmk_firmware qmkfm/qmk_firmware \
    make "$keyboard${keymap:+:$keymap}${target:+:$target}"
