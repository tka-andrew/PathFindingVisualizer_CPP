# Path Finding Visualizer in CPP
This is mainly to visualize the path finding algorithm written in CPP.

## DEPLOYMENT MODE

### To build this image
```
./builldDockerImage.sh
```

### To run the docker image
```
./runDockerFile.sh
```

## DEVELOPMENT MODE

### Install libwxgtk3.0-dev binaries
```
sudo apt-get update -y
sudo apt-get install -y libwxgtk3.0-gtk3-dev  (PS: for Ubuntu 20.04)
sudo apt-get install -y libwxgtk3.0-dev  (PS: for other versions of Ubuntu)
```

## References
1. [wxWidgets + CMake: Multiplatform Superbuild](https://justdevtutorials.medium.com/wxwidgets-cmake-multiplatform-superbuild-4ea86c4e6eda) PS: this will be future reference
2. [How to Build/Compile a wxWidgets Project in the Easiest Way](https://www.youtube.com/watch?v=JD1fZWMokkY)