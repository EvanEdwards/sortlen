#!/bin/bash

if [ "$1" == "-r" ]
then
  shift
  [ "$1" == "--" ] && shift
  awk '{ print length, $0 }' "$@" | sort -nrs | cut -d" " -f2-
else
  [ "$1" == "--" ] && shift
  awk '{ print length, $0 }' "$@" | sort -ns | cut -d" " -f2-
fi


