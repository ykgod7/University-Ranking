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
  props: {
    source: {
      type: String
    }
  },
  setup(props) {
    onMounted(() => {
      
      getData(props.source)
    })
    
    const route = useRoute()
    const uni = ref(null)
    const years = ref([])
    const ranks = ref([])
    const max = ref(0)
    const getData = async (source) => {
      const res = await axios.get(`http://localhost:5000/universities?source=${source}&name=` + route.params.name + `&_sort=year`)
      uni.value = res.data
      for (let i = 0; i < uni.value.length; i++) {
        years.value.push(uni.value[i].year)
        ranks.value.push(uni.value[i].rank)
        if (max.value <  uni.value[i].rank) {
          max.value = uni.value[i].rank
        }
      }
    }


    const testData = {
      labels: years.value,
      datasets: [
        {
          data: ranks.value,
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

    return { testData, options };
  },
});
</script>