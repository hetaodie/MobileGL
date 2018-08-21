#!/bin/bash  

#dir define
PROJECTDIR=$(pwd)
echo $PROJECTDIR

SRCDIR=${PROJECTDIR}/
#cd ${SRCDIR}

PARENTFOLDER=$(dirname $SRCDIR)
echo $PARENTFOLDER
OUTPUTDIR=$PARENTFOLDER/framework
echo ${OUTPUTDIR}

#这里填入工程下 Targets 中所有的 framework 包名字，用空格分隔
frameworkNames=(RenderEngineKit)

for framework in ${frameworkNames[@]}

do

FMK_NAME=$framework

# Install dir will be the final output to the framework.

# The following line create it in the root folder of the current project.

INSTALL_DIR=${OUTPUTDIR}/${FMK_NAME}.framework

# Working dir will be deleted after the framework creation.

WRK_DIR=$PARENTFOLDER/lib

DEVICE_DIR=${WRK_DIR}/Release-iphoneos/${FMK_NAME}.framework

SIMULATOR_DIR=${WRK_DIR}/Release-iphonesimulator/${FMK_NAME}.framework

# -configuration ${CONFIGURATION}

# Clean and Building both architectures.
xcodebuild -configuration "Release" -target "${FMK_NAME}" -sdk iphoneos clean build
xcodebuild -configuration "Release" -target "${FMK_NAME}" -sdk iphonesimulator

# Cleaning the oldest.

if [ -d "${INSTALL_DIR}" ];then

rm -rf "${INSTALL_DIR}"

fi

mkdir -p "${INSTALL_DIR}"

cp -R "${DEVICE_DIR}/" "${INSTALL_DIR}/"

# Uses the Lipo Tool to merge both binary files (i386 + armv6/armv7) into one Universal final product.

lipo -create "${DEVICE_DIR}/${FMK_NAME}" "${SIMULATOR_DIR}/${FMK_NAME}" -output "${INSTALL_DIR}/${FMK_NAME}"

rm -rf "${WRK_DIR}"

#open "${INSTALL_DIR}"

done


