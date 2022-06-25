import { Dispatch, SetStateAction } from "react";
import NavBar from "../componentes/NavBar";

interface IProps {
    first: string;
    setFirst: Dispatch<SetStateAction<string>>;
  }

export default function cadastro({first, setFirst}: IProps){

    return (
        <>
        <NavBar first={first} setFirst={setFirst}/>


        <div>CADASTRO</div></>
    )
}