<template>
  <div id="todo-app">
    <h1> Demo: Cart List(With Database) </h1>

    <p class="note" >操作提醒：此页面为购物车的列表页面
    <br />* 新增：点击进入<a href="./form" style="text-decoration:none;color:blue">新增</a>页面
    <br />* 修改：单击条目可设置此商品为已购买；
    <br />* 删除：双击条目移除此商品；
    <br /><br />
    </p>

    <!-- <input type="text" v-model="newItem" @keyup.enter="addItem"> -->

    <!-- <ul>
      <li></li>
      <li v-for="(item,index) in items"
          :class="{'cls-finished': item.isFinished}"
          @click="toggleFinish(item)"
          @dblclick="deleteItem(item)"
          :key="'item'+index" >
        {{ item.label }}
      </li>
    </ul> -->

    <table class="bordered" cellspacing="0" border="0" width="660px">  
      <thead>
        <th>商品名称</th><th>商品单价</th><th>商品数目</th>
      </thead>
      <tbody id="tbody_$commonName$">
        <tr v-for="(item,index) in items" :class="{'cls-finished': item.isFinished}"
          @click="toggleFinish(item)"
          @dblclick="deleteItem(item)"
          :key="'item'+index" >
          <td>{{item.label}}</td><td>{{item.price}}</td><td>{{item.number}}</td>
        </tr>
      </tbody>
      
    </table>

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
        store.dispatch("AddCartItem", {label:this.newItem,price:"63",number:"1", isFinished:false, });
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
