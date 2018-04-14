#!/bin/bash

aclocal
wait

autoconf
wait

automake --add-missing
wait
