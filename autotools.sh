#! /bin/sh

./bootstrap
wait

aclocal
wait

autoconf
wait

automake --add-missing
wait
