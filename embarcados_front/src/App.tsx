import { useEffect, useState } from 'react'
import {Routes,  BrowserRouter, Route} from 'react-router-dom'
import Home from './pages/home'
import Cadastro from './pages/cadastro'
import axios from 'axios'

function App() {
  const [first, setFirst] = useState<string>(location.href.split('/')[3].replace('?',''))
  const [entry, setEntry] = useState<{id:string, id_tag:string, name: string, permission: string, github_link:string, active:boolean}|''>('')
  setInterval(()=>{
    axios.get<{activeTags: [{id:string, id_tag:string, name: string, permission: string, github_link:string, active:boolean}]}>(' https://project-rfid-embarcados.herokuapp.com/active').then(function (response) {
    console.log(response.data.activeTags[0])  
    setEntry(response.data.activeTags[0]||'')
  
    })
  }
  ,10000)
  /**useEffect(()=>{axios.get<{activeTags: [{id:string, id_tag:string, name: string, permission: string, github_link:string, active:boolean}]}>(' https://project-rfid-embarcados.herokuapp.com/active').then(function (response) {
    console.log(response.data.activeTags[0])  
    setEntry(response.data.activeTags[0]||'')})},[])*/
  
  return (
    
    <BrowserRouter>
        <Routes location={location} key={location.pathname}>
          <Route path="/home" element={<Home entry={entry}  first={first} setFirst={setFirst}  />}/>
          <Route path="/cadastro" element={<Cadastro first={first} setFirst={setFirst}/>}/>
        </Routes>
        </BrowserRouter>
  )
}

export default App
