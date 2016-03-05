#!/bin/bash
cat Geom.h main.cpp | sed '/#include "*"/d' > toSend.cpp
