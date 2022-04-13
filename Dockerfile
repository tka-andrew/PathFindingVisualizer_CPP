FROM ubuntu:20.04

# Needed for Ubuntu installation
ENV DEBIAN_FRONTEND=noninteractive 
ENV TZ=Etc/UTC

# Install CMake and some necessary packages
RUN apt-get update && apt-get install build-essential cmake -y --no-install-recommends
RUN apt install libgtk-3-dev libwxgtk3.0-gtk3-dev libcanberra-gtk-module libcanberra-gtk3-module -y --no-install-recommends

RUN mkdir -p /src/PathFindingVisualizer/build
COPY . /src/PathFindingVisualizer/
WORKDIR /src/PathFindingVisualizer/build

# REFERENCE: https://unix.stackexchange.com/questions/230238/x-applications-warn-couldnt-connect-to-accessibility-bus-on-stderr
ENV NO_AT_BRIDGE=1

# This command runs your application, comment out this line to compile only
CMD ["./PathFindingVisualizer"]

LABEL Name=pathfindingvisualizercpp Version=0.0.1
