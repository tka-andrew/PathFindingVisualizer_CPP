FROM ubuntu:20.04

# Needed for Ubuntu installation
ENV DEBIAN_FRONTEND=noninteractive 
ENV TZ=Etc/UTC

# Install CMake
RUN apt-get update && apt-get install build-essential cmake -y --no-install-recommends

RUN mkdir -p /src/PathFindingVisualizer/build
COPY . /src/PathFindingVisualizer/
WORKDIR /src/PathFindingVisualizer/build

# This command runs your application, comment out this line to compile only
CMD ["./PathFindingVisualizer"]

LABEL Name=pathfindingvisualizercpp Version=0.0.1
