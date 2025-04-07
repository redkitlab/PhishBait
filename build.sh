PLATFORM=$(uname)
PROJECT_DIR="build"
cd CLI
mkdir $PROJECT_DIR
cd $PROJECT_DIR

if [ "$PLATFORM" == "Darwin" ]; then
    cmake ..
elif [ "$PLATFORM" == "Linux" ]; then
    cmake ..
elif [[ "$PLATFORM" == *"NT"* ]]; then
    if command -v ninja &> /dev/null; then
        cmake -G "Ninja" ..
    else
        cmake -G "Visual Studio 16 2019" ..
    fi
else
    echo "Unsupported platform: $PLATFORM"
    exit 1
fi

if command -v ninja &> /dev/null; then
    ninja
else
    make
fi

if [ "$PLATFORM" == "Darwin" ] || [ "$PLATFORM" == "Linux" ]; then
    ./PhishBait
elif [[ "$PLATFORM" == *"NT"* ]]; then
    ./PhishBait.exe
fi