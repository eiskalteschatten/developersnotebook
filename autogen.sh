#!/bin/sh

./bootstrap && autoheader && automake --add-missing && autoconf
