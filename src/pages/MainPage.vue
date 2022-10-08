<template>
<div class="container align-items-center" style="width: 1100px">
    <!-- 타이틀 & 로고 -->
    <div style="margin-bottom: 70px">
        <div id="titleDiv" class="d-flex align-items-center justify-content-center" style="height: 230px;">
            <div>
                <div id="title" style="">Top University Ranking</div>
                <div class="eng-name auth">
                    본 웹사이트는 QS World University Rankings (QS)와 Times Higher Education (THE)에 나와 있는 자료를 기반으로 제작되었습니다
                    

                </div>
            </div>
            <div>
                <img src="../assets/logo.png" alt="Responsive image" style="max-width: 250px; margin-left: 1em;border-radius: 100%">
            </div>
        </div>
    </div>

    <!-- <KeepFilter @filter-list="FilterList" /> -->
<!-- Filters -->
    <div class="d-flex justify-content-center ">
        <form class="row  wrapper  w-100">
            <!-- Source Selector -->
            <div class="btn-group col-4" style="height: 48px">
                <button type="button" :class="[source ==='THE'? 'btn-the w-50 rounded-3 currentSource' : 'btn-the w-50 rounded-3 beforeClicked']" @click="getData(year, 'THE')">
                    <span class="btn-gradient">
                        <i class="fa fa-graduation-cap" style="font-size: 0.8em;"></i>
                    </span>
                    <span class="btn-text">THE</span>
                </button>

                <button type="button" :class="[source ==='QS'? 'btn-qs w-50 rounded-3 currentSource' : 'btn-qs w-50 rounded-3 beforeClicked']" @click="getData(year, 'QS')">
                    <span class="btn-gradient" style="background-color: #b35900">
                        <i class="fa fa-graduation-cap" style="font-size: 0.8em;"></i>
                    </span>
                    <span class="btn-text">QS</span>
                </button>
            </div>

            <!-- Year Filter -->
            <div class="col-2">
                <select class="btn-lg w-100 dropdown-toggle border border-secondary rounded-3 korean-font" style="font-size: 20px; height: 48px"
                v-model="year" @change="getData(year, source)">
                    <option value="2021" selected="selected">2021</option>
                    <option value="2022">2022</option>
                </select>
            </div>
            
            <!-- Name Filter -->
            <div class="col-md-4">
                <div class="input-group border border-secondary rounded-3" style="height: 48px;">
                    <input 
                    onkeydown="return (event.keyCode!=13);"
                    type="search" 
                    placeholder="University Name" 
                    aria-describedby="button-addon3" 
                    class="form-control bg-none border-0 remove-x korean-font" 
                    style="font-size: 20px"
                    v-model="searchUniversity"
                    >
                    <div class="input-group-append border-0">
                        <button id="button-addon3" type="button" class="btn btn-link text-success">
                        <i class="fa fa-search align-middle"></i>
                        </button>
                    </div>
                </div>
            </div>

            <!-- Subject Filter -->
            <div class="col-2">
                <select 
                class="btn-lg w-100 dropdown-toggle border border-secondary rounded-3 korean-font" 
                style="font-size: 20px; height: 48px"
                v-model="selectedSubject"
                @change="changeList(year)"
                >
                    <option value="Subject">Subject</option>
                    <!-- eslint-disable-next-line -->
                    <option v-for="(rank, subject, index) in subjects" :key="subject" :value="subject">{{ subject }}</option>
                </select>
            </div>
        </form>
    </div>

    <!-- 대학교 리스트 -->
    <div class="d-flex justify-content-center">
        <div class="w-100" style="margin-bottom: 3em;">
            <div class="card m-2">
                <div class="card-body d-flex text-light bg-opacity-25 card-top rounded" style="height: 50px">
                    <div class="m-2 col-1 align-self-center text-center">Rank</div>
                    <div class="m-2 col-2 align-self-center text-center">University Name</div>
                    <div class="m-4 col align-self-center"></div>
                    <div class="m-2 col-2 align-self-center text-center">Competition Rate</div>
                </div>
            </div>

            <div v-for="(university, idx) in filteredUniversity" :key="university.id" class="card m-2" style="height: 100px; border-color: #bfbfbf">
                <div 
                @click="DetailPage(university.name)"
                class="card-body h-100 my-div">
                    <div class="d-flex h-100 align-items-center list-text">
                        <div v-if="subjectState" class="col-1">
                            <div class="m-2 align-self-center text-center idx"> {{ idx + 1 }}</div>
                        </div>
                        <div v-else class="col-1">
                            <div class="m-2 align-self-center text-center idx">{{ university.rank }}</div>
                        </div>
                        <div class="m-2 col-2 h-100 text-center text-center">
                            <img :src="require(`../assets/logo/${university.name}.png`)" class="h-100 mx-auto">
                        </div>
                        <div class="m-4 col">
                            <div class="text-left align-middle">{{ university.name }}</div>
                            <div class="eng-name">{{ university.engName }}</div>
                        </div>
                        <div class="m-2 col-2 align-self-center text-center" style="font-weight: 400">{{ university.compRate }}</div> 
                    </div>
                </div>
            </div>
            
            
        </div>
    </div>
</div>

</template>

<script>

import { ref, onMounted, computed, onBeforeUnmount, getCurrentInstance } from 'vue'
import { useRoute, useRouter } from 'vue-router'
import axios from 'axios'


