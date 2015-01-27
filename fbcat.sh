#!/bin/sh

export ECORE_EVAS_ENGINE=fb
export ELM_ENGINE=fb
export EVAS_FB_DEV=${1:-/dev/fb0}

exec $(dirname $0)/fbcat.real 

