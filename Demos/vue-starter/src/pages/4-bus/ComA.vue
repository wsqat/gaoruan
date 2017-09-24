<template>

  <div class="context-box-a">
   <h2>组件A</h2>

    <input type="text" v-model="message">
    <button @click="send"> 发送 </button>
  </div>

</template>

<script>

  import bus from './bus.js';

  export default {

    data(){
        return {message:""}
    },

    methods:{
      send(){
        bus.$emit('event-name', this.message);
      }
    }
  }
</script>
