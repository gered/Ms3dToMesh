#!/bin/sh
type premake4 >/dev/null 2>&1 || { echo >&2 "'premake4' not found in your path."; exit 1; }
premake4 --file=premake.lua gmake
