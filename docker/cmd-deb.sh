#!/bin/bash -e

echo "\n\nBuilding and packaging...\n\n"

make clean && make package-deb
