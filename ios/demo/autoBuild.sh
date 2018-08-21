#!/bin/bash  
#!/bin/sh

function buildOtherSh() {
    echo $1
    echo $2
    cd $1
    $2
    echo "funcition"
    pwd
    cd $3
}

echo "****************start to Build Avatar**********"
sleep 1
buildOtherSh "../sdk/RenderEngineKit" ./autoBuild.sh "../../demo"
echo "****************build Avatar end**********"
sleep 1

####################################################################
#
#echo "******************cp libs to tmp **************************"
rm -rf ./libs/RenderEngineKit.framework
cp -R ../sdk/framework/* ./libs
















