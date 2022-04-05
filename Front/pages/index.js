import Head from 'next/head'
import styles from '../styles/Home.module.css'

export default function Home() {
  return (
    <div className={styles.container}>
      <Head>
        <title>queue</title>
        <meta name="description" content="fila do bandeco" />
      </Head>

      <main className={styles.main}>
        <div >
          <h2 className={styles.title}>Fila agora:</h2>
          <section className='row'>
            <img src='pessoaVerde.png' height={200} width={200} />
            <img src='pessoaVerde.png' height={200} width={200} />
            <img src='pessoaAmarela.png' height={200} width={200} />
            <img src='pessoa.png' height={200} width={200} />
            <img src='pessoa.png' height={200} width={200} />
            <img src='pessoa.png' height={200} width={200} />
          </section>
        </div>
        <div>
          <h2 className={styles.title}>Histórico:</h2>
          <section className='graph'>
            <table >
            <tr className={styles.hea} >
    <th className={styles.hea}>Dia</th>
    <th className={styles.hea}>Tamanho da fila</th>
  </tr>
  <tr className={styles.lin}>
  <td className={styles.col}>Segunda</td>
  <td className={styles.col}>Cheia</td>
  </tr>
  <tr className={styles.lin}>
  <td className={styles.col}>Terça</td>
  <td className={styles.col}>Cheia</td>
  </tr>
  <tr className={styles.lin}>
  <td className={styles.col}>Quarta</td>
  <td className={styles.col}>Media</td>
  </tr>
  <tr className={styles.lin}>
  <td className={styles.col}>Quinta</td>
  <td className={styles.col}>Cheia</td>
  </tr>
  <tr className={styles.lin}>
  <td className={styles.col}>Sexta</td>
  <td className={styles.col}>Media</td>
  </tr>
  <tr className={styles.lin}>
  <td className={styles.col}>Sabado</td>
  <td className={styles.col}>Vazia</td>
  </tr>
    
</table>
          </section>
        </div>
      </main>
    </div>
  )
}
