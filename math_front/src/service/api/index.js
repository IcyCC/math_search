import axios from 'axios'

export const  querySearch = (query_text, query_type) => {
    return axios.post('/api/search', {
        'query_text':query_text,
        'query_type':query_type
    })
}

export const  getKeyWords = (query_text, query_type) => {
    return axios.get('/api/getKeyWord')
}

export const  segmentWords = (text) => {
    return axios.post('/api/segmentWords', {
       'text': text
    })
}

export const  getGexf = (text) => {
    return axios.get('/api/static/book.gexf')
}

export const  getBookIndex = (text) => {
    return axios.get('/api/getBookIndex')
}

export const  getBookPage = (page) => {
    return axios.get(`/api//bookPage/${page}`)
}