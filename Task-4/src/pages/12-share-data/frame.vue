<template>
  <div id="todo-app">
    <h1> Demo 12: 数据间在Vuex间共享 </h1>


    <button  @click="showData"> 显示数据 </button>


    <router-view></router-view>

  </div>
</template>

<script>
  import store from './vuex/store.js'

  export default {

    methods: {

      showData(){
        console.log("load result=", store.getters.todoItems);
      }

    },

    mounted(){
      store.dispatch("InitTodoItem").then(function(res) {
            console.log("load result=", res);
        });
    }
  }
</script>

<style rel="stylesheet/less" lang="less">
@import "./style.css";
</style>
