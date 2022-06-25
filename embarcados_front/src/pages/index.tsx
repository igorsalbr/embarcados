import  {Dispatch, SetStateAction} from "react";
import NavBar from "../componentes/NavBar";

interface IProps {
    first: string;
    setFirst: Dispatch<SetStateAction<string>>;
  }
export default function Home({first, setFirst}: IProps){
  return(<>
  
  <NavBar first={first} setFirst={setFirst}/>
  <h1>HOME</h1>
  
  </>)

}
