import Vue from 'vue'
import App from './App.vue'
import router from './router'
import store from './store'
import iView from 'iview';
import 'iview/dist/styles/iview.css';
import ECharts from 'vue-echarts'
import chartTheme from './components/charts_theme'
import VueKatex from 'vue-katex'
import 'katex/dist/katex.min.css';
ECharts.registerTheme(chartTheme);
Vue.config.productionTip = false
Vue.use(iView);
Vue.use(VueKatex);
// register component to use
new Vue({
  router,
  store,
  render: h => h(App)
}).$mount('#app')


Vue.component('v-chart', ECharts)