export default {
    name: 'MainPage',
    components: {
    },
    data(){
        return {
        }

    },
    mounted() {
    },

    setup() {
        onMounted(() => {
            console.log('new')
            loadFilter()
            getData(proxy.filters[1], proxy.filters[0])
        })

        onBeforeUnmount(() => {
            replaceValue(source.value, 0)
            replaceValue(year.value, 1)
            replaceValue(selectedSubject.value, 2)
        })

        const { proxy } = getCurrentInstance()
        const replaceValue = (val, idx) => {
            proxy.filters[idx] = val
        }
        const loadFilter = () => {
            source.value = proxy.filters[0]
            year.value = proxy.filters[1]
            selectedSubject.value = proxy.filters[2]
        }

        const router = useRouter()
        const year = ref('2021')
        const universities = ref([])
        const subjects = ref([])
        const source = ref('THE')

// Load Data
        const getData = async (year, e) => {
            const res = await axios.get(`http://localhost:5000/universities?year=${year}&source=${e}&_sort=rank`)
            source.value = e
            universities.value = res.data
            subjects.value = res.data[0].subject
            selectedSubject.value = proxy.filters[2]
        }

// University Name Filter
        const searchUniversity = ref('')
        const filteredUniversity = computed(() => {
            if (searchUniversity.value) {
                return universities.value.filter(university => {
                    return university.name.includes(searchUniversity.value)
                })
            }
            return universities.value
        })

// University Subject filter
        const selectedSubject = ref('Subject')
        const subjectState = ref(false)
        const changeList = async (year) => {
            if (selectedSubject.value === 'Subject') {
                const res = await axios.get(`http://localhost:5000/universities?year=${year}&source=${source.value}&_sort=rank`)
                universities.value = res.data
                subjectState.value = false
                proxy.filters[2] = 'Subject'
            } else {
            const res = await axios.get(`http://localhost:5000/universities?year=${year}&subject.${selectedSubject.value}_gte=1&_sort=subject.${selectedSubject.value}&source=${source.value}`)
            universities.value = res.data
            subjectState.value = true
            proxy.filters[2] = selectedSubject.value
            }
            return  universities.value
        }

// Move to Detail Page
        const DetailPage = (name) => {
            router.push({
                name: 'Info',
                params: {
                    name: name
                }
            })
        }

// 할일 :  대학교 리스트 상단 꾸미기

        return {
            year,
            universities,
            getData,
            subjects,
            searchUniversity,
            filteredUniversity,
            selectedSubject,
            changeList,
            DetailPage,
            // FilterList,
            source,
            subjectState,
            replaceValue
            
        }
    },
}
</script>



<style scoped>
#titleDiv {
    margin-top: 150px;
}

#title {
    font-family: 'Bebas Neue', cursive;
    font-size: 80px;
}

.dropdown-toggle::after{
    content: none;
}

.korean-font {
/* font-family: 'Jeju Myeongjo', serif; */
/* font-family: 'Nanum Gothic', sans-serif; */
/* font-family: 'Noto Sans KR', sans-serif; */
font-family: 'Noto Serif KR', serif;
font-weight: 600;
}

.wrapper {
    font-family: 'Barlow Condensed', cursive;
    font-size: 20px;
}

.formDiv {
    height: 100px;
}

.btn-qs {
    font-size:24px;
    font-weight: bold;
    padding:0px 20px;
    color: rgb(14, 13, 13);
    background-color: #ffcc99;
    border:none;
    justify-content: center;
    align-items: center;
    display: flex;
}

.btn-the {
    font-size:24px;
    font-weight: bold;
    padding:0px 20px;
    color: rgb(14, 13, 13);
    background-color: #d7d9da;
    border: none;
    justify-content: center;
    align-items: center;
    display: flex;
}

.btn-gradient {    
    width:40%;
    position: relative;
    display: inline-block;
    left:-20px;
    background: #7694bc;
    border-top-right-radius: 60px;
    padding: 7px 24px 5px 10px;
    box-shadow: 2px 0px 0px 0px rgba(78, 72, 72, 0.4);
}

.btn-text{
    width:60%;
}

input, input:focus, input:hover, input:active {
    outline: none;
    box-shadow:none;
}

input[type="search"]::-webkit-search-decoration,
input[type="search"]::-webkit-search-cancel-button,
input[type="search"]::-webkit-search-results-button,
input[type="search"]::-webkit-search-results-decoration {
    -webkit-appearance:none;
}

.card-top {
    background: #333333;
    font-family: 'Bebas Neue', cursive;
    font-size: 20px;
}

.list-text {
font-family: 'Do Hyeon', sans-serif;
/* font-family: 'Nanum Gothic', sans-serif; */
/* font-family: 'Nanum Gothic Coding', monospace; */
/* font-family: 'Noto Sans KR', sans-serif; */
/* font-family: 'Noto Serif KR', serif;  */
    font-weight: bold;
    font-size: 25px;
}

.my-div {
    cursor: pointer;
}

.eng-name {
    font-size: 18px;
    font-weight: 300;
    color: gray;
}

.auth {
    font-family: 'Do Hyeon', sans-serif;
/* font-family: 'Nanum Gothic', sans-serif; */
/* font-family: 'Nanum Gothic Coding', monospace; */
/* font-family: 'Noto Sans KR', sans-serif; */
/* font-family: 'Noto Serif KR', serif;  */
    font-weight: 550;
    font-size: 18px;
    width: 500px;
    float: right;
    color: #a6a6a6;
}

.currentSource {
    box-shadow: rgba(50, 50, 93, 0.25) 0px 30px 60px -12px inset, rgba(0, 0, 0, 0.3) 0px 18px 36px -18px inset;
    filter: brightness(80%)
}

.beforeClicked {
    box-shadow: rgba(0, 0, 0, 0.07) 0px 1px 1px, rgba(0, 0, 0, 0.07) 0px 2px 2px, rgba(0, 0, 0, 0.07) 0px 4px 4px, rgba(0, 0, 0, 0.07) 0px 8px 8px, rgba(0, 0, 0, 0.07) 0px 16px 16px;
}
</style>