#!/bin/sh

mv *.sh  *.md ../

rm ./* -r

mkdir proj.win32
cp /e/StudySource/cocos2d-x/cocos_create_Src/Graduation/proj.win32/*.h  ./proj.win32
cp /e/StudySource/cocos2d-x/cocos_create_Src/Graduation/proj.win32/*.cpp  ./proj.win32
cp -r /e/StudySource/cocos2d-x/cocos_create_Src/Graduation/Classes  ./ 

mkdir res
cp -r /e/StudySource/cocos2d-x/cocos_create_Src/Graduation/proj.win32/Debug.win32/Resources ./res

mv ../*.sh ../*.md ./


