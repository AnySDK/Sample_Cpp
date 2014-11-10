DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
NDK_ROOT=/Users/daisy/Documents/software/anysdk/adt-bundle-mac-x86_64/android-ndk-r9d
$NDK_ROOT/ndk-build -C $DIR \
"NDK_MODULE_PATH=$DIR"
