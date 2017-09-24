<template>

  <div>

    <h2>夯实Vue系列Demo 目录:</h2>

    <ol>
      <li>父->子 组件通讯：props <router-link to="props" >点击进入</router-link>
      <li>子 >父-组件通讯：Emit  <router-link to="emit" >点击进入</router-link>
      <li>双向绑定-组件通讯：v-model <router-link to="/2way">点击进入</router-link> <br />
        对象绑定-组件通讯：v-model <router-link to="/obj2way">点击进入</router-link>
      </li>
      <li>普通组件通讯：Global Bus <router-link to="/bus">点击进入</router-link></li>
      <li>一个简单的Todo List： <router-link to="/todo">点击进入</router-link></li>
      <li>基于Vuex的Todo List： <router-link to="/todo-vuex">点击进入</router-link></li>
      <li>RESTful服务器： <router-link to="/rest-server">点击进入</router-link></li>
      <li>RESTful客户端： <router-link to="/rest-client">点击进入</router-link></li>
      <li>MongoDB数据库： <router-link to="/db">点击进入</router-link></li>
      <li>TodoList(数据库)： <router-link to="/tododb">点击进入</router-link></li>
      <li>外部组件的使用 Google Map： <router-link to="/map">点击进入</router-link></li>
      <li>页面间贡献数据： <router-link to="/share/sub1">点击进入</router-link></li>

      <li>上传控件的使用： <router-link to="/upload">点击进入</router-link></li>
    </ol>

  </div>
</template>


<style>

  .grey-box{
    background-color: gainsboro;
    height: 400px;
  }

  .grey-box input{
    width: 300px;
    height: 35px;
    line-height: 35px;
    font-size: 18px;
  }

  .yellow-box{
    width: 500px;
    margin-left: 80px;
    margin-top: 30px;
    background-color: yellow;
    height: 100px;
  }


</style>
