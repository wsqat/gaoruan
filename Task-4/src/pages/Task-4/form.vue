<template>
  <div id="todo-app">
    <h1> Demo: Cart List(With Database) </h1>

    <p class="note" >操作提醒：此页面为购物车的列表页面
      <br />* 新增：在输入框中输入商品的名称，单价，数量，点击提交按钮，跳转到购物车列表页面
      <br /> <br />
    </p>

    <form class="bootstrap-frm">
      <label>
        <span>商品名称 :</span>
        <!-- <input id="name" type="text" name="name" placeholder="Your Full Name" /> -->
        <input type="text" v-model="newItem" placeholder="Good Name">
      </label>
      
      <label>
        <span>商品单价 :</span>
        <!-- <input id="name" type="text" name="name" placeholder="Your Full Name" /> -->
        <input type="text" v-model="price" placeholder="Good Price">
      </label>

      <label>
        <span>商品数目 :</span>
        <!-- <input id="name" type="text" name="name" placeholder="Your Full Name" /> -->
        <input type="text" v-model="number" placeholder="Good number">
      </label>
      <span>&nbsp;</span>
      <input type="button" class="button" value="Send" @click="addItem"/>
      <!-- <button @click="addItem"></button> -->
    </form>
    <!-- <ul>
      <li v-for="(item,index) in items"
          :class="{'cls-finished': item.isFinished}"
          @click="toggleFinish(item)"
          @dblclick="deleteItem(item)"
          :key="'item'+index" >
        {{ item.label }}
      </li>
    </ul> -->


  </div>
</template>

<script>
import store from './vuex/store.js'

export default {
  data(){
    return {
      newItem:"",
      price:"",
      number:""
    }
  },

  computed:{
    items:{
      get() {
        return store.getters.cartItems;
      }
    }
  },

  methods: {

    addItem(){
      store.dispatch("AddCartItem", {label:this.newItem,price:this.price,number:this.number, isFinished:false, });
      this.newItem  = "";
      self.location="./";
    }
  },
}
</script>

<style rel="stylesheet/less" lang="less">

@import "./style.css";

body{
  h1{

  }
}

</style>
