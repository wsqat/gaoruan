<template>
  <div id="todo-app">
    <h1> Demo 10: Cart List(With Database) </h1>

    <p class="note" >操作提醒:
      <br />* 新增：在输入框中输入商品，回车可添加到购物车
      <br />* 修改：单击条目可设置此商品为已购买；
      <br />* 删除：双击条目可删除此商品；
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
          return store.getters.cartItems;
        }
      }
    },

    methods: {

      addItem(){
        store.dispatch("AddCartItem", {label:this.newItem,price:"3",number:"1", isFinished:false, });
        this.newItem  = "";
      },

      toggleFinish(item){
        store.dispatch("ToggleFinishedCartItem", item);
      },

      deleteItem(item){
        store.dispatch("DeleteCartItem", item._id);
      }
    },

    mounted(){
      store.dispatch("InitCartItem");
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
