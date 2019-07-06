<template>
    <div
            @keyup.enter="onSearchClick"
    >
        <Row type="flex" style="padding-top: 20px">
            <Col span="10" offset="6">
                <span style="font-size: 90px; font-weight: bold"><Icon type="ios-book"/> 搜书网 </span>
            </Col>
        </Row>
        <Row style="padding-top: 30px">
            <Col span="8" offset="6">
                <Input v-model="query_text"
                       @on-change="onSearchChange"
                       search size="large"
                       placeholder="输入要查询的公式 性质 习题..."
                       style="width: 100%" />
            </Col>
            <Col span="2" offset="1">
                <Button type="primary" style="width: 100%" size="large" shape="circle" icon="ios-search"
                        @click="onSearchClick"
                >搜索一下</Button>
            </Col>
        </Row>
        <Row style="padding-top: 10px">
            公式预览:

            <div v-for="l,index in this.latex">
                公式 {{ index }}:
                <span v-katex="l" style="background-color: #dcdee2; font-size: 30px"></span>
            </div>
        </Row>
        <Row style="padding-top: 30px">
            <RadioGroup v-model="query_type" style="width: 100%" >
                <Col span="3"  offset="4">
                    <Radio label="text" class="query-type-option">
                        <Icon type="md-text"></Icon>
                        <span>文本</span>
                    </Radio>
                </Col>
                <Col span="3">
                    <Radio label="nature" class="query-type-option">
                        <Icon type="md-barcode" />
                        <span>性质</span>
                    </Radio>
                </Col>
                <Col span="3">
                    <Radio label="concept" class="query-type-option">
                        <Icon type="md-easel" />
                        <span>概念</span>
                    </Radio>
                </Col>
                <Col span="3">
                    <Radio label="example" class="query-type-option">
                        <Icon type="md-help-circle" />
                        <span>例题</span>
                    </Radio>
                </Col>
                <Col span="3">
                    <Radio label="excries" class="query-type-option">
                        <Icon type="md-help-circle" />
                        <span>习题</span>
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
                query_type: 'text',
                latex: []

            }
        },
        methods:{
            onSearchChange: function(text){
                let res = this.query_text.match(new RegExp(String.raw`\$(.*?)\$`, 'g'))
                if (res) {
                    this.latex = res.map((item)=>{
                        return item.replace(new RegExp(String.raw`\$`, 'g'),'')

                    })
                }

            },
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