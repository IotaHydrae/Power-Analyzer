# Power Anylzer

## 构建
更新子模块
```bash
git submodule update --init
```
编译MCU固件
```bash
cd software
mkdir build && cd build
cmake .. -G Ninja
ninja

openocd -f interface/cmsis-dap.cfg -f target/rp2040.cfg -s tcl -c "adapter speed 5000" -c "program src/rp2040-freertos-template.elf verify reset exit"
```

## UI 开发

### 编辑工程
打开 EEZ-Studio 后，选择Open project, 打开本工程ui文件夹下`.eez-project`后缀工程文件。

### 生成UI文件

点击软件左上角工具栏中的`扳手`按钮，所需的ui文件将导出到`Power-Anylzer/ui/src/ui`下，
此目录通过软链接引用于software工程中。

### 文本翻译
本工程lvgl多语言基于[lv_i18n](https://github.com/lvgl/lv_i18n)开发
`software/transations`文件夹下存放有相关的翻译文件，修改翻译文件后，需要执行
```
cd software
lv_i18n compile -t 'translations/*.yml' -o  'src/lv_i18n' -l 'zh-CN'
```
