#实验一：写一个hello world小程序
> 思路：跟着孟宁老师的网易云课堂回顾一下C编码，同时复习之前工作中使用的一些git操作。

###1、在github上创建仓库
首先在github上新建一个仓库，我这里是gaoruan。因此，我的git地址是：https://github.com/wsqat/gaoruan.git
![gaoruan.png](http://upload-images.jianshu.io/upload_images/688387-6a18960404122730.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
```
git clone https://github.com/wsqat/gaoruan.git
```
将远程新创建的git仓库gaoruan拉取到本地


###2、实现hello world

![vi.png](http://upload-images.jianshu.io/upload_images/688387-8308f6e072672148.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![vi hello.png](http://upload-images.jianshu.io/upload_images/688387-fb84ec65ab2a6175.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


![hello world.png](http://upload-images.jianshu.io/upload_images/688387-1ce1a676db2f283d.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

```
mkdir lab1
```
创建文件夹lab1

```
vi hello.c
```
编辑hello.c

```
gcc hello.c -o hello
```
编译hello
```
./hello
```
执行hello小程序
```
rm hello
```
删除hello

```
tar -zcvf wsqat_lab1.tar.gz ./*
```
当前下所有文件打包


###3、上传lab1到git
![push.png](http://upload-images.jianshu.io/upload_images/688387-d9f995b4959c4fad.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
```
git status
```
查看当前本地git库状态
```
git add .
```
把当前修改的文件add
```
git commit -m "xx"
```
添加注释
```
git push
```
提交到远程仓库

只是提示需要输入github的用户名和密码，输入即可
![log.png](http://upload-images.jianshu.io/upload_images/688387-b4aa76dd7c04449b.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

```
git log
```
查看本地提交记录

### 4、总结
加深自己对C语言编码的实践能力，同时对git指令进行复习和巩固。

