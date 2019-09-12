Para todas as questões, escreva os comandos correspondentes no terminal.
1-Escreva o texto "Ola mundo cruel!" em um arquivo denominado "Ola_mundo.txt". Apresente o conteúdo deste arquivo no terminal.
$ cat > Ola_mundo.txt
Ola mundo cruel!
control+z
$ cat Ola_mundo.txt

2-Apresente o nome de todos os arquivos e pastas na pasta 'root'.
$ ls -a /

3-Apresente o tipo de todos os arquivos e pastas na pasta 'root'.
$ cd /
$ file *


4-Apresente somente as pastas dentro da pasta 'root'.
$ cd /
$ file * | grep "directory"

5-Descubra em que dia da semana caiu o seu aniversário nos últimos dez anos.


for ano in `seq 1 10`; do
date --date="$ano years ago" | awk '{print $1}'
done

-Para as questões a seguir, use a pasta no endereço https://github.com/DiogoCaetanoGarcia/Sistemas_Embarcados/raw/master/Questoes/02_Intro_Linux_arqs.zip

6-Liste somente os arquivos com extensão .txt.
$ ls *.txt

7-Liste somente os arquivos com extensão .png.
$ ls *.png

8-Liste somente os arquivos com extensão .jpg.
$ ls *.jpg

9-Liste somente os arquivos com extensão .gif.
$ ls *.gif

10-Liste somente os arquivos que contenham o nome 'cal'.
$ ls | grep “cal”

11-Liste somente os arquivos que contenham o nome 'tux'.
$ ls | grep “tux”


12- Liste somente os arquivos que comecem com o nome 'tux'.
$ ls | grep “^tux”
