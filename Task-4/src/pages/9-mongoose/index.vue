<template>
  <div id="todo-app">
    <h1>  Demo 9: MongoDB 测试</h1>


    <div class="input-box">
      <h2>输入</h2>

      ID：<input type="text" v-model="id"><br />
      参数：<br />
      <textarea cols="40" rows="5" v-model="input"></textarea><br />

      <input type="button" @click="client.list()" value="List">
      <input type="button" @click="client.get(id)" value="Get">
      <input type="button" @click="client.add(JSON.parse(input))" value="Add">
      <input type="button" @click="client.modify(id, JSON.parse(input))" value="Moidfy">
      <input type="button" @click="client['delete'](id)" value="Delete"><br />
    </div>


    <div class="output-box">
      <h2>结果输出 </h2>

      状态：<input type="text" v-model="status"><br />
      输出：<br />
      <textarea cols="40" rows="10" v-model="output"></textarea>
    </div>


  </div>
</template>

<script>

  let client = require('./rest-client.js');

  export default {
    data(){
      return {
        id : 0,
        input : '',
        status : 0,
        output : '',
        client : client
      }
    },
    methods: {
        clear(){
          this.status = '';
          this.output = '';
        }
    },

    mounted(){

      let othis = this;
      client.ok = function (response) {
        othis.clear();
        othis.status = response.status;
        othis.output = JSON.stringify(response.data);
      };

      client.err = function (err) {
        othis.clear();
        othis.status = err.response.status;
        othis.output = JSON.stringify(err.response.data);
        console.log(err);
      };

    },

    watch:{
    }
  }
</script>

<style>

@import "./style.css";

  .input-box, .output-box{
    width: 350px;
    height: 350px;
    background-color: gainsboro;
    float: left;
    margin-left: 20px;
    padding-left: 20px;
  }

input[type=text], textarea{
  font-size: 14px;
}

.input-box input[type=button]{
  font-size: 14px;
  width: 60px;
}

</style>
