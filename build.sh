PLATFORM=$(uname)
PROJECT_DIR="build"
EXECUTABLE_NAME="PhishBait"
cd CLI || exit 1
mkdir -p "$PROJECT_DIR" && cd "$PROJECT_DIR" || exit 1

case "$PLATFORM" in
    Darwin|Linux)
        EXECUTABLE="./$EXECUTABLE_NAME"
        cmake ..
        ;;
    MINGW*|MSYS*|CYGWIN*|*_NT*)
        EXECUTABLE="./$EXECUTABLE_NAME.exe"
        if command -v ninja &>/dev/null; then
            cmake -G "Ninja" ..
        else
            cmake -G "Visual Studio 16 2019" ..
        fi
        ;;
    *)
        echo "Unsupported platform: $PLATFORM"
        exit 1
        ;;
esac

if [ -f "$EXECUTABLE" ]; then
    echo "$EXECUTABLE already exists, skipping build."
else
    if command -v ninja &>/dev/null; then
        ninja
    else
        make
    fi
fi

if [ -f "$EXECUTABLE" ]; then
    "$EXECUTABLE"
else
    exit 1
fi
