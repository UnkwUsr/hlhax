#!/bin/bash


if ! [ -n "$1" ]; then
    echo "Please write argument. Using: $0 [d]{load,unload,reload} ('d' is for debug)"
    exit 1
fi
if ! @CMAKE_MAKE_PROGRAM@; then
    echo "make error."
    exit 2
fi

pid=$(pidof hl_linux)
if ! [ -n "$pid" ]; then
    echo "Process not exist."
    exit 3
fi

libpath=$(realpath ./libhlhack.so)
#how its work: if we call lldb with '--batch', then lldb will exit after done script, else they dont exit, and just wait user(what we need for debug)
do_batch="--batch"
do_restore_on_crash="-u 1 --"
for param in "$@"
do
    if [ ${param:0:1} = "d" ]; then
        do_batch=""
        do_restore_on_crash="-u 0 --"

        param=${param:1}
    fi
    case $param in
    load)
        if grep -q $libpath /proc/$pid/maps; then
            echo "Already loaded."
            exit 4
        fi
        sudo lldb $do_batch --attach-pid $pid \
            --one-line "exp $do_restore_on_crash auto \$handle = (void*)dlopen(\"$libpath\", 0x00002)" \
            --one-line 'p (char*)dlerror()'
        echo "Loaded!"
        ;;
    unload)
        if ! grep -q $libpath /proc/$pid/maps; then
            echo "Can not unload until not loaded first."
            exit 5
        fi
        sudo lldb $do_batch --attach-pid $pid \
            --one-line "exp  auto \$handle = (void*(*)(char*, int)) dlopen(\"$libpath\", 6)" \
            --one-line "exp (int(*)(void*)) dlclose(\$handle)" \
            --one-line "exp $do_restore_on_crash (int(*)(void*)) dlclose(\$handle)"
        echo "UnLoaded!"
        ;;
    reload)
        if grep -q $libpath /proc/$pid/maps; then
            sudo lldb $do_batch --attach-pid $pid \
                --one-line "exp auto \$handle = (void*(*)(char*, int)) dlopen(\"$libpath\", 6)" \
                --one-line "exp (int(*)(void*)) dlclose(\$handle)" \
                --one-line "exp (int(*)(void*)) dlclose(\$handle)" \
                --one-line "exp (void*)dlopen(\"$libpath\", 0x00002)" \
                --one-line 'p (char*)dlerror()'
        else
            sudo lldb $do_batch --attach-pid $pid \
                --one-line "exp (void*)dlopen(\"$libpath\", 0x00002)" \
                --one-line 'p (char*)dlerror()'
        fi
        echo "ReLoaded!"
        ;;
    "")
        echo "Starting debugger"
        sudo lldb $do_batch --attach-pid $pid
        ;;
    *)
        echo "$1 is not an option"
        exit 6
        ;;
    esac
done

