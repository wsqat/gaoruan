<template>
  <div id="todo-app">
    <h1> Google Map </h1>

    <div class="map">
      <gmap-map
        :center="center"
        :zoom="12"
        map-type-id="terrain"
        style="width: 400px; height: 800px"
      >


        <gmap-marker
          :key="index"
          v-for="(m, index) in markers"
          :position="m.position"
          :clickable="true"
          :draggable="false"
          @click="center=m.position">


        </gmap-marker>

      </gmap-map>
    </div>

  </div>
</template>

<script>



  export default {
    data(){
      return {
        center:  {lat: 49.2241079, lng: -123.0055918},
        markers: [
            { position: {lat: 49.24,  lng: -123.01}},
            { position: {lat: 49.21,  lng: -123.0}},
            { position: {lat: 49.2,  lng: -123.02}},
            { position: {lat: 49.145,  lng: -123.02}},
            { position: {lat: 49.28,  lng: -123.05}},
            { position: {lat: 49.23, lng: -122.95}}
        ]
      }
    },

    methods: {


    },

    mounted(){

    }
  }
</script>

<style>

</style>
