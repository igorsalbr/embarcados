const axios = require('axios')

export async function funcaoTeste() {
    try {
        const user = await axios.post('http://localhost:3333/', {
            "id_tag":5,
            "name":"teste axios",
            "permission":"all",
            "github_link":"lala"
        })
        console.log(user.data)
    } catch(error) {
        console.log(error.response)
    }
}

funcaoTeste()