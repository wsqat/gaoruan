<template>

  <div class="context-box-b">

   <h1> 组件 B</h1>

    {{show}}

  </div>

</template>

<script>

  import bus from './bus.js';

  export default {
    data(){
        return {'show' : 0}
    },

    mounted(){
      var that = this;
      bus.$on('event-name', function (msg) {
        that.show = msg;
      });

    }
  }
</script>
