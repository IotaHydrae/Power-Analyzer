#!/bin/bash

mkdir -p build

lv_i18n -v > /dev/null
if [ $? -eq "0" ]; then
	echo "build i18n source files."
	lv_i18n compile -t 'translations/*.yml' -o  'src/lv_i18n' -l 'zh-CN'
else
	echo  '"lv_i18n" is not found, skip i18n build'
fi

pushd build > /dev/null
echo "build mcu firmware..."
cmake .. -G Ninja
ninja
popd > /dev/null
