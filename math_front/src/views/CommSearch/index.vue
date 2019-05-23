<template>
    <div>
        <Row type="flex" style="padding-top: 20px">
            <Col span="10" offset="6">
                <span style="font-size: 90px; font-weight: bold"><Icon type="ios-book"/> 搜书网 </span>
            </Col>
        </Row>
        <Row style="padding-top: 30px">
            <Col span="8" offset="6">
                <Input v-model="query_text" search size="large" placeholder="输入要查询的公式 性质 习题..." style="width: 100%"/>
            </Col>
            <Col span="2" offset="1">
                <Button type="primary" style="width: 100%" size="large" shape="circle" icon="ios-search" @click="onSearchClick">搜索一下</Button>
            </Col>
        </Row>
        <Row style="padding-top: 10px" v-show="query_type === 'formulation'">
            公式预览:
            <div>
                <span v-katex="query_text" style="background-color: #dcdee2; font-size: 30px"></span>
            </div>
        </Row>
        <Row style="padding-top: 30px">
            <RadioGroup v-model="query_type" style="width: 100%" >
                <Col span="3" offset="6">
                    <Radio label="formulation" class="query-type-option">
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
    </div>
</template>

<script>
    export default {
        name: "CommSearch",
        data: function () {
            return {
                query_text: '',
                query_type: 'formulation'
            }
        },
        methods:{
            onSearchClick: function () {
                this.$router.push({
                    name: 'result',
                    query: {
                        query_text: this.query_text,
                        query_type: this.query_type
                    }
                })
            }
        }
    }
</script>

<style scoped>
.query-type-option{
    font-size: 20px;
}
</style>