<template>
  <div id="todo-app">
    <h1> 子页面 Sub1</h1>


    <p> 利用router view，数据是否会重复获取？ </p>
    <button  @click="showData"> 显示数据 </button>

    <div>跳转到： <a href="/share/sub2">点击进入 Sub2</a></div>
  </div>
</template>

<script>
  import store from './vuex/store.js'

  export default {

    methods: {

      showData(){
        console.log("load result=", store.getters.todoItems);
      }
    }

  }
</script>
