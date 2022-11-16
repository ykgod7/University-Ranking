<template>
    <div v-if="loading"> Loading... </div>
    <body v-else>
        <div class="container list-text" style="width: 1100px; background-color: white;">
        <!-- 첫번째 줄 -->
            <div class="d-flex align-items-center row gx-3" style="height: 170px; justify-content: space-between;">
                <!-- 학교 이름 -->
                <div class="col-6 h-100 mt-5">
                    <div class="p-3 h-100 d-flex nameDiv">
                        <div class="col-3 m-1 d-flex align-items-center" style="line-height: 130px;">
                            <img :src="require(`../assets/logo/${uni.name}.png`)" class="center" style="height: 85px; width: 85px">
                        </div>
                        <div class="col list-text" style="">
                            <div style="padding-top: 20px">{{ uni.name }}</div>
                            <div class="eng-name" style=";padding-bottom: 20px">{{ uni.engName }}</div>
                        </div>
                    </div>
                </div>
            </div>

        <!-- 두번째 줄 -->
        <div class="d-flex year-rank" style="font-size: 20px; width: 260px; margin-top: 100px;">
            <i class="fa fa-crown m-2" style="margin-top: -1px"></i>
            <span style="padding: 5px 0">2022 국내 대학 순위 # {{ uni.rank }}</span>
        </div>

        <!-- 세번째 줄 -->
        <div class="d-flex mt-2 div-container" style="height: 360px; background-color: white;">
            <div class="container m-2 box1" >
                <div class="rankChart" style="margin-top: 10px;">
                    <button @click="graph_source = 'THE'" :class="[graph_source === 'THE' ? 'source-btn the-btn btn-clicked' : 'source-btn the-btn']">THE</button>
                    <button @click="graph_source = 'QS'" :class="[graph_source === 'QS' ? 'source-btn qs-btn btn-clicked' : 'source-btn qs-btn']">QS</button>
                    <span style="text-decoration: underline 2px; margin-left: 20px;">순위 그래프</span>
                </div>
                <RankChart :graph_source="graph_source" :key="graph_source" />
            </div>
            <div class="container m-2 box1">
                <div style="font-size:25px; width: 100px; margin: auto; margin-top: 10px;"><span style="text-decoration: underline 2px">학교 소개</span></div>
                <div class=" overflow-auto container p-font" style="font-size: 18px; font-weight: 400; height: 280px; color: #666; padding: 10px">
                    {{ uni.intro }}
                    <br /> <br />
                    <div class="citation">출처 : <span><a :href="uni.citation" class="citation">{{ uni.citation }}</a></span></div>
                </div>
            </div>
        </div>

        <!-- 네번째 줄 -->
        <div class="d-flex mt-5 justify-content-around rounded p-font" style="height: 300px; background-color: white">
            <div class="text-center circle detail-data" style="background-color: #0C2D48; width: 200px; height: 200px">
                <div class="mydiv">    
                    <div class="circle" style="box-shadow: none; line-height: 40px;">
                        <img src="../assets/multi.png">
                    </div>
                    <div class="mt-2" style="font-size: 21px">경쟁률</div>
                    <div class="">{{ uni.compRate }}</div>
                </div>
            </div>

            <div class="text-center circle detail-data" style="background-color: #0C2D48; width: 200px; height: 200px">
                <div class="mydiv">
                    <div class="circle" style="box-shadow: none; line-height: 40px;">
                        <img src="../assets/teacher.png">
                    </div>
                    <div class="mt-2" style="font-size: 21px">학생 교수 비율</div>
                    <div>{{ uni.SFRatio }}</div>
                </div>
            </div>

            <div class="text-center circle detail-data" style="background-color: #0C2D48; width: 200px; height: 200px">
                <div class="mydiv">
                    <div class="circle" style="box-shadow: none; line-height: 40px;">
                        <img src="../assets/student.png">
                    </div>
                    <div class="mt-2" style="font-size: 21px">총 학생수</div>
                    <div>{{ uni.TotStud }} 명</div>
                </div>
            </div>

            <div class="text-center circle detail-data" style="background-color: #0C2D48; width: 200px; height: 200px">
                <div class="mydiv" style="height: 142px;">
                    <div class="circle container" style="box-shadow: none; line-height: 40px;">
                        <img src="../assets/money.png">
                    </div>
                    <div class="mt-2" style="font-size: 21px">학비</div>
                    <div style="font-size: 25px">{{ uni.tuition }} 원</div>
                </div>
            </div>
        </div>

        <!-- 다섯번째 줄 -->
        <div class="mt-5 container" style="width: 900px;">
            <div>
                <img src="../assets/ranking_64.png" style="max-width: 40px; max-height: 40px;">학과별 순위
                <button :class="[subject_source === 'THE' ? 'source-btn the-btn btn-clicked' : 'source-btn the-btn']" @click="subject_source = 'THE'" autofocus>THE</button>
                <button :class="[subject_source === 'QS' ? 'source-btn qs-btn btn-clicked' : 'source-btn qs-btn']" @click="subject_source = 'QS'">QS</button>
            </div>
            <table class="table table-striped" style="font-size: 22px;">
                <thead class="" style="background-color: #0C2D48; color: white">
                    <tr style="font-size: 24px">
                        <th scope="col" class="col-5">학과</th>
                        <th scope="col" class="col-5">순위</th>
                    </tr>
                </thead>
                <tbody v-if="subject_source === 'THE'" style="max-height: 300px">   
                    <tr v-for="(rank, subject) in the_data" :key="subject">
                        <td>{{ subject }}</td>
                        <td>{{ rank }}</td>
                    </tr>
                </tbody>
                <tbody v-else style="max-height: 300px">
                    <tr v-for="(rank, subject) in qs_data" :key="subject">
                        <td>{{ subject }}</td>
                        <td>{{ rank }}</td>
                    </tr>
                </tbody>
            </table>
        </div>

        <!-- 여섯번째 줄 -->
        <div class="rounded mt-5" style="font-size: 20px; background-color: #dbebf0">
            <div class="m-2">학교 홈페이지 : <a v-bind:href="uni.website">{{ uni.website }}</a></div>
        </div>
        <br />
        </div>
    </body>
