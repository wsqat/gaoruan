<template>

  <div class="yellow-box">

   <h2> 子组件(黄色背景)</h2>

    <div>
      传来的值为： {{message}}
    </div>


  </div>

</template>

<script>


  export default {
    props:['message']
  }
</script>
