import axios from 'axios'

export const  querySearch = (query_text, query_type) => {
    return axios.post('/api/search', {
        'query_text':query_type,
        'query_type':query_type
    })
}

export const  getKeyWords = (query_text, query_type) => {
    return axios.get('/api/getKeyWord', {
        'query_text':query_type,
        'query_type':query_type
    })
}