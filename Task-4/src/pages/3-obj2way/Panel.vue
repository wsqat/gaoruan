<template>

  <div class="panel">

    <div class="panel-head">
      <input type="checkbox" v-model="my_penal.isshow">
      <span class="panel-head-title">{{title}}</span>
    </div>

    <div class="panel-body" v-show="my_penal.isshow">

      <input type="text" v-model="my_penal.name">
      <slot>

      </slot>
    </div>

  </div>

</template>

<script>
  export default {

    computed: {
      my_penal: {
        get() {
          return this.value;
        },
        set(val) {
          this.$emit('input', val);
        }
      }
    },
    props: ['title', 'value']
  }
</script>

<style scoped>

  .panel{
    background-color: yellow;
    width: 300px;
    float: left;
    margin-right: 50px;
  }

  .panel-head{
    height: 35px;
    width: 300px;
    float: left;
  }

  .panel-head input{
    width: 35px;
    height: 35px;
    line-height: 35px;
    float: left;
  }

  .panel-head .panel-head-title{
    float: left;
    line-height: 35px;
  }


</style>
