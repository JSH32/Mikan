#!/bin/bash

echo "Installing build dependencies for Mikan"

# Install packages from apt
sudo apt update
sudo apt install qt5-default qtdeclarative5-dev

# Get all submodule dependencies
git submodule update --init --recursive