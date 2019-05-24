<template>
    <div>
        <Card>
            <Row type="flex" style="padding-top: 20px">
                <Col span="5" offset="1">
                    <span style="font-size: 30px; font-weight: bold"><Icon type="ios-book"/> 搜书网 </span>
                </Col>
                <Col span="8" offset="1">
                    <Input v-model="query_text" search size="large" placeholder="输入要查询的公式 性质 习题..." style="width: 100%"/>
                </Col>
                <Col span="2" offset="1">
                    <Button type="primary" style="width: 100%" size="large" shape="circle" icon="ios-search" @click="onSearchClick">搜索一下</Button>
                </Col>
            </Row>
            <Row style="padding-top: 5px">
                <RadioGroup v-model="query_type" style="width: 100%" >
                    <Col span="3" offset="6">
                        <Radio value="formulation" label="formulation" class="query-type-option">
                            <Icon type="logo-apple"></Icon>
                            <span>公式</span>
                        </Radio>
                    </Col>
                    <Col span="3">
                        <Radio label="android" class="query-type-option">
                            <Icon type="logo-android"></Icon>
                            <span>文本</span>
                        </Radio>
                    </Col>
                    <Col span="3">
                        <Radio label="windows" class="query-type-option">
                            <Icon type="logo-windows"></Icon>
                            <span>性质</span>
                        </Radio>
                    </Col>
                </RadioGroup>
            </Row>
        </Card>
            <div style="padding-top: 30px"></div>
        <Card>
            <Row style="padding-top: 15px"
                 v-for="item, index in results"
                 :key="item.chapter + index"
                 >
                <div @click="onResultClick(item)">
                    <span style="color: #1a0dab">{{ item.chapter }}</span>
                </div>
                <div>
                   <span v-for="abc in item.abstract" v-html="highLight(abc)"></span> ...
                </div>
            </Row>
        </Card>
        <Detail
                :visible="show_detail"
                :result="select_result"
                :query_text="query_text"
                @onClose="show_detail=false"
        ></Detail>
    </div>
</template>

<script>
    import {querySearch,getKeyWords} from '@/service/api'
    import Detail from './components/detail'
    export default {
        name: "ResultPage",
        components:{Detail},
        data: function () {
            return {
                key_words: [],
                query_text: '',
                query_type: undefined,
                results: [],
                select_result : {},
                show_detail: false
            }
        },
        methods: {
            highLight: function(text){
                let replaceReg = new RegExp(this.query_text, 'g');
                // 高亮替换v-html值
                let replaceString = '<span class="search-text" style="color: darkred;">' + this.query_text + '</span>';
                // 开始替换
                return text.replace(replaceReg, replaceString);
            },
            onSearchClick: function () {
                this.$router.push({
                    name: 'result',
                    query: {
                        query_text: this.query_text,
                        query_type: this.query_type
                    }
                })
            },
            onResultClick: function (item) {
                this.select_result = item
                this.show_detail = true
            }
        },

        created: function () {
            this.query_text = this.$route.query.query_text
            this.query_type = this.$route.query.query_type
                querySearch('', '').then((resp)=>{
                    this.results = resp.data.data
                })
        }
    }
</script>

<style scoped>
    .query-type-option{
        font-size: 12px;
    }
    .search-text{

    }
</style>