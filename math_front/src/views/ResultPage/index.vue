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
            <Row style="padding-top: 15px" v-for="item in results" :key="'res'  + item.id">
                <span> {{ item.title }}</span>
                <div> {{ item.content }}</div>
            </Row>
        </Card>
    </div>
</template>

<script>
    export default {
        name: "ResultPage",
        data: function () {
            return {
                query_text: '',
                query_type: undefined,
                results: [{
                    id: 1,
                    title: '测试',
                    content: '测试内容'
                },
                    {
                        id: 2,
                        title: '测试2',
                        content: '测试内容2'
                    }]
            }
        },
        methods: {
            onSearchClick: function () {
                this.$router.push({
                    name: 'result',
                    query: {
                        query_text: this.query_text,
                        query_type: this.query_type
                    }
                })
            }
        },
        mounted: function () {

        }
    }
</script>

<style scoped>
    .query-type-option{
        font-size: 12px;
    }
</style>