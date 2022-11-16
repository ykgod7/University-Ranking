<template>
  <div>
    <LineChart :chartData="testData" :width="300" :height="300" :options=options />
  </div>
</template>

<script>
import { defineComponent, onMounted, defineProps } from 'vue';
import { LineChart } from 'vue-chart-3';
import { Chart, registerables } from "chart.js";
import axios from 'axios'
import { useRoute } from 'vue-router'
import { ref, reactive } from '@vue/reactivity'

Chart.register(...registerables);

export default defineComponent({
  name: 'RankChart',
  components: { LineChart },
  props: ['graph_source'],
  setup(props) {
    onMounted(() => {
      getData()
    })
    
    const route = useRoute()
    const years = ref([])
    const ranks = ref([])
    const max = ref(0)
    const qs_data = ref()   // 그래프 데이터
    const qs_rank = ref([])
    const the_data = ref()
    const the_rank = ref([])


    
    const getData = async () => {
      const res = await axios.get(`http://localhost:5000/universities?name=` + route.params.name)
      qs_data.value = res.data[0].source.QS
      the_data.value = res.data[0].source.THE

      for (let i = 0; i < Object.keys(qs_data.value).length; i++) {
        years.value.push(Object.keys(qs_data.value)[i])  // 연도 데이터 [2020, 2021, 2022]
        qs_rank.value.push(qs_data.value[Object.keys(qs_data.value)[i]].rank)
        the_rank.value.push(the_data.value[Object.keys(the_data.value)[i]].rank)

        // if (max.value <  uni.value[i].rank) {
        //   max.value = uni.value[i].rank
        // }
      }
    }


    const testData = {
      labels: years.value,
      datasets: [
        {
          data: (props.graph_source == 'THE') ? the_rank.value : qs_rank.value,
          backgroundColor: ['#00cc44'],
          borderColor: ['#0d0d0d'],
          borderWidth: 1
        },
      ],
    };

    const options = {
      plugins: {
        legend: {
          display: false,
        },
      },
      scales: {
        y: {
          reverse: true,
          // min: 1,
          // max: max.value + 5,
          ticks: {
            stepSize: 1
          }
        }
      }
    };

    return { 
      testData, 
      options
 
    };
  },
});
</script>