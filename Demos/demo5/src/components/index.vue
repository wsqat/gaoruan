<template>
  <div id="todo-app">
    <h1 v-text="title"></h1>

    <p class="note" >操作提醒:
      <br />* 新增：在输入框中输入内容，回车可新增
      <br />* 修改：单击条目可设置为完成；
      <br />* 删除：双击条目可删除；
      <br /> <br />
    </p>

    <input type="text" v-model="newItem" v-on:keyup.enter="addItem" id="search">

    <ul>
      <li v-for="(item,index) in items" 
          v-bind:class="{'cls-finished': item.isFinished}"
          :key="'item_'+index"
          @click="toggleFinish(item)"  @dblclick="deleteItem(item)">
        {{ item.label }}
      </li>
    </ul>

  </div>
</template>

<script>
  import DataStore from './DataStore.js'


  Array.prototype.remove = function(val) {
    var index = this.indexOf(val);
    if (index > -1) {
      this.splice(index, 1);
    }
  };

  export default {
    data(){
      return {
        title:"一个简单的Todo List",
        items:  DataStore.fetch(),
        newItem:""
      }
    },
    methods: {
      toggleFinish(item){
        item.isFinished = !item.isFinished;
      },
      addItem(){
        this.items.push({label:this.newItem, isFinished:false});
        this.newItem  = "";
      },

      deleteItem(item){
        this.items.remove(item);
      }
    }, 
    watch:{
      items : {
        handler: function (items) {
          DataStore.save(items);
        },
        deep: true
      }
    } 
  }
</script>

<style>

@import "./style.css";

</style>
