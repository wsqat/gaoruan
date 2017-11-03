<template>

  <div>


    <ComA></ComA>

    <ComB></ComB>

  </div>

</template>

<script>

  import bus from './bus.js';

  import ComA from './ComA.vue';
  import ComB from './ComB.vue';

  export default {
      components:{ComA, ComB}
  }

</script>

<style>

  h1,h2{
    display: block;
    height: 50px;
    padding-top: 20px;
  }

  .context-box-b,  .context-box-a{
    background-color: gainsboro;
    height: 200px;

    margin-left: 30px;
    width: 300px;
    float: left;
  }

  .context-box-a{
    background-color: yellow;
  }
</style>
