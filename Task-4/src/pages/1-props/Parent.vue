<template>

  <div class="grey-box">

   <h1>父组件（灰色背景）</h1>


    <input type="text" v-model="msg" >


    <Child :message="msg"></Child>

  </div>

</template>

<script>

  import Child from "./Child.vue";

  export default {
    data(){
      return {
        msg : "改变会发送给子组件"
      }
    },
    components: {Child}
  }
</script>
