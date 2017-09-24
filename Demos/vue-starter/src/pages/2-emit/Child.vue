<template>

  <div class="yellow-box">

   <h2> 子组件(黄色背景)</h2>

    <input type="text" v-model="message">

    <button @click="send"> 发送 </button>

  </div>

</template>

<script>
  export default {

    data(){
        return {
            message:""
        }
    },
    methods:{
      send(){
        this.$emit('emitMessage', this.message);
      }
    }
  }
</script>
