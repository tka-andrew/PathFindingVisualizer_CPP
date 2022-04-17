FROM ubuntu:20.04

# Needed for Ubuntu installation
ENV DEBIAN_FRONTEND=noninteractive 
ENV TZ=Etc/UTC

# Install CMake and some necessary packages
# REFERENCE: https://docs.wxwidgets.org/trunk/overview_install.html
# under Debian and Debian-derived systems such as Ubuntu, you need to run apt get libwxgtkX.Y-dev.
# REFERENCE : https://askubuntu.com/questions/1241217/package-libwxgtk3-0-dev-has-no-installation-candidate-on-ubuntu-20-04
# libwxgtk3.0-dev was changed to libwxgtk3.0-gtk3-dev in Ubuntu 20.04.
# REFERENCE: https://askubuntu.com/questions/971560/what-is-the-purpose-of-canberra-gtk-module
# libcanberra-gtk3-module is optional for this project actually
RUN apt-get update && apt-get install build-essential cmake libwxgtk3.0-gtk3-dev libcanberra-gtk3-module -y --no-install-recommends

RUN mkdir -p /src/PathFindingVisualizer/build
COPY . /src/PathFindingVisualizer/
WORKDIR /src/PathFindingVisualizer/build

# REFERENCE: https://unix.stackexchange.com/questions/230238/x-applications-warn-couldnt-connect-to-accessibility-bus-on-stderr
ENV NO_AT_BRIDGE=1

# This command runs your application, comment out this line to compile only
CMD ["./PathFindingVisualizer"]

LABEL Name=pathfindingvisualizercpp Version=0.0.1
