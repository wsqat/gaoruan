import Vue from 'vue'
import Router from 'vue-router'

Vue.use(Router)

import Index    from '@/pages/Index'



import ParentProps  from '@/pages/1-props/Parent.vue'
import ParentEmit   from '@/pages/2-emit/Parent.vue'
import Parent2Way   from '@/pages/3-2way/Parent.vue'
import ParentObj2Way   from '@/pages/3-obj2way/Parent.vue'
import BusDemo      from '@/pages/4-bus/Demo.vue'
import TodoDemo     from '@/pages/5-todo/index.vue'
import TodoVuex     from '@/pages/6-todo-vuex/index.vue'
import RestDemo     from '@/pages/7-rest-server/index.vue'
import ClientDemo   from '@/pages/8-rest-client/index.vue'
import DbDemo       from '@/pages/9-mongoose/index.vue'
import TodoDbDemo   from '@/pages/10-todo-db/index.vue'


import MapDemo      from '@/pages/11-google-map/index.vue'

import ShareFrame      from '@/pages/12-share-data/frame.vue'
import ShareSub1      from '@/pages/12-share-data/sub1.vue'
import ShareSub2      from '@/pages/12-share-data/sub2.vue'

import UploadDemo      from '@/pages/13-upload/index.vue'



export default new Router({
  mode:"history",
  routes: [
    { path: '/',            name: 'Index',          component: Index        },
    { path: '/props',       name: 'ParentProps',    component: ParentProps  },
    { path: '/emit',        name: 'ParentEmit',     component: ParentEmit   },
    { path: '/2way',        name: 'Parent2Way',     component: Parent2Way   },
    { path: '/obj2way',     name: 'ParentObj2Way',  component: ParentObj2Way },
    { path: '/bus',         name: 'BusDemo',        component: BusDemo      },
    { path: '/todo',        name: 'TodoDemo',       component: TodoDemo     },
    { path: '/todo-vuex',   name: 'TodoVuex',       component: TodoVuex     },
    { path: '/rest-server', name: 'RestDemo',       component: RestDemo     },
    { path: '/rest-client', name: 'ClientDemo',     component: ClientDemo   },
    { path: '/db',          name: 'DbDemo',         component: DbDemo       },
    { path: '/tododb',      name: 'TodoDbDemo',     component: TodoDbDemo   },
    { path: '/map',      name: 'MapDemo',        component: MapDemo   },

    { path: '/share',      name: 'Share',     component: ShareFrame, children:[
      {path: 'sub1',       component: ShareSub1},
      {path: 'sub2',       component: ShareSub1}

    ]  },

    { path: '/upload',      name: 'Upload',        component: UploadDemo   },

  ]

})
