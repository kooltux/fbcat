#!/bin/sh

export ECORE_EVAS_ENGINE=fb
export ELM_ENGINE=fb

if [ -e /dev/fb1 ]; then
	export EVAS_FB_DEV=${1:-/dev/fb1}
else
	export EVAS_FB_DEV=${1:-/dev/fb0}
fi

exec $(dirname $0)/fbcat.real 

