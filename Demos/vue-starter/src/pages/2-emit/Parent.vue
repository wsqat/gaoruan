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

