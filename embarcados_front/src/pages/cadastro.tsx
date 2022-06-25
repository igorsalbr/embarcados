import axios from "axios";
import { Dispatch, SetStateAction } from "react";
import NavBar from "../componentes/NavBar";

interface IProps {
    first: string;
    setFirst: Dispatch<SetStateAction<string>>;
  }

function cadas(){
   const object = {
    idTag:'',
    name: '',
    permission:'', 
    github: ''
    

   }

   object.idTag= document.querySelectorAll('input')[0].value
   object.name= document.querySelectorAll('input')[1].value
   object.permission= document.querySelectorAll('input')[2].value
   object.github= document.querySelectorAll('input')[3].value
   console.log(Object)
   return axios.post('http://localhost:3333/', object)
  .then(function (response) {
    console.log(response)
  })
  .catch(function (error) {
    console.error(error)
  })
}

export default function cadastro({first, setFirst}: IProps){

    return (
        <>
        <NavBar first={first} setFirst={setFirst}/>


        <div className="h-screen">

            <form id='form1' className="w-screen flex justify-center gap-4">
                <label className="flex-col" htmlFor="idtag">ID da tag
                <input className="bg-orange-300"  id="idtag"></input>
                </label>
                
                <label className="flex-col" htmlFor="name">Nome
                <input className="bg-orange-300" id="name"></input>
                </label>

                <label className="flex-col" htmlFor="permission">Permissão
                <input className="bg-orange-300"  id="permission"></input>
                </label>

                <label className="flex-col" htmlFor="github">Github
                <input className="bg-orange-300"  id="github"></input>
                </label>


            </form>
            <button onClick={cadas} className="border-b-2 rounded bottom-2 justify-center w-{300} h-{300} hover:bg-orange-600" type="submit" form="form1" value="Submit">Enviar</button>

        </div>
            
            </>
    )
}