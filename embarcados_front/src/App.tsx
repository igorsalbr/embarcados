import { useState } from 'react'
import {Routes,  BrowserRouter, Route} from 'react-router-dom'
import Home from './pages'
import Cadastro from './pages/cadastro'

function App() {
  const [first, setFirst] = useState<string>('Home')

  return (
    
    <BrowserRouter>
        <Routes location={location} key={location.pathname}>
          <Route path="/" element={<Home first={first} setFirst={setFirst}  />}/>
          <Route path="/cadastro" element={<Cadastro first={first} setFirst={setFirst}/>}/>
        </Routes>
        </BrowserRouter>
  )
}

export default App
