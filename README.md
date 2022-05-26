# Path Finding Visualizer in CPP
A desktop application developed to visualize the path finding algorithms written in C++. 
Take note that this project being tested on Ubuntu 20.04 environment only.

## RUNNING ON DOCKER CONTAINER

### To build this image
```
./builldDockerImage.sh
```

### To run the docker image
```
./runDockerFile.sh
```

## RUNNING ON LOCAL MACHINE

### Install libwxgtk3.0-dev binaries
```
sudo apt-get update -y
sudo apt-get install -y libwxgtk3.0-gtk3-dev  (PS: for Ubuntu 20.04)
sudo apt-get install -y libwxgtk3.0-dev  (PS: for other versions of Ubuntu)
```

### CMake and build
In this directory
```
mkdir build
cd build
cmake ..
cmake --build .
```

### Run the exectubale
```
./PathFindingVisualizer
```

## Dijkstra Algorithm vs A* Search vs Greedy Best First Search
### Example 01
![Dijkstra01](https://github.com/tka-andrew/PathFindingVisualizer_CPP/blob/master/images/Dijkstra01.png?raw=true)
![AStar01](https://github.com/tka-andrew/PathFindingVisualizer_CPP/blob/master/images/AStar01.png?raw=true)
![GreedyBestFirstSearch01](https://github.com/tka-andrew/PathFindingVisualizer_CPP/blob/master/images/GreedyBestFirstSearch01.png?raw=true)

### Example 02
![Dijkstra02](https://github.com/tka-andrew/PathFindingVisualizer_CPP/blob/master/images/Dijkstra02.png?raw=true)
![AStar02](https://github.com/tka-andrew/PathFindingVisualizer_CPP/blob/master/images/AStar02.png?raw=true)
![GreedyBestFirstSearch02](https://github.com/tka-andrew/PathFindingVisualizer_CPP/blob/master/images/GreedyBestFirstSearch02.png?raw=true)

## References
1. [Using CMake with wxWidgets application](https://docs.wxwidgets.org/trunk/overview_cmake.html)
2. [wxWidgets tutorials](https://www.wxwidgets.org/docs/tutorials/)
3. [wxWidgets + CMake: Multiplatform Superbuild](https://justdevtutorials.medium.com/wxwidgets-cmake-multiplatform-superbuild-4ea86c4e6eda) PS: this will be future reference
4. [How to Build/Compile a wxWidgets Project in the Easiest Way](https://www.youtube.com/watch?v=JD1fZWMokkY)
