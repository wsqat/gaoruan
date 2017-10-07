# gaoruan
## 高软课程实验代码
### 第一周作业
  1、lab1/: 此目录下是C语言编写的hello word的程序，[点击查看实验报告](https://www.shiyanlou.com/courses/reports/1290122)  。  
  2、todos/: 此目录下是
  使用vuejs完成的ToDoList   
  
#### vuejs安装指南
    #前面是指令, #后面是注释
-  brew install node 
#Mac安装node指令，其他大家百度哈，先安装node
-  npm -v #检查是否安装成功npm
-  npm install -g cnpm --registry=https://registry.npm.taobao.org #换淘宝源
-  cnpm -v #检查cnpm
-  sudo cnpm install -g vue-cli #安装vue
-  vue init webpack my-first-vue-project #初始化项目；回车；描述；作者；No；No；No；No
-  cd my-first-vue-project
-  sudo cnpm install #安装依赖
-  npm run dev #运行

### 第二周作业
  1、lab2/: 此目录下是C语言编写的菜单小程序, [点击查看实验报告](https://github.com/wsqat/gaoruan/tree/master/lab2)    
  2、Demos/: 此目录下是使用Vuejs完成的Demos  
-   vue-starter/: 此为夯实Vue系列Demo   
-   demo1/: 父->子 组件通讯：props  
-   demo2/: 子 >父-组件通讯：Emit    
-   demo3/: 2way 双向绑定-组件通讯：v-model, obj2way 双向绑定-组件通讯: v-model   
-   demo4/: 普通组件通讯：Global Bus
-   demo5/: 一个简单的Todo List
-   demo6/: 基于Vuex的Todo List

#### Demos安装指南
    以vue-starter为例(其他几个demo类似)使用如下命令，即可运行vue-starter所展示的Demos
-  git clone https://github.com/wsqat/gaoruan.git
-  cd gaoruan/Demos/vue-starter
-  cnpm install
-  npm run dev

### 第三周作业
  1、lab3/: 此目录下是C语言改写的模块化小程序, [点击查看实验报告](https://github.com/wsqat/gaoruan/tree/master/lab3)   
  2、Vue背后如何实现的双向数据绑定？  
*  数据劫持的方法：[Object.defineProperty方法(属性拦截器)](http://blog.csdn.net/u011277123/article/details/58597638)  
* 1.[理解vue实现原理，实现一个简单的Vue框架](https://github.com/fwing1987/MyVue)
* 2.[Vue源代码](https://github.com/vuejs/vue) - [便于跟踪vue源代码的例子](https://coding.net/u/mengning/p/mengning/git/raw/master/ase/vue-example.zip)
* 目标3：通过跟踪vue源代码来说明vue是如何实现数据双向绑定的？将1理解透彻合格，将2理解透彻优秀。应在10月09日完成
* [相关博客](https://zhuanlan.zhihu.com/p/24435564)

### 第四周作业
  lab4/: 此目录下是C语言改写的模块化小程序, [点击查看实验报告](https://github.com/wsqat/gaoruan/tree/master/lab4)   