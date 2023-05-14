#!/bin/bash
PROJECT_BASE=$(eval "pwd")
echo "Preparing in: $PROJECT_BASE"

LD_LIBRARY_PATH=$PROJECT_BASE/dist/lib
export LD_LIBRARY_PATH

$PROJECT_BASE/dist/bin/QtHttpServerUi