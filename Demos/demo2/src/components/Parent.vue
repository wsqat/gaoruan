<template>
  <div class="grey-box">

    <h1> 父组件(灰色背景)</h1>

    <div>
      子组件传来的值为： {{emitData}}
    </div>

    <Child @emitMessage="receiveFun"></Child>
  </div>

</template>

<script>

  import Child from "./Child.vue";

  export default {
    data(){
      return {
        emitData: ""
      }
    },
    methods: {
      receiveFun(message){
        this.emitData = message;
      }
    },
    components: {Child}
  }
</script>
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