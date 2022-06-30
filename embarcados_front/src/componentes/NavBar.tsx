import { Dispatch, SetStateAction } from "react";
import { Link } from "react-router-dom";
interface IProps {
    first: string;
    setFirst: Dispatch<SetStateAction<string>>;
  }
export default function NavBar({first, setFirst}: IProps){
    const handleclick = () =>{
        setFirst('cadastro')
    }

    return (
        <header>
            <div className="w-screen flex flex-1 h-1/6 gap-4 justify-end mr-5">
                <Link to={'/home'} onClick={()=>setFirst('home')}><p className={first == 'home' ? 'text-orange-600 font-bold px-2' : 'text-black hover:text-orange-600 px-2'} >Home  </p></Link>
                <Link to={'/cadastro'} onClick={handleclick} ><p className={first == 'cadastro' ? 'text-orange-600 font-bold px-2' : 'text-black hover:text-orange-600 px-2'}>Cadastro  &nbsp; </p></Link>
                
            </div>


        </header>


    )
}