import React from "react";
import axios, { AxiosResponse } from "axios";
import { Dispatch, SetStateAction, useEffect, useState } from "react";
import NavBar from "../componentes/NavBar";

interface IProps {
    first: string;
    setFirst: Dispatch<SetStateAction<string>>;
  }


async function funcaoTeste(a:{"id_tag": number; "name": string; "permission": string; "github_link": string;}) {
    try {
        const user = await axios.post('http://localhost:3333/', 
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
            const a = {"id_tag": parseInt(document.querySelectorAll('input')[0].value), "name": document.querySelectorAll('input')[1].value, "permission": document.querySelectorAll('input')[2].value, "github_link": document.querySelectorAll('input')[3].value}
            funcaoTeste(a)


    }else{console.log('darafalse')}
    setData(false)    
    console.log('vishh')
    },[data])
    
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
            <button onClick={()=>setData(true)} className="border-b-2 rounded bottom-2 justify-center w-{300} h-{300} hover:bg-orange-600" type="submit" form="form1" value="Submit">Enviar</button>
            <div></div>
        </div>
            
            </>
    )
}