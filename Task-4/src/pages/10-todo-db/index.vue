<template>
  <div id="todo-app">
    <h1> Demo 10: Todo List(With Database) </h1>

    <p class="note" >操作提醒:
      <br />* 新增：在输入框中输入内容，回车可新增
      <br />* 修改：单击条目可设置为完成；
      <br />* 删除：双击条目可删除；

      <br /> <br />
    </p>



    <input type="text" v-model="newItem" @keyup.enter="addItem">

    <ul>
      <li v-for="(item,index) in items"
          :class="{'cls-finished': item.isFinished}"
          @click="toggleFinish(item)"
          @dblclick="deleteItem(item)"
          :key="'item'+index" >
        {{ item.label }}
      </li>
    </ul>

  </div>
</template>

<script>
  import store from './vuex/store.js'

  export default {
    data(){
      return {
        newItem:""
      }
    },

   computed:{
      items:{
        get() {
          return store.getters.todoItems;
        }
      }
    },

    methods: {

      addItem(){
        store.dispatch("AddTodoItem", {label:this.newItem, isFinished:false});
        this.newItem  = "";
      },

      toggleFinish(item){
        store.dispatch("ToggleFinishedTodoItem", item);
      },

      deleteItem(item){
        store.dispatch("DeleteTodoItem", item._id);
      }
    },

    mounted(){
      store.dispatch("InitTodoItem");
    }
  }
</script>

<style rel="stylesheet/less" lang="less">

@import "./style.css";

  body{
    h1{

    }
  }

</style>
