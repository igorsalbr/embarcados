import React from "react";
import axios, { AxiosResponse } from "axios";
import { Dispatch, SetStateAction, useEffect, useState } from "react";
import NavBar from "../componentes/NavBar";

interface IProps {
    first: string;
    setFirst: Dispatch<SetStateAction<string>>;
  }


async function funcaoTeste(a:{"\"id_tag\"": string; "\"name\"": string; "\"permission\"": string; "\"github_link\"": string; "\"active\"":boolean}) {
    try {
        const user = await axios.post('https://project-rfid-embarcados.herokuapp.com/', 
       a
        )
        console.log(user.data)
    } catch(error) {
        console.log(error)
    }
}

export default function cadastro({first, setFirst}: IProps){
    const [req, setReq]= useState<boolean>(false)
        
    const [data, setData ] = useState(false)
    useEffect(()=>{
        if (data){
            console.log('tamo aq ne')
            const a = {"\"id_tag\"": document.querySelectorAll('input')[0].value, "\"name\"": document.querySelectorAll('input')[1].value, "\"permission\"": document.querySelectorAll('input')[2].value, "\"github_link\"": document.querySelectorAll('input')[3].value, "\"active\"": false}
            funcaoTeste(a)


    }else{console.log('darafalse')}
    setData(false)    
    console.log('vishh')
    },[data])
    
    return (
        <>
        <NavBar first={first} setFirst={setFirst}/>


        <div className="h-screen">
           <div className="w-3/4 mx-auto aspect-video">
            <form id='form1' className=" mt-10 grid grid-cols-4 gap-6 w-full shadow-inner border rounded p-5">
                <label className="col-start-1 col-end-3" htmlFor="idtag">ID da tag
                <input className="bg-orange-300 ml-1 justify-end"  id="idtag"></input>
                </label>
                
                <label className="col-start-3 col-end-5" htmlFor="name">Nome
                <input className="bg-orange-300 ml-1 justify-end" id="name"></input>
                </label>

                <label className="col-start-1 col-end-3" htmlFor="permission">Permissão
                <input className="bg-orange-300 ml-1 justify-end"  id="permission"></input>
                </label>

                <label className="col-start-3 col-end-5" htmlFor="github">Github
                <input className="bg-orange-300 ml-1 justify-end"  id="github"></input>
                </label>
                <button onClick={()=>setData(true)} className="border-b-2 mt-4 rounded col-start-1 col-span-full flex justify-center w-{300} h-{300} bg-orange-600 opacity-60 hover:opacity-100" type="submit" form="form1" value="Submit">Enviar</button>


            </form>
            <div></div>
        
            </div>
        </div>
            
            </>
    )
}