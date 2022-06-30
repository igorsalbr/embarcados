import React, { useRef } from "react";
import axios, { AxiosResponse } from "axios";
import { Dispatch, SetStateAction, useEffect, useState } from "react";
import NavBar from "../componentes/NavBar";
import { useRequest } from "../hooks/use-request2.hook";

// interface IProps {

//     first: string;
//     setFirst: Dispatch<SetStateAction<string>>;
//   }



export default function cadastro2({ first, setFirst}){
    
    const [req, setReq]= useState(false)
        
    const [data, setData ] = useState()
//     function postCadastro(){
//             console.log('tamo aq ne')
//             const a = {"\"id_tag\"":${document.querySelectorAll('input')[0].value}, "\"name\"":document.querySelectorAll('input')[1].value, "\"permission\"":document.querySelectorAll('input')[2].value, "\"github_link\"":document.querySelectorAll('input')[3].value, "\"active\"": false}
//             console.log(a)
//             axios.post('https://project-rfid-embarcados.herokuapp.com/', 
//         a, 
//    ).then(res=> setData(res)).catch(e=>console.log(e))  
        
//     }

    
    const {data: data2, request,errorCode}  = useRequest({route: '/', method: 'post'})

    console.log('errorCode', errorCode);

    // const a = {"\"id_tag\"":${document.querySelectorAll('input')[0].value}, "\"name\"":${document.querySelectorAll('input')[1].value}, "\"permission\"":${document.querySelectorAll('input')[2].value}, "\"github_link\"":${document.querySelectorAll('input')[3].value}, "\"active\"": false}
    
   

    const handleClick = () => {

       
    }

    const handleSubmit = (e) => {
        e.preventDefault();
         const body = {
            id_tag: document.querySelectorAll('input')[0].value,
            name: document.querySelectorAll('input')[1].value,
            permission: document.querySelectorAll('input')[2].value,
            github_link: document.querySelectorAll('input')[3].value,
            active: false
        }

        console.log(body)
        request({bodyData: body, withCredentials: false});
        console.log('hello');


    }
 
    return (
        <>
        <NavBar first={first} setFirst={setFirst}/>

        <div onClick={handleClick}>Clicar</div>


        <div className="h-screen">
           <div className="w-3/4 mx-auto aspect-video">
            <form onSubmit={handleSubmit} id='form1' className=" mt-10 grid grid-cols-4 gap-6 w-full shadow-inner border rounded p-5">
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
                <button  className="border-b-2 mt-4 rounded col-start-1 col-span-full flex justify-center w-{300} h-{300} bg-orange-600 opacity-60 hover:opacity-100" type="submit" form="form1" value="Submit">Enviar</button>


            </form>
            <div></div>
        
            </div>
        </div>
            
            </>
    )
}