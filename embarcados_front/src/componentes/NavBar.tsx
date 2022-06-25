import { Dispatch, SetStateAction } from "react";
import { Link } from "react-router-dom";
interface IProps {
    first: string;
    setFirst: Dispatch<SetStateAction<string>>;
  }
export default function NavBar({first, setFirst}: IProps){


    return (
        <header>
            <div className="w-screen flex flex-1 h-1/6 gap-4 justify-end">
                <Link to={'/'} onClick={()=>setFirst('Home')}><p className={first == 'Home' ? 'text-orange-600 font-bold' : 'text-black hover:text-orange-600'} >Home</p></Link>
                <Link to={'/cadastro'} onClick={()=>setFirst('Cadastro')} ><p className={first == 'Cadastro' ? 'text-orange-600 font-bold' : 'text-black hover:text-orange-600'}>Cadastro</p></Link>
            </div>


        </header>


    )
}