</template>
    


<script>
import axios from 'axios'
import { useRoute } from 'vue-router'
import { ref } from '@vue/reactivity'
import RankChart from '../components/RankChart.vue'


export default {
    name: 'InfoPage',
    components: {
        RankChart,
    },

    setup() {
        const route = useRoute()
        const uni = ref(null)
        const loading = ref(true)
        const subject_source = ref('THE')
        const graph_source = ref('THE')
        const qs_data = ref()  // 학과별 순위 데이터
        const the_data = ref()  // 학과별 순위 데이터
        
        const getUniveristy = async () => {
            const res = await axios.get('http://localhost:5000/universities?name=' + route.params.name)
            uni.value = res.data[0]
            qs_data.value = res.data[0].source.QS["2022"].subject   // 최신 연도로 바꿔야함
            the_data.value = res.data[0].source.THE["2022"].subject
            loading.value = false
        }

        getUniveristy()

        
        return {
            uni,
            loading,
            subject_source,
            qs_data,
            the_data,
            graph_source,
            
        }
    },
}
</script>

<style scoped>
body {
    margin-top: 60px;
}

.nameDiv {
    /* background: #0C2D48; */
    background: linear-gradient(310deg, rgba(177,212,224,1) 0%, rgba(255,255,255,1) 100%);
    box-shadow: rgba(0, 0, 0, 0.35) 0px 5px 15px;
    border-radius: 10px;
}
.fa-crown {
    color:#ffd700;
    left: 0;
}

.eng-name {
    font-size: 18px;
    font-weight: 300;
    color: gray;
}

.list-text {
    font-family: 'Do Hyeon', sans-serif;
    font-weight: bold;
    font-size: 35px;
    color: black;
}

.center {
    display: block;
    margin-left: auto;
    margin-right: auto;


}

.table td {
    text-align: center;   
    vertical-align: middle;
}

.table th {
    text-align: center;  
    vertical-align: middle; 
}

tr {
    line-height: 30px;
}

.rankChart {
    font-size: 25px;
    width: 100%;
    margin: auto;
    /* text-align: center; */
}

.circle {
    border-radius: 50%;
    background-color: #e9f0fb;
    width: 50px;
    height: 50px;
    margin: auto;
    box-shadow: rgba(0, 0, 0, 0.3) 0px 19px 38px, rgba(0, 0, 0, 0.22) 0px 15px 12px;
    color: white;
}

.mydiv {
    position: relative;
    top: 50%;
    transform: translateY(-50%);
}

.p-font {
    font-family: 'Noto Sans KR', sans-serif;
    font-weight: strong;
}

