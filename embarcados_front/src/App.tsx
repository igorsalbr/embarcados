import { useEffect, useState } from 'react'
import {Routes,  BrowserRouter, Route} from 'react-router-dom'
import Home from './pages/home'
import Cadastro from './pages/cadastro'
import axios from 'axios'
import Cadastro2 from './pages/cadastro2'

function App() {
  const [first, setFirst] = useState<string>(location.href.split('/')[3].replace('?',''))
  const [entry, setEntry] = useState<{id:string, id_tag:string, name: string, permission: string, github_link:string, active:boolean}|''>('')
  




  /**useEffect(()=>{axios.get<{activeTags: [{id:string, id_tag:string, name: string, permission: string, github_link:string, active:boolean}]}>(' https://project-rfid-embarcados.herokuapp.com/active').then(function (response) {
    console.log(response.data.activeTags[0])  
    setEntry(response.data.activeTags[0]||'')})},[])*/
  
  return (
    
    <BrowserRouter>
        <Routes location={location} key={location.pathname}>
          <Route path="/home" element={<Home setEntry={setEntry} entry={entry}  first={first} setFirst={setFirst}  />}/>
          <Route path="/cadastro" element={<Cadastro2  first={first} setFirst={setFirst}/>}/>
          <Route path="/cadastro2" element={<Cadastro  first={first} setFirst={setFirst}/>}/>
        </Routes>
        </BrowserRouter>
  )
}

export default App
