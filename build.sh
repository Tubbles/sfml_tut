#!/bin/bash

set -e

my_dir="$(dirname "$(realpath "$0")")"
target_dir="$my_dir/target"
app_name="$(grep -E '^project(.+)' CMakeLists.txt | sed -E 's/project\((.+)\)/\1/g')"

implicit_build=true
build=false
clean=false
format=false
run=false
verbose=false
extra_verbose=false
target="debug"
target_dir_target="$target_dir/debug"

usage="Usage: $0 [options]
where [options] can be zero or more of:
  ?,h,help,--help    display this help text and exit
  v,verbose          run more verbosely
  extra-verbose      run with all verbose text
  debug,release      build for debug (default) or release target
  clean              clean everything, does not build implicitly
  build              build, implicitly selected
  format             format all source code, does not build implicitly
  run                run the application after a successful build, forces build
  --                 pass the following args to the program, if running"

while (($#)); do
case $1 in
    \?|h|help|--help)
        echo "$usage"
        exit 0
        ;;
    v|verbose)
        verbose=true
        ;;
    extra-verbose)
        verbose=true
        extra_verbose=true
        set -x
        ;;
    debug)
        target="debug" || $run == true
        target_dir_target="$target_dir/debug"
        ;;
    release)
        target="release"
        target_dir_target="$target_dir/release"
        ;;
    clean)
        clean=true
        implicit_build=false
        ;;
    build)
        build=true
        ;;
    format)
        format=true
        implicit_build=false
        ;;
    run)
        build=true
        run=true
        ;;
    --)
        shift
        break
        ;;
    *)
        echo "Unknown argument: \"$1\""
        echo "$usage"
        exit 1
        ;;
esac
shift
done

cmake_debug=""
if [[ $target == "debug" ]]; then
    cmake_debug="-DCMAKE_BUILD_TYPE=Debug"
elif [[ $target == "release" ]]; then
    cmake_debug="-DCMAKE_BUILD_TYPE=Release"
fi

ninja_verbose=""
if [[ $verbose == true ]]; then
    ninja_verbose="-v"
fi

cmake_verbose=""
if [[ $extra_verbose == true ]]; then
    cmake_files=$(find "$my_dir" \( -name CMakeLists.txt -or -name '*.cmake' \) -not -path '*/modules/*/*' -not -path '*/target/*' | paste -sd' ')
    cmake_verbose="--trace-expand "
    for file in $cmake_files; do
        cmake_verbose+="--trace-source=$file "
    done
fi

if [[ $implicit_build == true ]]; then
    build=true
fi

clang-format --style=file -i "$my_dir/src/"*.{cpp,hpp}

if [[ $clean == true ]]; then
    rm -fr "$target_dir"
    rm -fr "$my_dir/compile_commands.json"
fi

if [[ $build == true ]]; then
    mkdir -p "$target_dir_target"
    cmake $cmake_verbose -S "$my_dir" -B "$target_dir_target" -G Ninja $cmake_debug
    cmake --build "$target_dir_target" -- $ninja_verbose
    if [[ $run == true ]]; then
        "$target_dir_target/$app_name" "$@"
    fi
fi
