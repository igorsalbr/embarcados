import axios from "axios";
import  {Dispatch, SetStateAction, useState} from "react";
import NavBar from "../componentes/NavBar";

interface IProps {
    first: string;
    setFirst: Dispatch<SetStateAction<string>>;
  }
export default function Home({first, setFirst}: IProps){
  const [entry, setEntry] = useState()
  axios.get('http://localhost:3333/5').then(function (response) {
    setEntry(response.data)

  })

  return(<>
  
  <NavBar first={first} setFirst={setFirst}/>
  <h1>{entry}</h1>
  
  </>)

}
