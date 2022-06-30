import axios from "axios";
import  {Dispatch, SetStateAction, useEffect, useState} from "react";
import NavBar from "../componentes/NavBar";

interface IProps {
  entry:  {id:string, id_tag:string, name: string, permission: string, github_link:string, active:boolean}|''
  first: string;
    setFirst: Dispatch<SetStateAction<string>>;
  }
export default function Home({entry, first, setFirst}: IProps){
  
  if (entry && entry.permission && entry.name){
  return(<>
  
    <NavBar first={first} setFirst={setFirst}/>
    
    <div className=" w-3/4 bg-orange-600 mt-5 mx-auto border rounded h-screen shadow-lg

">
      <div className="mt-6 grid grid-cols-6 gap-4 text-white">
         <div className="col-start-1 col-span-full flex  align-middle">
          <div className="w-full h-10 bg-black self-center"></div>
         <img className="w-80 self-center" src={entry.github_link}></img>
         <div className="w-full h-10 bg-black self-center"></div>
         </div>
         <div className="mt-5 col-start-2 col-end-4"><h1 className="text-3xl">Nome:</h1></div>
         <div className="mt-5 col-end-6 col-span-1"><h1 className="text-3xl">{entry.name}</h1></div>
         <div className="mt-10 col-start-2 col-end-4 mb-3"><h1 className="text-3xl">Acesso:</h1></div>
         <div className="mt-10 col-end-6 col-span-1 mb-3"><h1 className="text-3xl">{entry.permission}</h1></div>
  
      </div>
      
      </div>
    
    </>)} else {
      return (<div>
        <NavBar first={first} setFirst={setFirst}/>
        <div className=" w-3/4 bg-orange-600 mt-5 mx-auto border rounded aspect-video shadow-lg

">
      <div className="mt-3 grid grid-cols-6 grid-rows-4 gap-4 text-white">
      <h1 className="col-span-full row-span-full mx-auto my-auto animate-bounce">AGUARDANDO ENTRADA...</h1>
  
      </div>
      
      </div>
        </div>)
    }


}
