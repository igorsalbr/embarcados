import { useState } from 'react'
import {Routes,  BrowserRouter, Route} from 'react-router-dom'
import Home from './pages/home'
import Cadastro from './pages/cadastro'

function App() {
  const [first, setFirst] = useState<string>(location.href.split('/')[3].replace('?',''))

  return (
    
    <BrowserRouter>
        <Routes location={location} key={location.pathname}>
          <Route path="/home" element={<Home first={first} setFirst={setFirst}  />}/>
          <Route path="/cadastro" element={<Cadastro first={first} setFirst={setFirst}/>}/>
        </Routes>
        </BrowserRouter>
  )
}

export default App