.table-striped > tbody > tr:nth-child(2n+1) > td, .table-striped > tbody > tr:nth-child(2n+1) > th {
    background-color: #B1D4E0;
}

.year-rank {
    border-top: 2px solid #B1D4E0;
    border-bottom: 2px solid #B1D4E0;
}

.box1 {
    background: radial-gradient(circle, rgba(255,255,255,1) 0%, rgba(177,212,224,1) 100%);
    border-radius: 10px;
    box-shadow: rgba(50, 50, 93, 0.25) 0px 6px 12px -2px, rgba(0, 0, 0, 0.3) 0px 3px 7px -3px;
}

.detail-data {
    transition: transform .2s ease;
}

.detail-data:hover {
    transform: scale(1.1);
}

tbody {
    display: block;
    overflow: overlay;
}

thead, tbody tr {
    display: table;
    width: 100%;
    table-layout: fixed;
}

::-webkit-scrollbar {
    width: 8px;
    height: 50px;
    overflow: auto;
    float: left;
    margin: 0 10px;
}

::-webkit-scrollbar-track {
    background: #edf5f8;
    border-radius: 10px;
}

::-webkit-scrollbar-thumb {
    background: #326c81;
    border-radius: 10px; 
}

::-webkit-scrollbar-thumb:hover {
  cursor: pointer;
}

.table {
    outline-style: solid;
    outline-width: 2px;
    outline-color: #0C2D48;
}

.citation {
    font-size: 15px;
}


.source-btn {
  align-items: center;
  appearance: none;
  background-color: #fff;
  border-radius: 24px;
  border-style: none;
  box-shadow: rgba(0, 0, 0, .2) 0 3px 5px -1px,rgba(0, 0, 0, .14) 0 6px 10px 0,rgba(0, 0, 0, .12) 0 1px 18px 0;
  box-sizing: border-box;
  color: #3c4043;
  cursor: pointer;
  display: inline-flex;
  fill: currentcolor;
  font-family: "Google Sans",Roboto,Arial,sans-serif;
  font-size: 14px;
  font-weight: 500;
  height: 48px;
  justify-content: center;
  letter-spacing: .25px;
  line-height: normal;
  max-width: 100%;
  overflow: visible;
  padding: 2px 24px;
  position: relative;
  text-align: center;
  text-transform: none;
  transition: box-shadow 280ms cubic-bezier(.4, 0, .2, 1),opacity 15ms linear 30ms,transform 270ms cubic-bezier(0, 0, .2, 1) 0ms;
  user-select: none;
  -webkit-user-select: none;
  touch-action: manipulation;
  width: auto;
  will-change: transform,opacity;
  z-index: 0;
  margin: 5px;
  bottom: 7px;
  width: 80px;
}

.source-btn:hover {
  opacity: 0.8;
  color: #174ea6;
}   

.source-btn:active {
  box-shadow: 0 4px 4px 0 rgb(60 64 67 / 30%), 0 8px 12px 6px rgb(60 64 67 / 15%);
  outline: none;
}


.btn-clicked  {
    outline: none;
    border: 2px solid #52527a;
}

.source-btn:not(:disabled) {
  box-shadow: rgba(60, 64, 67, .3) 0 1px 3px 0, rgba(60, 64, 67, .15) 0 4px 8px 3px;
}

.source-btn:not(:disabled):hover {
  box-shadow: rgba(60, 64, 67, .3) 0 2px 3px 0, rgba(60, 64, 67, .15) 0 6px 10px 4px;
}

.source-btn:not(:disabled):focus {
  box-shadow: rgba(60, 64, 67, .3) 0 1px 3px 0, rgba(60, 64, 67, .15) 0 4px 8px 3px;
}

.source-btn:not(:disabled):active {
  box-shadow: rgba(60, 64, 67, .3) 0 4px 4px 0, rgba(60, 64, 67, .15) 0 8px 12px 6px;
}

.source-btn:disabled {
  box-shadow: rgba(60, 64, 67, .3) 0 1px 3px 0, rgba(60, 64, 67, .15) 0 4px 8px 3px;
}

.qs-btn {
    background: linear-gradient(310deg, rgba(255,255,220,1) 0%, rgba(218,218,218,1) 100%);
}

.the-btn {
    background: linear-gradient(310deg, rgba(220,225,255,1) 0%, rgba(255,201,201,1) 100%);
}
</style>